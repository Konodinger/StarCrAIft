#include "SoldierDefendBaseTask.h"
#include "BT_ACTION_ATTACK_CLOSEST_ENEMY.h"

SoldierDefendBaseTask::SoldierDefendBaseTask(std::shared_ptr<TaskEmitter> taskEmitter) : Task("Soldier Defend Base Task", taskEmitter) {
	
	m_compatibilityUnitType = { BWAPI::UnitTypes::Protoss_Photon_Cannon, 
			BWAPI::UnitTypes::Protoss_Dark_Archon,
			BWAPI::UnitTypes::Protoss_Dark_Templar,
			BWAPI::UnitTypes::Protoss_Dragoon,
			BWAPI::UnitTypes::Protoss_High_Templar,
			BWAPI::UnitTypes::Protoss_Reaver,
			BWAPI::UnitTypes::Protoss_Zealot,
			BWAPI::UnitTypes::Protoss_Arbiter,
			BWAPI::UnitTypes::Protoss_Carrier,
			BWAPI::UnitTypes::Protoss_Corsair,
			BWAPI::UnitTypes::Protoss_Interceptor,
			BWAPI::UnitTypes::Protoss_Scout };

	m_taskBT = std::make_shared<BT_DECORATOR>("Entry Point", nullptr);

	// Probably a problem here, I don't understand what it's supposed to do...
	BT_NODE* pRepeatUntilSeesEnemy = new BT_DECO_REPEATER("Repeat until sees enemy", m_taskBT.get(), 100, false, true, false); // => REPEATER TO CREATE

	BT_NODE* pAttackClosestEnemy = new BT_ACTION_ATTACK_CLOSEST_ENEMY("Attack closest enemy", pRepeatUntilSeesEnemy); // => ACTION TO CREATE
}