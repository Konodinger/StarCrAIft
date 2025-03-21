#include "CreateBuildingTask.h"
#include "Tools.h"
#include "BT_ACTION_EXECUTE_METHOD.h"
#include <functional>

CreateBuildingTask::CreateBuildingTask(std::shared_ptr<TaskEmitter> taskEmitter, BWAPI::UnitType building, BWAPI::TilePosition idealPosition) : m_building(building), Task("Mineral Gathering Task", taskEmitter) {
    m_compatibilityUnitAgentType = { UnitAgent::UnitAgentType::WORKER };

    m_buildingIdealPosition = (idealPosition == BWAPI::TilePositions::None)
        ? BWAPI::Broodwar->self()->getStartLocation()
        : idealPosition;

    m_taskBT = std::make_shared<BT_DECORATOR>(BT_DECORATOR("Entry Point", nullptr));
    BT_DECO_RETURN_SUCCESS* pConstructSection = new BT_DECO_RETURN_SUCCESS("ConstructSection", m_taskBT.get());
    BT_DECO_MULTIPLEXER* pConstructPylonOrOther = new BT_DECO_MULTIPLEXER("ConstructPylonOrOther", pConstructSection);
    BT_ACTION_EXECUTE_METHOD* pCheckIfConstructionPylon = new BT_ACTION_EXECUTE_METHOD("CheckIfConstructingPylon", pConstructPylonOrOther, std::bind(checkIfConstructingPylon, std::placeholders::_1, this));
    BT_NODE* pConstructPylon = new BT_ACTION_EXECUTE_METHOD("ConstructPylon", pConstructPylonOrOther, std::bind(constructPylon, std::placeholders::_1, this));
    BT_NODE* pConstructOtherBuilding = new BT_ACTION_EXECUTE_METHOD("ConstructOtherBuilding", pConstructPylonOrOther, std::bind(constructOtherBuilding, std::placeholders::_1, this));
}

BT_NODE::State CreateBuildingTask::constructPylon(void* pData, CreateBuildingTask* task) {
    auto probe = task->getExecutor()->getUnit();
    if (!probe->isConstructing()) {
        BWAPI::Error prevError = BWAPI::Broodwar->getLastError();


        int maxBuildRange = 64;
        BWAPI::TilePosition buildPos = BWAPI::Broodwar->getBuildLocation(task->m_building, task->m_buildingIdealPosition, maxBuildRange, false);
        task->getExecutor()->getUnit()->build(task->m_building, buildPos);

        BWAPI::Error newError = BWAPI::Broodwar->getLastError();
        if (newError != BWAPI::Errors::None && newError != prevError)
            return BT_NODE::FAILURE;
        else {
            task->m_isBuildingBeingConstructed = true;
            return BT_NODE::RUNNING;
        }

    }
    else {
        return (task->m_isBuildingBeingConstructed)
            ? BT_NODE::SUCCESS : BT_NODE::RUNNING;
    }
}

BT_NODE::State CreateBuildingTask::constructOtherBuilding(void* pData, CreateBuildingTask* task) {
    auto probe = task->getExecutor()->getUnit();
    if (!probe->isConstructing()) {
        BWAPI::Error prevError = BWAPI::Broodwar->getLastError();


        int maxBuildRange = 64;
        BWAPI::TilePosition buildPos = BWAPI::Broodwar->getBuildLocation(task->m_building, task->m_buildingIdealPosition, maxBuildRange, false);
        task->getExecutor()->getUnit()->build(task->m_building, buildPos);

        BWAPI::Error newError = BWAPI::Broodwar->getLastError();
        if (newError != BWAPI::Errors::None && newError != prevError)
            return BT_NODE::FAILURE;
        else {
            task->m_isBuildingBeingConstructed = true;
            return BT_NODE::RUNNING;
        }

    }
    else {
        return (task->m_isBuildingBeingConstructed)
            ? BT_NODE::SUCCESS : BT_NODE::RUNNING;
    }
}

BT_NODE::State CreateBuildingTask::checkIfConstructingPylon(void* pData, CreateBuildingTask* task) {
    return (task->m_building == BWAPI::UnitTypes::Protoss_Pylon)
        ? BT_NODE::SUCCESS : BT_NODE::FAILURE;
}