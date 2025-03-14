#pragma once

class TaskEmitter;

#include "Data.h"
#include "Task.h"

enum EmitterType {
	WORKER,
	EVENT,
	SCOUT,
	ARMY,
	TECHTREE,
};

class TaskEmitter {
public:
	void ExecuteTaskEmissionBT(Data *pData);
	void computeTaskReward();

	void emitTask(void* pData, std::shared_ptr<Task> task);

	void onTaskFinished(std::shared_ptr<Task> task);
	std::vector<std::shared_ptr<Task>> m_taskEmitted;
protected:
	TaskEmitter() {};
	std::string m_name{};
	BT_NODE* pTaskEmitterBT = nullptr;

};