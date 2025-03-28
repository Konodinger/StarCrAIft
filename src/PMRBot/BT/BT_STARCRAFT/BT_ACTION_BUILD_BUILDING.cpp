#include "BT_ACTION_BUILD_BUILDING.h"
#include "Tools.h"
#include "Data.h"
#include "BuildingTask.h"

BT_ACTION_BUILD_BUILDING::BT_ACTION_BUILD_BUILDING(std::string name, BT_NODE* parent, BuildingTask* task, BWAPI::TilePosition idealPosition)
	: BT_ACTION(name, parent), m_task(task), m_idealPosition(idealPosition) {

}

BT_NODE::State BT_ACTION_BUILD_BUILDING::Evaluate(void* data)
{
	return ReturnState(BuildBuilding(data));
}

std::string BT_ACTION_BUILD_BUILDING::GetDescription()
{
	return "BUILD SUPPLY PROVIDER";
}


BT_NODE::State BT_ACTION_BUILD_BUILDING::BuildBuilding(void* data)
{
	Data* pData = (Data*)data;
	BWAPI::Unit builder = m_task->getExecutor()->getUnit();
	for (auto unit : Tools::GetAllIncompleteUnits()) {
		if (unit->getType() == m_task->getType()
			&& unit->getTilePosition().getApproxDistance(builder->getTilePosition()) < 6) {
			// The construction has started...
			BWAPI::Broodwar->printf("Started Building %s", m_task->getType().getName().c_str());
			pData->resourcesManager->free_resource(this);
			return BT_NODE::SUCCESS;
		}
	}

	if (!builder->isConstructing()) {
		if (!m_have_borrowed)
		{
			pData->resourcesManager->allocate_resource(ResourceType::MINERALS, m_task->getType().mineralPrice(), this);
			m_have_borrowed = true;
		}

		if (pData->resourcesManager->can_borrow(this)) {

			BWAPI::TilePosition desiredPosition = m_idealPosition;
			BWAPI::TilePosition buildingPosition;
			if (desiredPosition == BWAPI::TilePositions::None) {
				buildingPosition = BWAPI::Broodwar->getBuildLocation(m_task->getType(), builder->getTilePosition(), 64, false);
				if (Tools::BuildingNeedPower(m_task->getType())
					&& !pData->mapTools.isPowered(buildingPosition.x, buildingPosition.y)) {
					BWAPI::Unit nearestPylon = Tools::GetClosestUnitTo(builder, Tools::GetUnitsOfType(BWAPI::UnitTypes::Protoss_Pylon));
					if (nearestPylon != nullptr) {
						buildingPosition = BWAPI::Broodwar->getBuildLocation(m_task->getType(), nearestPylon->getTilePosition(), 7, false);
							
						// If no good position is found, back to first choice.
						if (!buildingPosition.isValid()) {
							buildingPosition = BWAPI::Broodwar->getBuildLocation(m_task->getType(), builder->getTilePosition(), 64, false);
						}
					}
				}
			}
			else {
				buildingPosition = BWAPI::Broodwar->getBuildLocation(m_task->getType(), desiredPosition, 64, false);
			}

			const bool startedBuilding = builder->build(m_task->getType(), buildingPosition);
			if (!startedBuilding) {
				return BT_NODE::FAILURE;
			}
		}
	}
	return BT_NODE::RUNNING;
}