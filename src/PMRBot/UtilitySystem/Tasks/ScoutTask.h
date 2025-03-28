#pragma once
#include "Task.h"



/*
* Represent a task to be accomplished, specific to scouting.
* Allow to compute the reward associated with completing it.
* Holds a Behaviour Tree that states how to accomplish the task.
*/
class ScoutTask : public Task {
public:
	ScoutTask(std::shared_ptr<TaskEmitter> taskEmitter, std::vector<BWAPI::TilePosition>* enemyBaseList, std::shared_ptr<int> nbScoutsMonitoring);

};