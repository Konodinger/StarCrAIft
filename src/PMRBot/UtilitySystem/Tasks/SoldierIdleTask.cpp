#include "SoldierIdleTask.h"

SoldierIdleTask::SoldierIdleTask(std::shared_ptr<TaskEmitter> taskEmitter) : Task("Soldier Idle Task", taskEmitter) {
	
	m_compatibilityUnitAgentType = { UnitAgent::GROUNDMOBILE, UnitAgent::FLYINGMOBILE };

	m_taskBT = std::make_shared<BT_DECORATOR>(BT_DECORATOR("Entry Point", nullptr));

	BT_NODE* pSoldierIdleSelector = new BT_SELECTOR("Soldier Idle", m_taskBT.get(), 2);

	//BT_NODE* pRegroupSequencer = new BT_SEQUENCER("Regroup", pSoldierIdleSelector, 2);
	//BT_NODE* pIsPreparingArmy = new BT_DECO_COND_IS_PREPARING_ARMY("Is preparing army ?", pRegroupSequencer, ...); // => CONDITION TO CREATE
	//BT_NODE* pMoveToRegroupPosition = new BT_ACTION_MOVE_TO_REGROUP_POSITION("Move to regroup position", pRegroupSequencer, ...); // => ACTION TO CREATE

	//BT_NODE* pPatrolSelector = new BT_SELECTOR("Patrol selector", pSoldierIdleSelector, 2);
	//
	//BT_NODE* pBaseAttackedSequencer = new BT_SEQUENCER("Base attacked sequencer", pPatrolSelector, 2);
	//BT_NODE* pCondSeesEnemy = new BT_DECO_COND_SEES_ENEMY("Sees enemy condition", pBaseAttackedSequencer, ...); // => CONDITION TO CREATE (also in attack base task)
	//BT_NODE* pInformEnemyAttacks = new BT_ACTION_INFORM_ENEMY_ATTACKS("Inform that enemy attacks the base", pBaseAttackedSequencer, ...); // => ACTION TO CREATE

	//BT_NODE* pPatrolAction = new BT_ACTION_PATROL("Patrol in the surroundings", pPatrolSelector, ...); // => ACTION TO CREATE
}