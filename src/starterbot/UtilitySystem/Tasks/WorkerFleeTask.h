#pragma once
#include "Task.h"
class WorkerFleeTask :
    public Task
{
public:
    WorkerFleeTask(std::shared_ptr<TaskEmitter> taskEmitter);
};

