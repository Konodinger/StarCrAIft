#pragma once

#include <functional>
#include <BWAPI.h>
#include "BT_ACTION.h"

class Task;

class BT_ACTION_SEARCH_NEW_ENEMY_BASE : public BT_ACTION
{
public:
	BT_ACTION_SEARCH_NEW_ENEMY_BASE(std::string name, BT_NODE* parent, Task* task, std::vector<BWAPI::TilePosition>* enemyBaseList);
private:
	State Evaluate(void* data) override;
	std::string GetDescription() override;

	std::shared_ptr<Task> taskPtr;
	std::vector<BWAPI::TilePosition>* enemyBaseList;

	BT_NODE::State SearchEnemyBase(void* data);
};
	
