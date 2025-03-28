#pragma once

#include <functional>
#include "BT_ACTION.h"
#include <BWAPI.h>

class Task;

class BT_ACTION_MONITOR_EXISTING_BASE : public BT_ACTION
{
public:
	BT_ACTION_MONITOR_EXISTING_BASE(std::string name, BT_NODE* parent, std::shared_ptr<int> nbScouts, std::vector<BWAPI::TilePosition>* enemyBaseList, Task* task);

private:
	State Evaluate(void* data) override;
	std::string GetDescription() override;

	BT_NODE::State MonitorEnemyBase(void* data);

	std::shared_ptr<int> nbScouts;
	std::vector<BWAPI::TilePosition>* enemyBaseList;
	Task* taskPtr;
};

