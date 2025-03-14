#pragma once
#include "Task.h"

class VespeneGatheringTask : public Task {
public:
	VespeneGatheringTask();

	static BT_NODE::State gatherNearestVespene(void* pData, std::shared_ptr<UnitAgent> unitAgent);

};

