#pragma once
#include "Task.h"

class MineralGatheringTaskIdle : public Task {
public:
	MineralGatheringTaskIdle(std::shared_ptr<TaskEmitter> taskEmitter);

	static BT_NODE::State gatherNearestMineral(void* pData, MineralGatheringTaskIdle* task);

};

