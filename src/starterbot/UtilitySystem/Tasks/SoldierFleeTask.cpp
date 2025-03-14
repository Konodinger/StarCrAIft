#include "SoldierFleeTask.h"

SoldierFleeTask::SoldierFleeTask() : Task("Soldier Flee Task") {
	
	m_compatibilityUnitAgentType = { UnitAgent::GROUNDMOBILE, UnitAgent::FLYINGMOBILE };

	m_taskBT = std::make_shared<BT_DECORATOR>(BT_DECORATOR("Entry Point", nullptr));

	BT_NODE* pFleeMainSelector = new BT_SELECTOR("Flee selector", m_taskBT.get(), 2);

	//BT_NODE* pFleeToNearestArmySequencer = new BT_SEQUENCER("Flee to nearest army", pFleeMainSelector, 2);
	//BT_NODE* pIsArmyNotFleeing = new BT_DECO_COND_ARMY_NOT_FLEEING("Is army not fleeing", pFleeToNearestArmySequencer, ...); // => CONDITION TO CREATE
	//BT_NODE* pMoveToNearestArmy = new BT_ACTION_MOVE_TO_NEAREST_ARMY("Move to nearest army", pFleeToNearestArmySequencer, ...); // => ACTION TO CREATE

	//BT_NODE* pFleeToNearestBaseSequencer = new BT_SEQUENCER("Flee to nearest base", pFleeMainSelector, 2);
	//BT_NODE* pConditionIsBase = new BT_DECO_COND_IS_BASE("", pFleeToNearestBaseSequencer, ...); // => CONDITION TO CREATE
	//BT_NODE* pMoveToNearestBase = new BT_ACTION_MOVE_TO_NEAREST_BASE("Move to nearest base", pFleeToNearestBaseSequencer, ...); // => ACTION TO CREATE
}
