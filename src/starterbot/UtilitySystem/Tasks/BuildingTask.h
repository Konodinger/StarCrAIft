#pragma once
#include "Task.h"

class BuildingTask :
    public Task
{
public:
    BuildingTask(std::shared_ptr<TaskEmitter> taskEmitter);
};

