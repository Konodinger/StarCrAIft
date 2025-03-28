#pragma once
#include "Task.h"

class ScoutTask : public Task {
public:
	ScoutTask(std::shared_ptr<TaskEmitter> taskEmitter);

private:
	std::vector<BWAPI::TilePosition>* enemyBaseList;

};