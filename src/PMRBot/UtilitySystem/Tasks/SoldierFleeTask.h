#pragma once
#include "Task.h"


/*
* Represent a task to be accomplished, specific to fleeing.
* Allow to compute the reward associated with completing it.
* Holds a Behaviour Tree that states how to accomplish the task.
*/
class SoldierFleeTask :
    public Task
{
public:
    SoldierFleeTask(std::shared_ptr<TaskEmitter> taskEmitter);
};

