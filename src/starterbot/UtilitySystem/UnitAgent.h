	#pragma once

class UnitAgent;
enum UnitAgentType;
enum UnitAgentState;
class Data;

#include <memory>

#include "BWAPI/Unit.h"
#include "BT.h"
#include "Task.h"


enum UnitAgentState
{
	IDLING,
	//WAITINGFORSQUAD,
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
	UnitAgent(BWAPI::Unit unit, std::shared_ptr<BT_NODE> fleeingBT)
		: m_unit(unit), m_fleeingBT(fleeingBT)
	{ }

	BWAPI::Unit getUnit() { return m_unit; }
	UnitAgentState getState() const { return m_state; }

	const std::shared_ptr<BT_NODE> getIdlingBT() { return m_idlingBT; }
	void setIdlingBT(std::shared_ptr<BT_NODE> const bt) { m_idlingBT = bt; }

	// Called by [] in order to check if the unit is available
	virtual bool checkFlee(Data* pData) = 0;

	void execute(Data* pData);

	virtual float computeInterest(std::shared_ptr<Task> task /*pData*/) = 0;


private:
	bool m_isSquad = false;

	std::shared_ptr<BT_NODE> m_fleeingBT = std::make_shared<BT_ACTION_EMPTY_BT>("Default fleeing BT", nullptr);
	std::shared_ptr<BT_NODE> m_idlingBT = std::make_shared<BT_ACTION_EMPTY_BT>("Default idling BT", nullptr);

	BWAPI::Unit m_unit;
	std::vector<BWAPI::Unit> m_squadUnit;
	std::shared_ptr<Task> m_task;

	UnitAgentType m_type;
	UnitAgentState m_state;


};

