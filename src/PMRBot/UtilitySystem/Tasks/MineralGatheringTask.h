#pragma once
#include "Task.h"
#include "TaskEmitter.h"
#include <memory>

class MineralGatheringTask: public Task {
public:
	MineralGatheringTask (std::shared_ptr<TaskEmitter> taskEmitter);

	static BT_NODE::State gatherNearestMineral(void* pData, MineralGatheringTask* task);

};

