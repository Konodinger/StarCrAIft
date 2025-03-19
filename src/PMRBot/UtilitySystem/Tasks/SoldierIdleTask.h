#pragma once
#include "Task.h"
class SoldierIdleTask :
    public Task
{
public:
    SoldierIdleTask(std::shared_ptr<TaskEmitter> taskEmitter);
};

