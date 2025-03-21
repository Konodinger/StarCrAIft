#include "UnitProducerTE.h"

#include "BT.h"
#include "BT_ACTION_EXECUTE_METHOD.h"
#include "BT_ACTION_ASK_FOR_NEW_PYLONS.h"
#include "BT_ACTION_EMIT_CREATE_PYLON_TASK.h"

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
	BT_CONDITION* pCheckIfEnoughPylons = new BT_CONDITION("CheckIfEnoughPylon", pProduceWorkers, checkIfEnoughPylon);
	BT_ACTION_EXECUTE_METHOD* pEmitCreateWorkerTask = new BT_ACTION_EXECUTE_METHOD("EmitCreateWorkerTask", pProduceWorkers, emitCreateWorkerTask);
	BT_ACTION_ASK_FOR_NEW_PYLONS* pAskForNewWorkers = new BT_ACTION_ASK_FOR_NEW_PYLONS("AskForNewPylons", pProduceWorkers);

	// Create new pylons if needed
	BT_DECO_RETURN_SUCCESS* pPylonProductionSection = new BT_DECO_RETURN_SUCCESS("PylonProductionSection", pSequencer);
	BT_DECO_CONDITION* pConditionAskForNewPylons = new BT_DECO_CONDITION("CheckIfAskForNewPylons", pPylonProductionSection, checkIfAskForNewPylons);
	BT_ACTION_EMIT_CREATE_PYLON_TASK* pEmitCreatePylonTask = new BT_ACTION_EMIT_CREATE_PYLON_TASK("EmitCreatePylonTask", pConditionAskForNewPylons, this);
}

bool UnitProducerTE::checkIfEnoughWorker(void* data)
{
	//TODO
	return true;
}

bool UnitProducerTE::checkIfAskForNewPylons(void* data)
{
	Data* pData = static_cast<Data*>(data);
	return pData->askForNewPylons;
}

bool UnitProducerTE::checkIfEnoughPylon(void* data) {
	return (BWAPI::Broodwar->self()->supplyUsed() < Tools::GetTotalSupply(true));
}

BT_NODE::State UnitProducerTE::emitCreateWorkerTask(void* data)
{
	Data* pData = static_cast<Data*>(data);
	std::shared_ptr<TaskEmitter> te = pData->m_task_emitter_map[EmitterType::UNITPRODUCER];
	std::shared_ptr<Task> t = std::make_shared<CreateWorkerTask>(te);
	te->emitTask(data, t);
	return BT_NODE::State::SUCCESS;
}