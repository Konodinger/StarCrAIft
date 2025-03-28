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
	BUILDORDER,
	UNITPRODUCER,
};


/**
* Generic class for Task Emitters.
* Uses a Behaviour Tree and the data stored on the Blackboard to emit tasks.
*/
class TaskEmitter {
public:
	TaskEmitter() = default;

	/*
		Execute the Behaviour Tree.
		@param pData pointer to the Data blackboard
	*/
	virtual void ExecuteTaskEmissionBT(Data* pData);

	/*
		Returns the reward associated with the task.
	*/
	void computeTaskReward();

	/*
		Add a Task to the list.
	*/
	void emitTask(void* pData, std::shared_ptr<Task> task);

	/*
		Is called when a Task has been accomplished, in order to remove it from the list and potentially emit a new one.
	*/
	void onTaskFinished(std::shared_ptr<Task> task);

	std::vector<std::shared_ptr<Task>> m_taskEmitted; // stores the list of currently emitted tasks.

protected:
	std::string m_name{};
	BT_NODE* pTaskEmitterBT = nullptr;

};