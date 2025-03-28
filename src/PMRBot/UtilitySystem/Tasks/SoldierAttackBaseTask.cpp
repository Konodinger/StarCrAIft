#include "SoldierAttackBaseTask.h"

#include "BT_ACTION_EXECUTE_METHOD.h"

SoldierAttackBaseTask::SoldierAttackBaseTask(std::shared_ptr<TaskEmitter> taskEmitter) : Task("Soldier Attack Base Task", taskEmitter) {
	
	m_compatibilityUnitAgentType = { UnitAgent::GROUNDMOBILE, UnitAgent::FLYINGMOBILE };

	m_taskBT = std::make_shared<BT_DECORATOR>("Entry Point", nullptr);

	BT_NODE* pAttackBaseMainSelector = new BT_SELECTOR("Attack base sequencer", m_taskBT.get(), 6);

	BT_NODE* pMoveToPos = new BT_ACTION_EXECUTE_METHOD("Move to pos", pAttackBaseMainSelector, moveToPosition); // => ACTION TO CREATE

	BT_NODE* pAttackEnemySoldiersSequencer = new BT_SEQUENCER("Attack enemy soldiers sequencer", pAttackBaseMainSelector, 2); // => ACTION TO CREATE
	BT_NODE* pCondSeesEnemy = new BT_DECO_CONDITION("Sees enemy condition", pAttackEnemySoldiersSequencer, areEnemyInSight); // => CONDITION TO CREATE (also in idle task)
	BT_NODE* pAttackSoldierAction = new BT_ACTION_EXECUTE_METHOD("Attack seen enemy", pAttackEnemySoldiersSequencer, attackSeenEnemy); // => CREATE ACTION

	BT_NODE* pAttackDefendingBuildingsSequencer = new BT_SEQUENCER("Attack defending buildings sequencer", pAttackBaseMainSelector, 2);
	BT_NODE* pCondSeesDefendingBuildings = new BT_DECO_CONDITION("Sees defending building condition", pAttackDefendingBuildingsSequencer, areDefensiveBuildingsInSight); // => CONDITION TO CREATE
	BT_NODE* pAttackDefendingBuildingsAction = new BT_ACTION_EXECUTE_METHOD("Attack defending building", pAttackDefendingBuildingsSequencer, attackDefensiveBuildings); // => ACTION TO CREATE

	BT_NODE* pAttackSupplyProvidersSequencer = new BT_SEQUENCER("Attack supply providers sequencer", pAttackBaseMainSelector, 2);
	BT_NODE* pSeesSupplyProviders = new BT_DECO_CONDITION("Sees suply provider condition", pAttackSupplyProvidersSequencer, areSupplyProviderInSight); // => CONDITION TO CREATE
	BT_NODE* pAttackSupplyProviderAction = new BT_ACTION_EXECUTE_METHOD("Attack supply provider", pAttackSupplyProvidersSequencer, attackSupplyProvider); // => ACTION TO CREATE

	BT_NODE* pAttackWorkersOrStocksSequencer = new BT_SEQUENCER("Attack worker or ressource stocks", pAttackBaseMainSelector, 2);
	BT_NODE* pCondSeesWorkersOrStocks = new BT_DECO_CONDITION("Sees workers or ressources stock condition", pAttackWorkersOrStocksSequencer, areWorkerOrRessourceStocksInSight); // => CONDITION TO CREATE
	BT_NODE* pAttackWorkerOrStockAction = new BT_ACTION_EXECUTE_METHOD("Attack wortker or ressource stock", pAttackWorkersOrStocksSequencer, attackWorkerOrStocksInSight); // => CREATE ACTION

	BT_NODE* pAttackOther = new BT_ACTION_EXECUTE_METHOD("Attack something else", pAttackBaseMainSelector, attackAll); // => CREATE ACTION to attack soemthing else
}

BT_NODE::State SoldierAttackBaseTask::moveToPosition(void* data)
{
	Data* pData = (Data*)data;

	// TODO
	// 
	//

	return BT_NODE::State::SUCCESS;
}

bool SoldierAttackBaseTask::areEnemyInSight(void* data)
{
	Data* pData = (Data*)data;

	// TODO
	// 
	//

	return true;
}

BT_NODE::State SoldierAttackBaseTask::attackSeenEnemy(void* data)
{
	Data* pData = (Data*)data;

	// TODO
	// 
	//

	return BT_NODE::State::SUCCESS;
}

bool SoldierAttackBaseTask::areDefensiveBuildingsInSight(void* data)
{
	Data* pData = (Data*)data;

	// TODO
	// 
	//

	return true;
}

BT_NODE::State SoldierAttackBaseTask::attackDefensiveBuildings(void* data)
{
	Data* pData = (Data*)data;

	// TODO
	// 
	//

	return BT_NODE::State::SUCCESS;
}

bool SoldierAttackBaseTask::areSupplyProviderInSight(void* data)
{
	Data* pData = (Data*)data;

	// TODO
	// 
	//

	return true;
}

BT_NODE::State SoldierAttackBaseTask::attackSupplyProvider(void* data)
{
	Data* pData = (Data*)data;

	// TODO
	// 
	//

	return BT_NODE::State::SUCCESS;
}

bool SoldierAttackBaseTask::areWorkerOrRessourceStocksInSight(void* data)
{
	Data* pData = (Data*)data;

	// TODO
	// 
	//

	return true;
}

BT_NODE::State SoldierAttackBaseTask::attackWorkerOrStocksInSight(void* data)
{
	Data* pData = (Data*)data;

	// TODO
	// 
	//

	return BT_NODE::State::SUCCESS;
}

BT_NODE::State SoldierAttackBaseTask::attackAll(void* data)
{
	Data* pData = (Data*)data;

	// TODO
	// 
	//

	return BT_NODE::State::SUCCESS;
}
