#pragma once
#include "Task.h"


/*
* Represent a task to be accomplished, specific to workers fleeing.
* Allow to compute the reward associated with completing it.
* Holds a Behaviour Tree that states how to accomplish the task.
*/
class WorkerFleeTask :
    public Task
{
public:
    WorkerFleeTask(std::shared_ptr<TaskEmitter> taskEmitter);

    static bool isThereBase(void* data);
    static BT_NODE::State moveToNearestBase(void* data);

    static bool isArmyFleeing(void* data);
    static BT_NODE::State moveToNearestArmy(void* data);

    static BT_NODE::State makeNewBase(void* data);
};

