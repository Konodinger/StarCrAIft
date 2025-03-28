#include "WorkerFleeTask.h"

WorkerFleeTask::WorkerFleeTask(std::shared_ptr<TaskEmitter> taskEmitter) : Task("Worker Flee Task", taskEmitter) {

	m_compatibilityUnitAgentType = { UnitAgent::WORKER };

	m_taskBT = std::make_shared<BT_DECORATOR>("EntryPoint", nullptr);

	BT_NODE* pFleeMainSelector = new BT_SELECTOR("Flee", m_taskBT.get(), 3);

	BT_NODE* pFleeToNearestBaseSequencer = new BT_SEQUENCER("Flee to nearest base", pFleeMainSelector, 2);
	//BT_NODE* pConditionIsBase = new BT_DECO_COND_IS_BASE("", pFleeToNearestBaseSequencer, ...); // => CONDITION TO CREATE
	//BT_NODE* pMoveToNearestBase = new BT_ACTION_MOVE_TO_NEAREST_BASE("Move to nearest base", pFleeToNearestBaseSequencer, ...); // => ACTION TO CREATE

	//BT_NODE* pFleeToNearestArmySequencer = new BT_SEQUENCER("Flee to nearest army", pFleeMainSelector, 2);
	//BT_NODE* pIsArmyNotFleeing = new BT_DECO_COND_ARMY_NOT_FLEEING("Is army not fleeing", pFleeToNearestArmySequencer, ...); // => CONDITION TO CREATE
	//BT_NODE* pMoveToNearestArmy = new BT_ACTION_MOVE_TO_NEAREST_ARMY("Move to nearest army", pFleeToNearestArmySequencer, ...); // => ACTION TO CREATE

	//BT_NODE* pMakeNewBase = new BT_ACTION_MAKE_NEW_BASE("Make new base", pFleeMainSelector, ...); // => ACTION TO CREATE

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
