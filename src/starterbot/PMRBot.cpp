#include "PMRBot.h"
#include "Tools.h"
#include "Data.h"

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

    pIdleManagerBT = new BT_ACTION_IDLE("IDLEManagerRoot", nullptr);

    m_EventTE.setData(pData);
}

void PMRBot::runBotLoop() {
    m_WorkerTE.ExecuteTaskEmissionBT(pData);
    // Same for other TE...


    m_WorkerTE.computeTaskReward();
    // Same for other TE...
    // 

    // Attribute IDLE behaviour
    if (pIdleManagerBT != nullptr && pIdleManagerBT->Evaluate(pData) != BT_NODE::SUCCESS)
    {
        BWAPI::Broodwar->printf("Warning: the IDLE Manager ended incorrectly...");
    }

    // Check if units should flee and compute their interest in available tasks.
    for (auto unitAgent : pData->unitAgentsList) {
        unitAgent->checkFlee(pData);
        if (unitAgent->getState() == UnitAgentState::IDLING) {
            for (auto task : pData->m_taskList)
                m_taskToAgentInterest[task][unitAgent] = unitAgent->computeInterest(task);
        }
        else {
            for (auto task : pData->m_taskList) {
                m_taskToAgentInterest[task].erase(unitAgent);
            }
        }
    }

    // Attribute tasks to agents
    taskAttribuer();

    // Execute agents behaviour tree
    for (auto unitAgent : pData->unitAgentsList) {
        unitAgent->executeBehaviorTree();
    }
}

void PMRBot::taskAttribuer() {
    //TODO
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

    m_EventTE.onStart();

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

    m_EventTE.onFrame();
}

// Draw some relevent information to the screen to help us debug the bot
void PMRBot::drawDebugInformation()
{
    Tools::DrawUnitCommands();
    Tools::DrawUnitBoundingBoxes();
}

// Called whenever the game ends and tells you if you won or not
void PMRBot::onEnd(bool isWinner)
{
    std::cout << "We " << (isWinner ? "won!" : "lost!") << "\n";

    m_EventTE.onEnd(isWinner);
}

// Called whenever a unit is destroyed, with a pointer to the unit
void PMRBot::onUnitDestroy(BWAPI::Unit unit)
{

    //Remove the UnitAgent affiliated.

    m_EventTE.onUnitDestroy(unit);
}

// Called whenever a unit is morphed, with a pointer to the unit
// Zerg units morph when they turn into other units
void PMRBot::onUnitMorph(BWAPI::Unit unit)
{
    m_EventTE.onUnitMorph(unit);
}

// Called whenever a text is sent to the game by a user
void PMRBot::onSendText(std::string text)
{
    if (text == "/map")
    {
        m_mapTools.toggleDraw();
    }

    m_EventTE.onSendText(text);
}

// Called whenever a unit is created, with a pointer to the destroyed unit
// Units are created in buildings like barracks before they are visible, 
// so this will trigger when you issue the build command for most units
void PMRBot::onUnitCreate(BWAPI::Unit unit)
{
    // SIMPLIFIED, WILL NEED TO ADD UNITAGENTTYPES...
    // std::shared_ptr<UnitAgent> pUnitAgent = std::make_shared<UnitAgent>();
    // unitAgentsList.insert(pUnitAgent);

    m_EventTE.onUnitCreate(unit);
}

// Called whenever a unit finished construction, with a pointer to the unit
void PMRBot::onUnitComplete(BWAPI::Unit unit)
{
    m_EventTE.onUnitComplete(unit);
}

// Called whenever a unit appears, with a pointer to the destroyed unit
// This is usually triggered when units appear from fog of war and become visible
void PMRBot::onUnitShow(BWAPI::Unit unit)
{
    m_EventTE.onUnitShow(unit);
}

// Called whenever a unit gets hidden, with a pointer to the destroyed unit
// This is usually triggered when units enter the fog of war and are no longer visible
void PMRBot::onUnitHide(BWAPI::Unit unit)
{
    m_EventTE.onUnitHide(unit);
}

// Called whenever a unit switches player control
// This usually happens when a dark archon takes control of a unit
void PMRBot::onUnitRenegade(BWAPI::Unit unit)
{
    m_EventTE.onUnitRenegade(unit);
}