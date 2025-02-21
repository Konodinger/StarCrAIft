#pragma once

class UnitAgent;
enum UnitAgentType;
enum UnitAgentState;

#include <memory>

#include "BWAPI/Unit.h"
#include "BT.h"
#include "Task.h"


enum UnitAgentState
{
	IDLING,
	WORKING,
	FLEEING
};

enum UnitAgentType
{
	WORKER,
	// à compléter
};

class UnitAgent
{
public:
	UnitAgent() = delete;
	UnitAgent(std::shared_ptr<BWAPI::Unit> unit, std::shared_ptr<BT_NODE> bt)
		: m_unit(unit), m_bt(bt)
	{ }

	std::shared_ptr<BWAPI::Unit> getUnit() { return m_unit; }
	UnitAgentState getState() const { return m_state; }

	// Called by [] in order to check if the unit is available
	virtual void checkFlee() = 0;

	virtual void executeBehaviorTree() = 0;

	virtual float computeInterest(std::shared_ptr<Task> task /*pData*/) = 0;


private:
	bool m_isSquad = false;

	std::shared_ptr<BT_NODE> m_bt;

	std::shared_ptr<BWAPI::Unit> m_unit;
	std::vector<std::shared_ptr<BWAPI::Unit>> m_squadUnit;
	
	UnitAgentType m_type;
	UnitAgentState m_state;


};

