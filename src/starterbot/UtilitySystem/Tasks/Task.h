#pragma once

class Task;

#include <string>
#include "assert.h"
#include <algorithm>
#include <memory>
#include <vector>
#include "TaskEmitter.h"

#include "BT.h"
#include "UnitAgent.h"

class TaskEmitter;

class Task
{
public:
	// � compl�ter pour chaque cat�gorie de t�che
	enum TaskType
	{
		BUILD,
		SCOUT,
		FLEE
	};

	Task() = delete;

	Task(std::string name)
		: m_name(name)
	{
		assert(count < UINT_MAX && "task id overflow : Tasks.h");
		m_id = count++;
	}

	bool isCompatible(std::shared_ptr<UnitAgent> unitAgent) const {
		if (m_compatibilityUnitType.size() != 0)
			return (std::find(m_compatibilityUnitType.begin(), m_compatibilityUnitType.end(), unitAgent->getUnit()->getType()) != m_compatibilityUnitType.end());
		if (m_compatibilityUnitAgentType.size() != 0)
			return (std::find(m_compatibilityUnitAgentType.begin(), m_compatibilityUnitAgentType.end(), unitAgent->getType()) != m_compatibilityUnitAgentType.end());
		return true;
	}

	// For now, we should not be able to replace the executor. It could be useful if the current executor died, but this should be checked before.
	bool setExecutor(std::shared_ptr<UnitAgent> executor) {
		assert(m_executor == nullptr && ("Can't set a new executor on task " + m_name + std::to_string(m_id)).c_str());
		m_executor = executor;

		return true;
	}
	std::shared_ptr<UnitAgent> getExecutor() { return m_executor; }
	// Should be called only if the executor died.
	void removeExecutor() { m_executor = nullptr; }

	const std::shared_ptr<BT_NODE> getBT() { return m_taskBT; }
	void setBT(std::shared_ptr<BT_NODE> const bt) { m_taskBT = bt; }
	const std::string getName() { return m_name; }
	const std::shared_ptr<TaskEmitter> getTaskEmitter() { return m_taskEmitter; }

	bool ongoing() const;

	float reward(/*pData*/) { return 0.f; };


protected:
	static unsigned int count;

	std::string m_name{};
	unsigned int m_id = 0;

	float m_intrinsicReward = 0.f;

	std::vector<BWAPI::UnitType> m_compatibilityUnitType;
	std::vector<UnitAgent::UnitAgentType> m_compatibilityUnitAgentType;
	std::shared_ptr<UnitAgent> m_executor = nullptr;
	std::shared_ptr<BT_NODE> m_taskBT = std::make_shared<BT_ACTION_EMPTY_BT>("Default task BT", nullptr);
	std::shared_ptr<TaskEmitter> m_taskEmitter = nullptr;

	// pr�requis / 
};

