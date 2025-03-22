#include "UnitProducerTE.h"

#include "BT.h"
#include "BT_ACTION_EXECUTE_METHOD.h"
#include "BT_ACTION_ASK_FOR_NEW_PYLONS.h"

#include "CreateWorkerTask.h"
#include "Data.h"
#include "Tools.h"

void UnitProducerTE::createBT()
{
	pTaskEmitterBT = new BT_DECORATOR("EntryPoint", nullptr);
	BT_SEQUENCER* pSequencer = new BT_SEQUENCER("sequencer", pTaskEmitterBT, 2);

	// Create new workers if needed
	BT_DECO_RETURN_SUCCESS* pWorkerProductionSection = new BT_DECO_RETURN_SUCCESS("WorkerProductionSection", pSequencer);
	BT_DECO_CONDITION* pCheckIfEnoughWorkers = new BT_DECO_CONDITION("CheckIfEnoughWorkers", pWorkerProductionSection, checkIfEnoughWorker);
	BT_DECO_MULTIPLEXER* pProduceWorkers = new BT_DECO_MULTIPLEXER("ProduceWorkers", pCheckIfEnoughWorkers);
	BT_CONDITION* pCheckIfEnoughPylons = new BT_CONDITION("CheckIfEnoughPylon", pProduceWorkers, checkIfEnoughPylonForNewWorker);
	BT_ACTION_EXECUTE_METHOD* pEmitCreateWorkerTask = new BT_ACTION_EXECUTE_METHOD("EmitCreateWorkerTask", pProduceWorkers, emitCreateWorkerTask);
	BT_ACTION_ASK_FOR_NEW_PYLONS* pAskForNewWorkers = new BT_ACTION_ASK_FOR_NEW_PYLONS("AskForNewPylons", pProduceWorkers);
}

bool UnitProducerTE::checkIfEnoughWorker(void* data)
{
	Data* pData = static_cast<Data*>(data);
	const BWAPI::UnitType workerType = BWAPI::Broodwar->self()->getRace().getWorker();
	const int workersOwnedWithProgress = Tools::CountUnitsOfType(workerType, BWAPI::Broodwar->self()->getUnits(), true);
	
	return (workersOwnedWithProgress < pData->nWantedWorkersTotal
	&& pData->resourcesManager->getResourceLeft(ResourceType::MINERALS) >= workerType.mineralPrice());
}

bool UnitProducerTE::checkIfEnoughPylonForNewWorker(void* data) {
	
	return (BWAPI::Broodwar->self()->supplyUsed() + BWAPI::UnitTypes::Protoss_Probe.supplyRequired()
		< Tools::GetTotalSupply(false));
}

BT_NODE::State UnitProducerTE::emitCreateWorkerTask(void* data)
{
	Data* pData = static_cast<Data*>(data);
	bool alreadyCreated = false;
	std::shared_ptr<TaskEmitter> te = pData->m_task_emitter_map[EmitterType::UNITPRODUCER];
	for (std::shared_ptr<Task> task : te->m_taskEmitted)
	{
		if (task->getName() == "Create Worker Task") {
			alreadyCreated = true;
			break;
		}
	}

	if (alreadyCreated)
		return BT_NODE::State::RUNNING;
	std::shared_ptr<Task> t = std::make_shared<CreateWorkerTask>(te);
	te->emitTask(data, t);
	return BT_NODE::State::SUCCESS;
}