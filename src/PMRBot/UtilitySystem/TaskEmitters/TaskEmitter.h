#pragma once

#include <vector>
#include <memory>
#include <string>

#include "BT.h"

class Task;
class Data;

enum class EmitterType {
	WORKER,
	EVENT,
	SCOUT,
	ARMY,
	TECHTREE,
	BUILDORDER
};

class TaskEmitter {
public:
	TaskEmitter() = default;

	virtual void ExecuteTaskEmissionBT(Data* pData);
	void computeTaskReward();

	void emitTask(void* pData, std::shared_ptr<Task> task);

	void onTaskFinished(std::shared_ptr<Task> task);
	std::vector<std::shared_ptr<Task>> m_taskEmitted;
protected:
	std::string m_name{};
	BT_NODE* pTaskEmitterBT = nullptr;

};