#pragma once
#include "Task.h"


/*
* Represent a task to be accomplished, specific to the soldier's default behaviour.
* Allow to compute the reward associated with completing it.
* Holds a Behaviour Tree that states how to accomplish the task.
*/
class SoldierIdleTask :
    public Task
{
public:
    SoldierIdleTask(std::shared_ptr<TaskEmitter> taskEmitter);
};

