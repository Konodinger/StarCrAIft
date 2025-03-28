#include "CreateWorkerTask.h"
#include "Tools.h"
#include "Data.h"
#include "BT_ACTION_EXECUTE_METHOD.h"
#include <functional>

CreateWorkerTask::CreateWorkerTask(std::shared_ptr<TaskEmitter> taskEmitter) : Task("Create Worker Task", taskEmitter) {
    m_compatibilityUnitType = { BWAPI::UnitTypes::Protoss_Nexus };

    m_taskBT = std::make_shared<BT_DECORATOR>("Entry Point", nullptr);
    BT_NODE* pActionTrainWorker = new BT_ACTION_EXECUTE_METHOD("ActionTrainWorker", m_taskBT.get(), std::bind(trainWorker, std::placeholders::_1, this));
}

BT_NODE::State CreateWorkerTask::trainWorker(void* data, CreateWorkerTask* task) {
    Data* pData = (Data*)data;

    if (!task->m_have_borrowed) {
        pData->resourcesManager->allocate_resource(ResourceType::MINERALS, BWAPI::UnitTypes::Protoss_Probe.mineralPrice(), task);
        task->m_have_borrowed = true;
    }
    if (pData->resourcesManager->can_borrow(task)) {

    auto nexus = task->getExecutor()->getUnit();
        if (!nexus->isTraining()) {
            BWAPI::Error prevError = BWAPI::Broodwar->getLastError();
            nexus->train(BWAPI::UnitTypes::Protoss_Probe);
            BWAPI::Error newError = BWAPI::Broodwar->getLastError();
            if (newError != BWAPI::Errors::None && newError != prevError)
                return BT_NODE::FAILURE;
            else {
                pData->resourcesManager->free_resource(task);
                return BT_NODE::SUCCESS;
            }
        }
    }
    return BT_NODE::RUNNING;
}