#include "SoldierDefendBaseTask.h"

SoldierDefendBaseTask::SoldierDefendBaseTask() : Task("Soldier Defend Base Task") {
	m_taskBT = std::make_shared<BT_NODE>(BT_DECORATOR("Entry Point", nullptr));

	BT_NODE* pRepeatUntilSeesEnemy = new BT_REPEATER_UNTIL_SEES_ENEMY("Repeat until sees enemy", m_taskBT.get(), ...); // => REPEATER TO CREATE

	BT_NODE* pAttackClosestEnemy = new BT_ACTION_ATTACK_CLOSEST_ENEMY("Attack closest enemy", pRepeatUntilSeesEnemy, ...); // => ACTION TO CREATE
}