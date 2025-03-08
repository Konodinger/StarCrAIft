#pragma once

class Task;

#include <string>
#include <assert.h>
#include <algorithm>
#include <memory>
#include <vector>
#include "TaskEmitter.h"

#include "../BT/BT.h"
#include "UnitAgent.h"

// À compléter pour chaque catégorie de tâche
enum TaskType
{
	BUILD,
	SCOUT,
	FLEE
};

class Task
{
public:
	Task() = delete;
	
	Task(std::string name)
		: m_name(name)
	{
		assert(count < std::UINT_MAX && "task id overflow : Tasks.h");
		m_id = count++;
	}

	bool isCompatible(UnitAgentType type) const { return (std::find(m_compatibility.begin(), m_compatibility.end(), type) != m_compatibility.end()); }

	// For now, we should not be able to replace the executor. It could be useful if the current executor died, but this should be checked before.
	bool setExecutor(std::shared_ptr<UnitAgent> executor) {
		assert(m_executor == nullptr && ("Can't set a new executor on task " + m_name + std::string(m_id)));
		m_executor = executor;
	}
	std::shared_ptr<UnitAgent> getExecutor() { return m_executor; }
	// Should be called only if the executor died.
	void removeExecutor() { m_executor = nullptr; }

	const std::shared_ptr<BT_NODE> getBT() { return m_taskBT; }
	void setBT(std::shared_ptr<BT_NODE> const bt) { m_taskBT = bt; }
	const std::string getName() { return m_name; }
	const std::shared_ptr<TaskEmitter> getTaskEmitter() { return m_taskEmitter; }

	bool ongoing() const;

	virtual float reward(/*pData*/) = 0;


private:
	static unsigned int count;

	std::string m_name{};
	unsigned int m_id = 0;

	float m_intrinsicReward = 0.f;

	std::vector<UnitAgentType> m_compatibility;
	std::shared_ptr<UnitAgent> m_executor = nullptr;
	std::shared_ptr<BT_NODE> m_taskBT = std::make_shared<BT_ACTION_EMPTY_BT>("Default task BT", nullptr);
	std::shared_ptr<TaskEmitter> m_taskEmitter = nullptr;

	// prérequis / 
};

