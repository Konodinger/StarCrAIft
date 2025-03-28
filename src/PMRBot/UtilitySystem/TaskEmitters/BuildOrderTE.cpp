#include "BuildOrderTE.h"
#include "Tools.h"
#include "BuildingTask.h"
#include "Data.h"

void BuildOrderTE::ExecuteTaskEmissionBT(Data* pData) {
	const BWAPI::UnitType workerType = BWAPI::Broodwar->self()->getRace().getWorker();
	const int workersOwned = Tools::CountUnitsOfType(workerType, BWAPI::Broodwar->self()->getUnits());
	const int workersOwnedWithProgress = Tools::CountUnitsOfType(workerType, BWAPI::Broodwar->self()->getUnits(), true);

	for (auto& buildElement : pData->buildOrderTechTree) {
		if (workersOwned >= buildElement.first
			&& (Tools::CountUnitsOfType(buildElement.second, BWAPI::Broodwar->self()->getUnits()) == 0)) {
			const BWAPI::TechType techType = buildElement.second.requiredTech();
			if (techType == BWAPI::TechTypes::None
				|| BWAPI::Broodwar->self()->hasResearched(techType)) {
				
				// Let's check if a similar task has already been created...
				bool alreadyCreated = false;
				for (std::shared_ptr<Task> task : m_taskEmitted)
				{
					if (task->getName() == "Building Task") {
						std::shared_ptr<BuildingTask> bTask = std::static_pointer_cast<BuildingTask>(task);
						if (bTask->getType() == buildElement.second) {
							alreadyCreated = true;
							break;
						}
					}
				}
				if (!alreadyCreated) {
					std::shared_ptr<Task> task = std::make_shared<BuildingTask>(pData->m_task_emitter_map[EmitterType::BUILDORDER], buildElement.second, pData->resourcesManager);
					emitTask(pData, task);
					std::cout << "BuildOrder: " << buildElement.second.getName() << std::endl;
				}
			}
			else {
				BWAPI::Broodwar->printf("Can't build...........");
			}
		}
	}

	//if (workersOwned != m_numRegisteredWorkers) {
	//	m_numRegisteredWorkers = workersOwned;
	//	if (workersOwned == 16) { // GATEWAY
	//		std::shared_ptr<Task> task = std::make_shared<BuildingTask>(pData->m_task_emitter_map[EmitterType::BUILDORDER], BWAPI::UnitTypes::Protoss_Gateway, pData->resourcesManager);
	//		emitTask(pData, task);
	//		std::cout << "BuildOrder: Create Gateway" << std::endl;
	//	}
	//	if (workersOwned == 17) { // ASSIMILATOR
	//		std::shared_ptr<Task> task = std::make_shared<BuildingTask>(pData->m_task_emitter_map[EmitterType::BUILDORDER], BWAPI::UnitTypes::Protoss_Assimilator, pData->resourcesManager);
	//		emitTask(pData, task);
	//		std::cout << "BuildOrder: Create Assimilator" << std::endl;
	//	}
	//	if (workersOwned == 20) { // NEXUS CORE
	//		std::shared_ptr<Task> task = std::make_shared<BuildingTask>(pData->m_task_emitter_map[EmitterType::BUILDORDER], BWAPI::UnitTypes::Protoss_Nexus, pData->resourcesManager);
	//		emitTask(pData, task);
	//		std::cout << "BuildOrder: Create Nexus" << std::endl;
	//	}
	//	if (workersOwned == 23) { // WARP RESEARCH
	//		std::shared_ptr<Task> task = std::make_shared<BuildingTask>(pData->m_task_emitter_map[EmitterType::BUILDORDER], BWAPI::UnitTypes::Protoss_Cybernetics_Core, pData->resourcesManager);
	//		emitTask(pData, task);
	//		std::cout << "BuildOrder: Create Cybernetics Core" << std::endl;
	//	}

	//	std::cout << "Number of workers: " << workersOwned << std::endl;
	//}

	/*if (workersOwnedWithProgress < pData->nWantedWorkersTotal && pData->resourcesManager->getResourceLeft(ResourceType::MINERALS) >= workerType.mineralPrice()) {
		const BWAPI::Unit myDepot = Tools::GetDepot();

		if (myDepot && !myDepot->isTraining()) { myDepot->train(workerType); }
	}*/

	// Check if new pylons are needed
	if (Tools::GetUnusedSupply(false) <= pData->thresholdSupply) {
		if (pData->askingForNewPylons == Data::UNNEEDED)
			pData->askingForNewPylons = Data::REQUESTED;
	}

	for (auto building : Tools::GetAllBuildings()) {
		if (Tools::BuildingNeedPower(building->getType()) && !building->isPowered()) {
			if (pData->askingForNewPylons == Data::UNNEEDED)
				pData->askingForNewPylons = Data::REQUESTED;
			if (pData->askingForNewPylons != Data::TREATED
				&& pData->askingForNewPylonsIdealPosition != BWAPI::TilePositions::None)
				pData->askingForNewPylonsIdealPosition = building->getTilePosition();
		}
	}

	if (pData->askingForNewPylons == Data::REQUESTED) {
		std::shared_ptr<Task> task = std::make_shared<BuildingTask>(pData->m_task_emitter_map[EmitterType::BUILDORDER], BWAPI::UnitTypes::Protoss_Pylon, pData->resourcesManager, pData->askingForNewPylonsIdealPosition);
		emitTask(pData, task);
		pData->askingForNewPylons = Data::TREATED;
	}
}