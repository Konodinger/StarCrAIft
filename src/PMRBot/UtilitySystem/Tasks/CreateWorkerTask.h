#pragma once
#include "Task.h"

class CreateWorkerTask : public Task {
public:
	CreateWorkerTask(std::shared_ptr<TaskEmitter> taskEmitter);

	static BT_NODE::State trainWorker(void* pData, CreateWorkerTask* task);

};
