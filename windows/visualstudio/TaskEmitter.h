#pragma once

#include "Data.h"
#include "Task.h"

class TaskEmitter {
public:
	void ExecuteTaskEmissionBT(Data *pData);
	void computeTaskReward();
protected:
	TaskEmitter() {};
	BT_NODE* pTaskEmitterBT;
	std::vector<std::shared_ptr<Task>> m_taskEmitted;
};