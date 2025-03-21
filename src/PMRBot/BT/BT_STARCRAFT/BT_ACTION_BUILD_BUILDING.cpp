#include "BT_ACTION_BUILD_BUILDING.h"
#include "Tools.h"
#include "Data.h"
#include "BuildingTask.h"

BT_ACTION_BUILD_BUILDING::BT_ACTION_BUILD_BUILDING(std::string name, BT_NODE* parent, BuildingTask* task)
	: BT_ACTION(name, parent), m_task(task) {

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

	if (!have_borrowed)
	{
		pData->resourcesManager->allocate_resource(ResourceType::MINERALS, m_task->getType().mineralPrice(), this);
		have_borrowed = true;
	}

	if (pData->resourcesManager->can_borrow(this)) {

		BWAPI::Unit builder = m_task->getExecutor()->getUnit();
		BWAPI::TilePosition desiredPos = BWAPI::Broodwar->getBuildLocation(m_task->getType(), builder->getTilePosition(), 64, false);

		const bool startedBuilding = builder->build(m_task->getType(), desiredPos);
		if (startedBuilding) {
			BWAPI::Broodwar->printf("Started Building %s", m_task->getType().getName().c_str());
			pData->resourcesManager->free_resource(this);
			return BT_NODE::SUCCESS;
		}
	}

	return BT_NODE::FAILURE;

	//const bool startedBuilding = Tools::BuildBuilding(m_type);

	//if (startedBuilding)
	//	BWAPI::Broodwar->printf("Started Building %s", m_type.getName().c_str());

	//return startedBuilding ? BT_NODE::SUCCESS : BT_NODE::FAILURE;
}