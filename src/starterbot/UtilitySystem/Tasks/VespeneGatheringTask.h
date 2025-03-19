#pragma once
#include "Task.h"

class VespeneGatheringTask : public Task {
public:
	VespeneGatheringTask(std::shared_ptr<TaskEmitter> taskEmitter);

	static BT_NODE::State gatherNearestVespene(void* pData, VespeneGatheringTask* task);

};

