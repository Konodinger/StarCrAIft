#include "ScoutTask.h"

ScoutTask::ScoutTask(int& enemyBasePosListSize) : Task("Scout") {
	m_taskBT = std::make_shared<BT_DECORATOR>(BT_DECORATOR("EntryPoint", nullptr));
	BT_NODE* pScoutMainSelector = new BT_SELECTOR("Scout", m_taskBT.get(), 2); // 2 children

	// Searching for enemy bases
	BT_NODE* pSearchEnemyBaseSequencer = new BT_SEQUENCER("Search for enemy base", pScoutMainSelector, 2);
	BT_NODE* pConditionNoEnemyBase = new BT_DECO_COND_LESSER_THAN("Is no known enemy base", pSearchEnemyBaseSequencer, 0, enemyBasePosListSize, false);
	// BT_NODE* pSearchForBase = new BT_ACTION_SEARCH_NEW_ENEMY_BASE // Search base action to implement (according to Miro)

	// Monitoring enemy base
	BT_NODE* pMonitorEnemyBaseSequencer = new BT_SEQUENCER("Monitor enemy base", pScoutMainSelector, 2);
	BT_NODE* pConditionEnemyBaseExists = new BT_DECO_COND_GREATER_THAN("Is known enemy base", pMonitorEnemyBaseSequencer, 0, enemyBasePosListSize, true);
	// BT_NODE* pMonitorExistingBase = new BT_ACTION_MONITOR_EXISTING_BASE // Monitor action to implement (according to Miro)

}