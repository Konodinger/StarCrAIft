#include "PMRBot.h"
#include "Tools.h"
#include "Data.h"
#include <algorithm>

#define LOCAL_SPEED 10
#define FRAME_SKIP 0



PMRBot::PMRBot() {
	pData = new Data();
	pData->currMinerals = 0;
	pData->thresholdMinerals = THRESHOLD1_MINERALS;
	pData->currSupply = 0;
	pData->thresholdSupply = THRESHOLD1_UNUSED_SUPPLY;
	pData->nWantedWorkersTotal = NWANTED_WORKERS_TOTAL;
	pData->nWantedWorkersFarmingMinerals = NWANTED_WORKERS_FARMING_MINERALS;

	pData->m_task_emitter_map[EmitterType::WORKER] = std::make_shared<WorkerTE>();
	pData->m_task_emitter_map[EmitterType::BUILDORDER] = std::make_shared<BuildOrderTE>();
	pData->m_eventManagerTE = std::make_shared<EventManagerTE>(pData);

	pData->resourcesManager = std::make_shared<ResourcesManager>();

	m_IdleManager = std::make_shared<IdleManager>(pData);

}

void PMRBot::runBotLoop() {

	// Update resources
	pData->resourcesManager->updateResources();

	// Loop over all task emitters and execute their behaviour tree
	for (auto& emitter : pData->m_task_emitter_map) {
		emitter.second->ExecuteTaskEmissionBT(pData);
	}

	// Same for other TE...

	//pData->m_task_emitter_map[EmitterType::WORKER]->computeTaskReward();
	for (auto& emitter : pData->m_task_emitter_map) {
		emitter.second->computeTaskReward();
	}
	// Same for other TE...
	// 


	// Check if units should flee and compute their interest in available tasks.
	for (auto& id_unitAgent_pair : pData->unitAgentsList) {
		auto& unitAgent = id_unitAgent_pair.second;
		unitAgent->checkFlee(pData);
		if (unitAgent->getState() == UnitAgent::IDLING) {
			for (auto& task : pData->m_taskList) {

				m_taskToAgentInterest[task][unitAgent] = unitAgent->computeInterest(task);
			}
		}
		else {
			for (auto& task : pData->m_taskList) {
				m_taskToAgentInterest[task].erase(unitAgent);
			}
		}
	}

	// Attribute tasks to agents
	taskAttribuer();

	// Execute agents behaviour tree
	for (auto& id_unitAgent_pair : pData->unitAgentsList) {
		//BWAPI::Broodwar->printf(std::to_string(a++).c_str());
		id_unitAgent_pair.second->execute(pData);
	}

	// IDLE behaviour
	m_IdleManager->Execute();
}

void PMRBot::taskAttribuer() {

	// Sort tasks by reward in descending order
	std::sort(pData->m_taskList.begin(), pData->m_taskList.end(), [this](const std::shared_ptr<Task>& task1, const std::shared_ptr<Task>& task2) {
		return task1->reward() > task2->reward();
		});

	if (pData->m_taskList.size() > 0)
		BWAPI::Broodwar->printf(("NB task: " + std::to_string(pData->m_taskList.size()) + ".").c_str());

	// For each task, attribute it to the best suited agent
	for (const std::shared_ptr<Task>& task : pData->m_taskList) {
		std::shared_ptr<UnitAgent> bestSuited = nullptr;
		float bestInterest = -1;
		for (auto& id_unitAgent_pair : pData->unitAgentsList) {
			auto& unitAgent = id_unitAgent_pair.second;

			if (unitAgent->getState() != UnitAgent::IDLING)
				continue;

			const float interest = unitAgent->computeInterest(task);

			if (!bestSuited || interest > bestInterest) {
				bestInterest = interest;
				bestSuited = unitAgent;
			}
		}

		if (bestSuited) {
			bestSuited->setTask(task);
			task->setExecutor(bestSuited);
		}
	}

	// Remove from the list tasks that have been attributed
	pData->m_taskList.erase(std::remove_if(pData->m_taskList.begin(), pData->m_taskList.end(), [](const std::shared_ptr<Task>& task) {
		return task->getExecutor() != nullptr;
		}), pData->m_taskList.end());
}




// Called when the bot starts!
void PMRBot::onStart()
{
	// Set our BWAPI options here    
	BWAPI::Broodwar->setLocalSpeed(LOCAL_SPEED);
	BWAPI::Broodwar->setFrameSkip(FRAME_SKIP);

	// Enable the flag that tells BWAPI top let users enter input while bot plays
	BWAPI::Broodwar->enableFlag(BWAPI::Flag::UserInput);

	// Call MapTools OnStart
	m_mapTools.onStart();

	pData->m_eventManagerTE->onStart();

}

// Called on each frame of the game
void PMRBot::onFrame()
{
	// Update our MapTools information
	m_mapTools.onFrame();

	pData->currMinerals = BWAPI::Broodwar->self()->minerals();
	pData->currSupply = Tools::GetUnusedSupply(true);


	// Run the bot Loop
	runBotLoop();


	// Draw unit health bars, which brood war unfortunately does not do
	Tools::DrawUnitHealthBars();

	// Draw some relevent information to the screen to help us debug the bot
	drawDebugInformation();

	pData->m_eventManagerTE->onFrame();
}

// Draw some relevent information to the screen to help us debug the bot
void PMRBot::drawDebugInformation()
{
	Tools::DrawUnitCommands();
	Tools::DrawUnitBoundingBoxes();
	pData->resourcesManager->drawDebugInformation();
}

// Called whenever the game ends and tells you if you won or not
void PMRBot::onEnd(bool isWinner)
{
	std::cout << "We " << (isWinner ? "won!" : "lost!") << "\n";

	pData->m_eventManagerTE->onEnd(isWinner);
}

// Called whenever a unit is destroyed, with a pointer to the unit
void PMRBot::onUnitDestroy(BWAPI::Unit unit)
{

	//Remove the UnitAgent affiliated.

	pData->m_eventManagerTE->onUnitDestroy(unit);
}

// Called whenever a unit is morphed, with a pointer to the unit
// Zerg units morph when they turn into other units
void PMRBot::onUnitMorph(BWAPI::Unit unit)
{
	pData->m_eventManagerTE->onUnitMorph(unit);
}

// Called whenever a text is sent to the game by a user
void PMRBot::onSendText(std::string text)
{
	if (text == "/map")
	{
		m_mapTools.toggleDraw();
	}

	pData->m_eventManagerTE->onSendText(text);
}

// Called whenever a unit is created, with a pointer to the destroyed unit
// Units are created in buildings like barracks before they are visible, 
// so this will trigger when you issue the build command for most units
void PMRBot::onUnitCreate(BWAPI::Unit unit)
{
	// SIMPLIFIED, WILL NEED TO ADD UNITAGENTTYPES...
	// std::shared_ptr<UnitAgent> pUnitAgent = std::make_shared<UnitAgent>();
	// unitAgentsList.insert(pUnitAgent);

	pData->m_eventManagerTE->onUnitCreate(unit);
}

// Called whenever a unit finished construction, with a pointer to the unit
void PMRBot::onUnitComplete(BWAPI::Unit unit)
{
	pData->m_eventManagerTE->onUnitComplete(unit);
}

// Called whenever a unit appears, with a pointer to the destroyed unit
// This is usually triggered when units appear from fog of war and become visible
void PMRBot::onUnitShow(BWAPI::Unit unit)
{
	pData->m_eventManagerTE->onUnitShow(unit);
}

// Called whenever a unit gets hidden, with a pointer to the destroyed unit
// This is usually triggered when units enter the fog of war and are no longer visible
void PMRBot::onUnitHide(BWAPI::Unit unit)
{
	pData->m_eventManagerTE->onUnitHide(unit);
}

// Called whenever a unit switches player control
// This usually happens when a dark archon takes control of a unit
void PMRBot::onUnitRenegade(BWAPI::Unit unit)
{
	pData->m_eventManagerTE->onUnitRenegade(unit);
}