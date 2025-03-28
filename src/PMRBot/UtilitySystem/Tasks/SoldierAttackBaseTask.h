#pragma once
#include "Task.h"


/*
* Represent a task to be accomplished, specific to attacking.
* Allow to compute the reward associated with completing it.
* Holds a Behaviour Tree that states how to accomplish the task.
*/
class SoldierAttackBaseTask :
    public Task
{
public:
    SoldierAttackBaseTask(std::shared_ptr<TaskEmitter> taskEmitter);
};

