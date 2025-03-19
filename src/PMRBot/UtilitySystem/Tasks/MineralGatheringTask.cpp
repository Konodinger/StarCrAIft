#include "MineralGatheringTask.h"
#include "Tools.h"
#include "BT_ACTION_EXECUTE_METHOD.h"
#include <functional>

MineralGatheringTask::MineralGatheringTask(std::shared_ptr<TaskEmitter> taskEmitter) : Task("Mineral Gathering Task", taskEmitter) {
	m_compatibilityUnitAgentType = { UnitAgent::WORKER };

	m_taskBT = std::make_shared<BT_DECORATOR>(BT_DECORATOR("Entry Point", nullptr));
    BT_NODE* pActionGatherNearestMineral = new BT_ACTION_EXECUTE_METHOD("Action execute gatherNearestMaterial", m_taskBT.get(), std::bind(gatherNearestMineral, std::placeholders::_1, this));
}

BT_NODE::State MineralGatheringTask::gatherNearestMineral(void* pData, MineralGatheringTask* task)
{
    auto unit = task->getExecutor()->getUnit();
    BWAPI::Unit closestMineral = Tools::GetClosestUnitTo(unit, BWAPI::Broodwar->getMinerals());

    // If a valid mineral was found, right click it with the unit in order to start harvesting
    if (closestMineral) {
        unit->rightClick(closestMineral);
        return BT_NODE::SUCCESS;
    }
    return BT_NODE::FAILURE;
}
