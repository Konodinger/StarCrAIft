#include "SoldierFleeTask.h"

#include "BT.h"
#include "BT_ACTION_EXECUTE_METHOD.h"

SoldierFleeTask::SoldierFleeTask(std::shared_ptr<TaskEmitter> taskEmitter) : Task("Soldier Flee Task", taskEmitter) {
	
	m_compatibilityUnitAgentType = { UnitAgent::GROUNDMOBILE, UnitAgent::FLYINGMOBILE };

	m_taskBT = std::make_shared<BT_DECORATOR>("Entry Point", nullptr);

	BT_NODE* pFleeMainSelector = new BT_SELECTOR("Flee selector", m_taskBT.get(), 2);

	BT_NODE* pFleeToNearestArmySequencer = new BT_SEQUENCER("Flee to nearest army", pFleeMainSelector, 2);
	BT_NODE* pIsArmyNotFleeing = new BT_DECO_CONDITION("Is army not fleeing", pFleeToNearestArmySequencer, isArmyFleeing); // => CONDITION TO CREATE
	BT_NODE* pMoveToNearestArmy = new BT_ACTION_EXECUTE_METHOD("Move to nearest army", pFleeToNearestArmySequencer, moveToNearestArmy); // => ACTION TO CREATE

	BT_NODE* pFleeToNearestBaseSequencer = new BT_SEQUENCER("Flee to nearest base", pFleeMainSelector, 2);
	BT_NODE* pConditionIsBase = new BT_DECO_CONDITION("Is there a base", pFleeToNearestBaseSequencer, isThereBase); // => CONDITION TO CREATE
	BT_NODE* pMoveToNearestBase = new BT_ACTION_EXECUTE_METHOD("Move to nearest base", pFleeToNearestBaseSequencer, moveToNearestBase); // => ACTION TO CREATE
}


bool SoldierFleeTask::isArmyFleeing(void* data)
{
	Data* pData = (Data*)data;

	// TODO
	// 
	//

	return true;
}

BT_NODE::State SoldierFleeTask::moveToNearestArmy(void* data)
{
	Data* pData = (Data*)data;

	// TODO
	// 
	//

	return BT_NODE::State::SUCCESS;
}

bool SoldierFleeTask::isThereBase(void* data)
{
	Data* pData = (Data*)data;

	// TODO
	// 
	//

	return true;
}

BT_NODE::State SoldierFleeTask::moveToNearestBase(void* data)
{
	Data* pData = (Data*)data;

	// TODO
	// 
	//

	return BT_NODE::State::SUCCESS;
}