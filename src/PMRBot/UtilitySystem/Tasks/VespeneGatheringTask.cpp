#include "VespeneGatheringTask.h"
#include "Tools.h"
#include "BT_ACTION_EXECUTE_METHOD.h"
#include <functional>

VespeneGatheringTask::VespeneGatheringTask(std::shared_ptr<TaskEmitter> taskEmitter) : Task("Vespene Gathering Task", taskEmitter) {
    m_compatibilityUnitAgentType = { UnitAgent::WORKER };

    m_taskBT = std::make_shared<BT_DECORATOR>("Entry Point", nullptr);
    BT_NODE* pActionGatherNearestMineral = new BT_ACTION_EXECUTE_METHOD("Action execute gatherNearestVespene", m_taskBT.get(), std::bind(gatherNearestVespene, std::placeholders::_1, this));
}

BT_NODE::State VespeneGatheringTask::gatherNearestVespene(void* pData, VespeneGatheringTask* task)
{
    auto unit = task->getExecutor()->getUnit();
    BWAPI::Unit closestVespene = Tools::GetClosestUnitTo(unit, BWAPI::Broodwar->getGeysers());

    // If a valid geyser was found, right click it with the unit in order to start harvesting
    if (closestVespene) {
        unit->rightClick(closestVespene);
        return BT_NODE::SUCCESS;
    }
    return BT_NODE::FAILURE;
}
