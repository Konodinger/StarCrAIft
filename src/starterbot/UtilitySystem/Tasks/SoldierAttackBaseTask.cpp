#include "SoldierAttackBaseTask.h"

SoldierAttackBaseTask::SoldierAttackBaseTask() : Task("Soldier Attack Base Task") {
	m_taskBT = std::make_shared<BT_NODE>(BT_DECORATOR("Entry Point", nullptr));

	BT_NODE* pAttackBaseMainSelector = new BT_SELECTOR("Attack base sequencer", m_taskBT.get(), 6);

	BT_NODE* pMoveToPos = new BT_ACTION_MOVE_TO_POS("Move to pos", pAttackBaseMainSelector, ...); // => ACTION TO CREATE

	BT_NODE* pAttackEnemySoldiersSequencer = new BT_SEQUENCER("Attack enemy soldiers sequencer", pAttackBaseMainSelector, 2); // => ACTION TO CREATE
	BT_NODE* pCondSeesEnemy = new BT_DECO_COND_SEES_ENEMY("Sees enemy condition", pAttackEnemySoldiersSequencer, ...); // => CONDITION TO CREATE (also in idle task)
	BT_NODE* pAttackSoldierAction = new BT_ACTION_ATTACK_ENEMY("Attack seen enemy", pAttackEnemySoldiersSequencer, ...); // => CREATE ACTION

	BT_NODE* pAttackDefendingBuildingsSequencer = new BT_SEQUENCER("Attack defending buildings sequencer", pAttackBaseMainSelector, 2);
	BT_NODE* pCondSeesDefendingBuildings = new BT_DECO_COND_SEES_DEFENDING_BUILDING("Sees defending building condition", pAttackDefendingBuildingsSequencer, ...); // => CONDITION TO CREATE
	BT_NODE* pAttackDefendingBuildingsAction = new BT_ACTION_ATTACK_DEFENDING_BUILDING("Attack defending building", pAttackDefendingBuildingsSequencer, ...); // => ACTION TO CREATE

	BT_NODE* pAttackSupplyProvidersSequencer = new BT_SEQUENCER("Attack supply providers sequencer", pAttackBaseMainSelector, 2);
	BT_NODE* pSeesSupplyProviders = new BT_DECO_COND_SEES_SUPPLY_PROVIDER("Sees suply provider condition", pAttackSupplyProvidersSequencer, ...); // => CONDITION TO CREATE
	BT_NODE* pAttackSupplyProviderAction = new BT_ACTION_ATTACK_SUPPLY_PROVIDER("Attack supply provider", pAttackSupplyProvidersSequencer, ...); // => ACTION TO CREATE

	BT_NODE* pAttackWorkersOrStocksSequencer = new BT_SEQUENCER("Attack worker or ressource stocks", pAttackBaseMainSelector, 2);
	BT_NODE* pCondSeesWorkersOrStocks = new BT_DECO_COND_SEES_WORKERS_OR_STOCKS("Sees workers or ressources stock condition", pAttackWorkersOrStocksSequencer, ...); // => CONDITION TO CREATE
	BT_NODE* pAttackWorkerOrStockAction = new BT_ACTION_ATTACK_WORKER_OR_STOCK("Attack wortker or ressource stock", pAttackWorkersOrStocksSequencer, ...); // => CREATE ACTION

	BT_NODE* pAttackOther = new BT_ACTION_ATTACK_OTHER("Attack something else", pAttackBaseMainSelector, ...); // => CREATE ACTION to attack soemthing else
}