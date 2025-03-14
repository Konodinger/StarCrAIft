#include "WorkerTE.h"

#include "BT.h"
#include "BT_ACTION_EXECUTE_METHOD.h"

#include "MineralGatheringTask.h"
#include "VespeneGatheringTask.h"

#include "ScoutTask.h"

void WorkerTE::createBT()
{
	pTaskEmitterBT = new BT_DECORATOR("EntryPoint", nullptr);
	BT_SEQUENCER* pSequencer = new BT_SEQUENCER("sequencer", pTaskEmitterBT, 3);

	// change si le bt marche pas ça doit être possible de faire beaucoup plus simple, ça devrait suffir de juste créer (n_max - n) taches

	// minerals
	BT_DECO_UNTIL_FAILURE* pWhileMineralGatheringNotEnough = new BT_DECO_UNTIL_FAILURE("WhileMineralGatheringNotEnough", pSequencer);
	BT_SEQUENCER* pSequencerMineralGathering = new BT_SEQUENCER("SequencerMineralGathering", pWhileMineralGatheringNotEnough, 2);
	BT_CONDITION* pTestIfEnoughMineralGathering = new BT_CONDITION("TestIfEnoughMineralGathering", pSequencerMineralGathering, checkIfEnoughMineralGathering);
	BT_ACTION_EXECUTE_METHOD* pEmitMineralGatheringTask = new BT_ACTION_EXECUTE_METHOD("EmitMineralGatheringTask", pTestIfEnoughMineralGathering, emitMineralGatheringTask);

	// vespene
	BT_DECO_UNTIL_FAILURE* pWhileVespeneGatheringNotEnough = new BT_DECO_UNTIL_FAILURE("WhileVespeneGatheringNotEnough", pSequencer);
	BT_SEQUENCER* pSequencerVespeneGathering = new BT_SEQUENCER("SequencerVespeneGathering", pWhileVespeneGatheringNotEnough, 2);
	BT_CONDITION* pTestIfEnoughVespeneGathering = new BT_CONDITION("TestIfEnoughVespeneGathering", pSequencerVespeneGathering, checkIfEnoughVespeneGathering);
	BT_ACTION_EXECUTE_METHOD* pEmitVespeneGatheringTask = new BT_ACTION_EXECUTE_METHOD("EmitVespeneGatheringTask", pSequencerVespeneGathering, emitVespeneGatheringTask);

	// scouting
	BT_DECO_UNTIL_FAILURE* pWhileScoutNotEnough = new BT_DECO_UNTIL_FAILURE("WhileScoutNotEnough", pSequencer);
	BT_SEQUENCER* pSequencerScout = new BT_SEQUENCER("SequencerScout", pWhileScoutNotEnough, 2);
	BT_CONDITION* pTestIfEnoughScout = new BT_CONDITION("TestIfEnoughScout", pSequencerScout, checkIfEnoughScout);
	BT_ACTION_EXECUTE_METHOD* pEmitScoutTask = new BT_ACTION_EXECUTE_METHOD("EmitScoutTask", pSequencerScout, emitScoutingTask);
}

bool WorkerTE::checkIfEnoughMineralGathering(void* pData)
{
	Data* data = static_cast<Data*>(pData);
	auto taskList = data->m_task_emitter_map[WORKER].m_taskEmitted;
	int count = 0;
	for (std::shared_ptr<Task> task : taskList)
	{
		// if(task.isInstanceOf(MineralGatheringTask)) { count++; }
	//}

	return count < data->goalMineralGatheringWorkforce;
}

// d'ailleurs ça on peut surement en faire un template au niveau de TaskEmitter
BT_NODE::State WorkerTE::emitMineralGatheringTask(void* pData)
{
	// Task t = std::make_shared<MineralGatheringTask>();
	// data->m_taskList.push_back(t);
	// m_taskEmitted.push_back(t);
	return BT_NODE::State::SUCCESS;
}

bool WorkerTE::checkIfEnoughVespeneGathering(void* pData)
{
	Data* data = static_cast<Data*>(pData);
	auto taskList = data->m_task_emitter_map[WORKER].m_taskEmitted;
	int count = 0;
	for (std::shared_ptr<Task> task : taskList)
	{
		// if(task.isInstanceOf(VespeneGatheringTask)) { count++; }
	}

	return count < data->goalVespeneGatheringWorkforce;
}

BT_NODE::State WorkerTE::emitVespeneGatheringTask(void* pData)
{
	// Task t = std::make_shared<VespeneGatheringTask>();
	// data->m_taskList.push_back(t);
	// m_taskEmitted.push_back(t);
	return BT_NODE::State::SUCCESS;
}



bool WorkerTE::checkIfEnoughScout(void* pData)
{
	Data* data = static_cast<Data*>(pData);
	auto taskList = data->m_task_emitter_map[WORKER].m_taskEmitted;
	int count = 0;
	for (std::shared_ptr<Task> task : taskList)
	{
		// if task == scouter : count++;
	}

	return count >= data->goalMineralGatheringWorkforce;
}

BT_NODE::State WorkerTE::emitScoutingTask(void* pData)
{
	std::shared_ptr<Task> t = std::make_shared<ScoutTask>();
	Data* data = static_cast<Data*>(pData);
	data->m_task_emitter_map[WORKER].emitTask(pData, t);
	return BT_NODE::State::SUCCESS;
}
