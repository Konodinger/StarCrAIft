#pragma once
#include "Task.h"

class MineralGatheringTask : public Task {
public:
	MineralGatheringTask();

	static BT_NODE::State gatherNearestMineral(void* pData, std::shared_ptr<UnitAgent> unitAgent);

};

