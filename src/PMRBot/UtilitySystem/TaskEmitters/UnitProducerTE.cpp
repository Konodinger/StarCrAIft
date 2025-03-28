#include "UnitProducerTE.h"

#include "BT.h"
#include "BT_ACTION_EXECUTE_METHOD.h"
#include "BT_ACTION_ASK_FOR_NEW_PYLONS.h"
#include <functional>

#include "CreateWorkerTask.h"
#include "CreateUnitTask.h"
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
	BT_ACTION_EXECUTE_METHOD* pCheckIfEnoughPylons = new BT_ACTION_EXECUTE_METHOD("CheckIfEnoughPylon", pProduceWorkers, std::bind(checkIfEnoughPylonForNewUnit, std::placeholders::_1, BWAPI::UnitTypes::Protoss_Probe));
	BT_ACTION_EXECUTE_METHOD* pEmitCreateWorkerTask = new BT_ACTION_EXECUTE_METHOD("EmitCreateWorkerTask", pProduceWorkers, emitCreateWorkerTask);
	BT_ACTION_ASK_FOR_NEW_PYLONS* pAskForNewPylons = new BT_ACTION_ASK_FOR_NEW_PYLONS("AskForNewPylons", pProduceWorkers);

	// Create new zealots are needed
	BT_DECO_CONDITION* pCheckIfGateway = new BT_DECO_CONDITION("CheckIfGateWay", pSequencer, checkIfGateway);
	BT_SEQUENCER* pGatewaySequencer = new BT_SEQUENCER("GatewaySequencer", pCheckIfGateway, 2);
	
	BT_DECO_RETURN_SUCCESS* pZealotsProductionSection = new BT_DECO_RETURN_SUCCESS("ZealotsProductionSection", pGatewaySequencer);
	BT_DECO_CONDITION* pCheckIfEnoughZealots = new BT_DECO_CONDITION("CheckIfEnoughZealots", pZealotsProductionSection, checkIfEnoughZealot);
	BT_DECO_MULTIPLEXER* pProduceZealots = new BT_DECO_MULTIPLEXER("ProduceZealots", pCheckIfEnoughZealots);
	BT_ACTION_EXECUTE_METHOD* pCheckIfEnoughPylons2 = new BT_ACTION_EXECUTE_METHOD("CheckIfEnoughPylon", pProduceZealots, std::bind(checkIfEnoughPylonForNewUnit, std::placeholders::_1, BWAPI::UnitTypes::Protoss_Zealot));
	BT_ACTION_EXECUTE_METHOD* pEmitCreateZealotTask = new BT_ACTION_EXECUTE_METHOD("EmitCreateZealotTask", pProduceZealots, emitCreateZealotTask);
	BT_ACTION_ASK_FOR_NEW_PYLONS* pAskForNewPylons2 = new BT_ACTION_ASK_FOR_NEW_PYLONS("AskForNewPylons", pProduceZealots);
}

bool UnitProducerTE::checkIfGateway(void* data) {
	return Tools::GetUnitsOfType(BWAPI::UnitTypes::Protoss_Gateway).size() > 0;
}

bool UnitProducerTE::checkIfEnoughWorker(void* data)
{
	Data* pData = static_cast<Data*>(data);
	const BWAPI::UnitType workerType = BWAPI::Broodwar->self()->getRace().getWorker();
	const int workersOwnedWithProgress = Tools::CountUnitsOfType(workerType, BWAPI::Broodwar->self()->getUnits(), true);
	
	return (workersOwnedWithProgress < pData->nWantedWorkersTotal
	&& pData->resourcesManager->getResourceLeft(ResourceType::MINERALS) >= workerType.mineralPrice());
}

bool UnitProducerTE::checkIfEnoughZealot(void* data) {
	Data* pData = static_cast<Data*>(data);
	const BWAPI::UnitType unitType = BWAPI::UnitTypes::Protoss_Zealot;
	const int unitOwnedWithProgress = Tools::CountUnitsOfType(unitType, BWAPI::Broodwar->self()->getUnits(), true);
	return (unitOwnedWithProgress < pData->nWantedZealotsTotal);
}

BT_NODE::State UnitProducerTE::checkIfEnoughPylonForNewUnit(void* data, BWAPI::UnitType unitType) {
	
	return (BWAPI::Broodwar->self()->supplyUsed() + unitType.supplyRequired()
		< Tools::GetTotalSupply(false))
		? BT_NODE::SUCCESS : BT_NODE::FAILURE;
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


BT_NODE::State UnitProducerTE::emitCreateZealotTask(void* data) {
	auto unitToBuild = BWAPI::UnitTypes::Protoss_Zealot;
	auto building = BWAPI::UnitTypes::Protoss_Gateway;
	
	Data* pData = static_cast<Data*>(data);
	bool alreadyCreated = false;
	std::shared_ptr<TaskEmitter> te = pData->m_task_emitter_map[EmitterType::UNITPRODUCER];
	for (std::shared_ptr<Task> task : te->m_taskEmitted)
	{
		if (task->getName() == "Create Unit Task") {
			std::shared_ptr<CreateUnitTask> bTask = std::static_pointer_cast<CreateUnitTask>(task);
			if (bTask->getType() == unitToBuild) {
				alreadyCreated = true;
				break;
			}
			alreadyCreated = true;
			break;
		}
	}

	if (alreadyCreated)
		return BT_NODE::State::RUNNING;
	std::shared_ptr<Task> t = std::make_shared<CreateUnitTask>(te, unitToBuild, building);
	te->emitTask(data, t);
	return BT_NODE::State::SUCCESS;
}