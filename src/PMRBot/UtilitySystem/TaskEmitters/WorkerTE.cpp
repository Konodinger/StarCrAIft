#include "WorkerTE.h"

#include "BT.h"
#include "BT_ACTION_EXECUTE_METHOD.h"

#include "VespeneGatheringTask.h"

#include "ScoutTask.h"
#include "Data.h"
#include "Tools.h"

void WorkerTE::createBT()
{
	pTaskEmitterBT = new BT_DECORATOR("EntryPoint", nullptr);
	BT_SEQUENCER* pSequencer = new BT_SEQUENCER("sequencer", pTaskEmitterBT, 1);

	// scouting
	BT_DECO_RETURN_SUCCESS* pScoutingSection = new BT_DECO_RETURN_SUCCESS("ScoutingSection", pSequencer);
	BT_DECO_CONDITION* pCheckIfAdvancedEnough = new BT_DECO_CONDITION("Check if advanced enough", pScoutingSection, checkIfAdvancedEnough);
	BT_DECO_CONDITION* pTestIfEnoughScout = new BT_DECO_CONDITION("TestIfEnoughScout", pCheckIfAdvancedEnough, checkIfNeedScout);
	BT_ACTION_EXECUTE_METHOD* pEmitScoutTask = new BT_ACTION_EXECUTE_METHOD("EmitScoutTask", pTestIfEnoughScout, emitScoutingTask);
}

bool WorkerTE::checkIfAdvancedEnough(void* data) {
	Data* pData = static_cast<Data*>(data);
	const BWAPI::UnitType workerType = BWAPI::Broodwar->self()->getRace().getWorker();
	const int workersOwned = Tools::CountUnitsOfType(workerType, BWAPI::Broodwar->self()->getUnits(), false);

	return workersOwned >= pData->nMinWorkersBeforeScouting;
}

bool WorkerTE::checkIfNeedScout(void* pData)
{
	Data* data = static_cast<Data*>(pData);
	auto& taskList = data->m_task_emitter_map[EmitterType::WORKER]->m_taskEmitted;
	int count = 0;
	for (std::shared_ptr<Task> task : taskList)
	{
		if (task->getName() == "Scout Task")
			count++;
	}

	return count < data->goalScoutWorkforce;
}

BT_NODE::State WorkerTE::emitScoutingTask(void* pData)
{
	Data* data = static_cast<Data*>(pData);
	std::shared_ptr<TaskEmitter> te = data->m_task_emitter_map[EmitterType::WORKER];
	std::shared_ptr<Task> t = std::make_shared<ScoutTask>(te, enemyBaseList, nbScoutsMonitoring);
	te->emitTask(pData, t);
	return BT_NODE::State::SUCCESS;
}
