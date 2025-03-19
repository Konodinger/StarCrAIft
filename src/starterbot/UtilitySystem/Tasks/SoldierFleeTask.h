#pragma once
#include "Task.h"
class SoldierFleeTask :
    public Task
{
public:
    SoldierFleeTask(std::shared_ptr<TaskEmitter> taskEmitter);
};

