#include "TaskEmitter.h"

#include "Data.h"


void TaskEmitter::ExecuteTaskEmissionBT(Data* pData) {
	if (pTaskEmitterBT == nullptr) {
		BWAPI::Broodwar->printf(("Warning: the task emitter " + m_name + " doesn't have a behaviour tree associated...").c_str());
		return;
	}
	if (pTaskEmitterBT->Evaluate(pData) == BT_NODE::FAILURE)
	{
		BWAPI::Broodwar->printf(("Warning: the task emitter " + m_name + " ended incorrectly...").c_str());
	}
}

void TaskEmitter::onTaskFinished(std::shared_ptr<Task> task) {
	auto taskPos = std::find(m_taskEmitted.begin(), m_taskEmitted.end(), task);
	if (taskPos == m_taskEmitted.end()) {
		BWAPI::Broodwar->printf(("Warning: the task emitter " + m_name + " received a notification of the finished task " + task->getName() + ", but is not responsible for this task...").c_str());
	}
	else {
		m_taskEmitted.erase(taskPos);
	}
}

void TaskEmitter::computeTaskReward() {
	for (auto task : m_taskEmitted) {
		task->reward();
	}
}

void TaskEmitter::emitTask(void* pData, std::shared_ptr<Task> task)
{
	Data* data = static_cast<Data*>(pData);
	m_taskEmitted.push_back(task);
	data->m_taskList.push_back(task);
}
