#pragma once

class Task;

#include <string>
#include <assert.h>
#include <algorithm>
#include <memory>
#include <vector>

#include "UnitAgent.h"

enum TaskType
{
	BUILD,

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

	bool setExecutor(std::shared_ptr<UnitAgent> executor) { m_executor = executor; }
	std::shared_ptr<UnitAgent> getExecutor() { return m_executor; }


	bool ongoing() const;

	virtual float reward(/*pData*/) = 0;


private:
	static unsigned int count;

	std::string m_name{};
	unsigned int m_id = 0;

	float m_intrinsicReward = 0.f;

	std::vector<UnitAgentType> m_compatibility;
	std::shared_ptr<UnitAgent> m_executor = nullptr;

	// prérequis / 




};

