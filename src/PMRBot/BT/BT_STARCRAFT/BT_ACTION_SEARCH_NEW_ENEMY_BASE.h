#pragma once

#include <functional>
#include "BT_ACTION.h"
#include <ScoutTask.h>

class BT_ACTION_SEARCH_NEW_ENEMY_BASE : BT_ACTION
{
public:
	BT_ACTION_SEARCH_NEW_ENEMY_BASE(std::string name, BT_NODE* parent, ScoutTask* task, std::vector<BWAPI::TilePosition>* enemyBaseList);
private:
	State Evaluate(void* data) override;
	std::string GetDescription() override;

	ScoutTask* m_task;
	std::vector<BWAPI::TilePosition>* enemyBaseList;

	BT_NODE::State SearchEnemyBase(void* data);
};
	
