#pragma once

#include "Data.h"
#include "Task.h"

class TaskEmitter {
public:
	void ExecuteTaskEmissionBT(Data *pData);
	void computeTaskReward();
protected:
	TaskEmitter() {};
	std::string m_name{};
	BT_NODE* pTaskEmitterBT = nullptr;
	std::vector<std::shared_ptr<Task>> m_taskEmitted;
};