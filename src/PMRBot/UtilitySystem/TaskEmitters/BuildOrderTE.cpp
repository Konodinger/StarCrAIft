#include "BuildOrderTE.h"
#include "Tools.h"
#include "BuildingTask.h"
#include "Data.h"

void BuildOrderTE::ExecuteTaskEmissionBT(Data* pData) {
	const BWAPI::UnitType workerType = BWAPI::Broodwar->self()->getRace().getWorker();
	const int workersOwned = Tools::CountUnitsOfType(workerType, BWAPI::Broodwar->self()->getUnits());
	const int workersOwnedWithProgress = Tools::CountUnitsOfType(workerType, BWAPI::Broodwar->self()->getUnits(), true);

	if (workersOwned != m_numRegisteredWorkers) {
		m_numRegisteredWorkers = workersOwned;
		if (workersOwned == 7 || workersOwned == 14 || workersOwned == 22) { // PYLON
			if (pData->askingForNewPylons == Data::UNNEEDED)
				pData->askingForNewPylons = Data::REQUESTED;
		}
		if (workersOwned == 16) { // GATEWAY
			std::shared_ptr<Task> task = std::make_shared<BuildingTask>(pData->m_task_emitter_map[EmitterType::BUILDORDER], BWAPI::UnitTypes::Protoss_Gateway, pData->resourcesManager);
			emitTask(pData, task);
			std::cout << "BuildOrder: Create Gateway" << std::endl;
		}
		if (workersOwned == 17) { // ASSIMILATOR
			std::shared_ptr<Task> task = std::make_shared<BuildingTask>(pData->m_task_emitter_map[EmitterType::BUILDORDER], BWAPI::UnitTypes::Protoss_Assimilator, pData->resourcesManager);
			emitTask(pData, task);
			std::cout << "BuildOrder: Create Assimilator" << std::endl;
		}
		if (workersOwned == 20) { // NEXUS CORE
			std::shared_ptr<Task> task = std::make_shared<BuildingTask>(pData->m_task_emitter_map[EmitterType::BUILDORDER], BWAPI::UnitTypes::Protoss_Nexus, pData->resourcesManager);
			emitTask(pData, task);
			std::cout << "BuildOrder: Create Nexus" << std::endl;
		}
		if (workersOwned == 23) { // WARP RESEARCH
			std::shared_ptr<Task> task = std::make_shared<BuildingTask>(pData->m_task_emitter_map[EmitterType::BUILDORDER], BWAPI::UnitTypes::Protoss_Cybernetics_Core, pData->resourcesManager);
			emitTask(pData, task);
			std::cout << "BuildOrder: Create Cybernetics Core" << std::endl;
		}

		std::cout << "Number of workers: " << workersOwned << std::endl;
	}

	if (workersOwnedWithProgress < pData->nWantedWorkersTotal && pData->resourcesManager->getResourceLeft(ResourceType::MINERALS) >= workerType.mineralPrice()) {
		const BWAPI::Unit myDepot = Tools::GetDepot();

		if (myDepot && !myDepot->isTraining()) { myDepot->train(workerType); }
	}

	if (pData->askingForNewPylons == Data::REQUESTED) {
		std::shared_ptr<Task> task = std::make_shared<BuildingTask>(pData->m_task_emitter_map[EmitterType::BUILDORDER], BWAPI::UnitTypes::Protoss_Pylon, pData->resourcesManager);
		emitTask(pData, task);
		std::cout << "BuildOrder: Create Pylon" << std::endl;
		pData->askingForNewPylons = Data::TREATED;
	}
}