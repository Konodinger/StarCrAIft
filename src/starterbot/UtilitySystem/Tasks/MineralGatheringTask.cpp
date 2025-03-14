#include "MineralGatheringTask.h"
#include "Tools.h"
#include "BT_ACTION_EXECUTE_METHOD.h"
#include <functional>

MineralGatheringTask::MineralGatheringTask() : Task("Mineral Gathering Task") {
	m_compatibilityUnitAgentType = { UnitAgent::WORKER };

	m_taskBT = std::make_shared<BT_DECORATOR>(BT_DECORATOR("Entry Point", nullptr));
    BT_NODE* pActionGatherNearestMineral = new BT_ACTION_EXECUTE_METHOD("Action execute gatherNearestMaterial", m_taskBT.get(), std::bind(gatherNearestMineral, std::placeholders::_1, m_executor));
}

BT_NODE::State MineralGatheringTask::gatherNearestMineral(void* pData, std::shared_ptr<UnitAgent> unitAgent)
{
    auto unit = unitAgent->getUnit();
    BWAPI::Unit closestMineral = Tools::GetClosestUnitTo(unit, BWAPI::Broodwar->getMinerals());

    // If a valid mineral was found, right click it with the unit in order to start harvesting
    if (closestMineral) {
        unit->rightClick(closestMineral);
        return BT_NODE::SUCCESS;
    }
}
