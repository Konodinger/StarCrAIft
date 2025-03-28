#pragma once
#include "Task.h"


/*
* Represent a task to be accomplished, specific to creating workers.
* Allow to compute the reward associated with completing it.
* Holds a Behaviour Tree that states how to accomplish the task.
*/
class CreateWorkerTask : public Task {
public:
	CreateWorkerTask(std::shared_ptr<TaskEmitter> taskEmitter);

	static BT_NODE::State trainWorker(void* pData, CreateWorkerTask* task);

};
