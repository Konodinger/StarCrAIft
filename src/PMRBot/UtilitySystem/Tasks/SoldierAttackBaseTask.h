#pragma once
#include "Task.h"
class SoldierAttackBaseTask :
    public Task
{
public:
    SoldierAttackBaseTask(std::shared_ptr<TaskEmitter> taskEmitter);
};

