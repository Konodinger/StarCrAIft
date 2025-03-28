#pragma once
#include "Task.h"



/*
* Represent a task to be accomplished, specific to gathering gas.
* Allow to compute the reward associated with completing it.
* Holds a Behaviour Tree that states how to accomplish the task.
*/
class VespeneGatheringTask : public Task {
public:
	VespeneGatheringTask(std::shared_ptr<TaskEmitter> taskEmitter);

	static BT_NODE::State gatherNearestVespene(void* pData, VespeneGatheringTask* task);

};

