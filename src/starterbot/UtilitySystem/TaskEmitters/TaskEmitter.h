#pragma once

class TaskEmitter;

#include "Data.h"
#include "Task.h"

class TaskEmitter {
public:
	void ExecuteTaskEmissionBT(Data *pData);
	void computeTaskReward();

	void onTaskFinished(std::shared_ptr<Task> task);
protected:
	TaskEmitter() {};
	std::string m_name{};
	BT_NODE* pTaskEmitterBT = nullptr;
	std::vector<std::shared_ptr<Task>> m_taskEmitted; // bon il faudrait surement passer ça au sein de chaque sous classe plutôt car là tout est au même endroit (et en double en plus car il les faut aussi dans le pdata)
};