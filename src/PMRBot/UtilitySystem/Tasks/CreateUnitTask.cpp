#include "CreateUnitTask.h"
#include "Tools.h"
#include "Data.h"
#include "BT_ACTION_EXECUTE_METHOD.h"
#include <functional>

CreateUnitTask::CreateUnitTask(std::shared_ptr<TaskEmitter> taskEmitter, BWAPI::UnitType unitToCreate, BWAPI::UnitType buildingTraining)
    : Task("Create Unit Task", taskEmitter), unitToTrain(unitToCreate) {
    m_compatibilityUnitType = { buildingTraining };

    m_taskBT = std::make_shared<BT_DECORATOR>("Entry Point", nullptr);
    BT_NODE* pActionTrainWorker = new BT_ACTION_EXECUTE_METHOD("ActionTrainUnit", m_taskBT.get(), std::bind(trainUnit, std::placeholders::_1, this));
}

BT_NODE::State CreateUnitTask::trainUnit(void* data, CreateUnitTask* task) {
    Data* pData = (Data*)data;

    BWAPI::UnitType unitToTrain = task->unitToTrain;

    if (!task->m_have_borrowed) {
        pData->resourcesManager->allocate_resource(ResourceType::MINERALS, unitToTrain.mineralPrice(), task);
        task->m_have_borrowed = true;
    }
    if (pData->resourcesManager->can_borrow(task)) {

        auto building = task->getExecutor()->getUnit();
        if (!building->isTraining()) {
            BWAPI::Error prevError = BWAPI::Broodwar->getLastError();
            building->train(unitToTrain);
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