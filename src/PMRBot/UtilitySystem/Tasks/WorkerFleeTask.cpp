#include "WorkerFleeTask.h"


#include "BT_ACTION_EXECUTE_METHOD.h"

WorkerFleeTask::WorkerFleeTask(std::shared_ptr<TaskEmitter> taskEmitter) : Task("Worker Flee Task", taskEmitter) {

	m_compatibilityUnitAgentType = { UnitAgent::WORKER };

	m_taskBT = std::make_shared<BT_DECORATOR>("EntryPoint", nullptr);

	BT_NODE* pFleeMainSelector = new BT_SELECTOR("Flee", m_taskBT.get(), 3);

	BT_NODE* pFleeToNearestBaseSequencer = new BT_SEQUENCER("Flee to nearest base", pFleeMainSelector, 2);
	BT_NODE* pConditionIsBase = new BT_DECO_CONDITION("", pFleeToNearestBaseSequencer, isThereBase); // => CONDITION TO CREATE
	BT_NODE* pMoveToNearestBase = new BT_ACTION_EXECUTE_METHOD("Move to nearest base", pFleeToNearestBaseSequencer, moveToNearestBase); // => ACTION TO CREATE

	BT_NODE* pFleeToNearestArmySequencer = new BT_SEQUENCER("Flee to nearest army", pFleeMainSelector, 2);
	BT_NODE* pIsArmyNotFleeing = new BT_DECO_CONDITION("Is army not fleeing", pFleeToNearestArmySequencer, isArmyFleeing); // => CONDITION TO CREATE
	BT_NODE* pMoveToNearestArmy = new BT_ACTION_EXECUTE_METHOD("Move to nearest army", pFleeToNearestArmySequencer, moveToNearestArmy); // => ACTION TO CREATE

	BT_NODE* pMakeNewBase = new BT_ACTION_EXECUTE_METHOD("Make new base", pFleeMainSelector, makeNewBase); // => ACTION TO CREATE

}

bool WorkerFleeTask::isThereBase(void* data)
{
	Data* pData = (Data*)data;

	// TODO
	// 
	//

	return true;
}

BT_NODE::State WorkerFleeTask::moveToNearestBase(void* data)
{
	Data* pData = (Data*)data;

	// TODO
	// 
	//

	return BT_NODE::State::SUCCESS;
}

bool WorkerFleeTask::isArmyFleeing(void* data)
{
	Data* pData = (Data*)data;

	// TODO
	// 
	//

	return true;
}

BT_NODE::State WorkerFleeTask::moveToNearestArmy(void* data)
{
	Data* pData = (Data*)data;

	// TODO
	// 
	//

	return BT_NODE::State::SUCCESS;
}

BT_NODE::State WorkerFleeTask::makeNewBase(void* data)
{
	Data* pData = (Data*)data;

	// TODO
	// 
	//

	return BT_NODE::State::SUCCESS;
}
