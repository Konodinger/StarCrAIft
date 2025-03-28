#pragma once

class UnitAgent;
enum UnitAgentType;
enum UnitAgentState;
class Data;
class Task;

#include <memory>

#include "BWAPI/Unit.h"
#include "BT.h"
#include <set>



/* 
*	Generic class that wraps around BWAPI::Unit.
*	Holds a reference to the current Task associated with it.
*	May also wraps around multiple units in order to form a squad.
*/
class UnitAgent
{
public:

	enum UnitAgentType
	{
		WORKER,
		OBSERVER,
		GROUNDMOBILE,
		FLYINGMOBILE,
		BUILDING,
		NONE_TYPE
	};

	enum UnitAgentState
	{
		IDLING,
		//WAITINGFORSQUAD,
		WORKING,
		FLEEING
	};

	UnitAgent() = delete;
	explicit UnitAgent(BWAPI::Unit unit)
		: m_unit(unit)
	{
	}

	UnitAgent(BWAPI::Unit unit, std::shared_ptr<BT_NODE> fleeingBT)
		: m_unit(unit), m_fleeingBT(fleeingBT)
	{
	}

	BWAPI::Unit getUnit() const { return m_unit; }
	UnitAgentState getState() const { return m_state; }
	UnitAgentType getType() const { return m_type; }

	/*
		
	*/
	virtual bool checkFlee(Data* pData) = 0;

	/*
	* Execute the Behaviour Tree of the unit.
	* @param pData pointer to the Data Blackboard. Needed for some of the BT nodes.
	*/
	void execute(Data* pData);

	/*
	* Computes the interest of this unit for a specific task, in order to decide tasks assignement.
	* @param task shared_ptr to the Task.
	*/
	virtual float computeInterest(std::shared_ptr<Task> task /*pData*/) = 0;

	virtual void drawDebug() = 0;

	/*
	* Assign a Task to the unit.
	* @param task shared_ptr to the Task.
	*/
	void setTask(std::shared_ptr<Task> task) {
		m_state = UnitAgentState::WORKING;
		m_task = task;
	}
public:
	// Create a UnitAgent from a BWAPI::Unit using the correct class
	static std::shared_ptr<UnitAgent> createUnitAgent(BWAPI::Unit unit);

private:
	bool m_isSquad = false;

	std::shared_ptr<BT_NODE> m_fleeingBT = std::make_shared<BT_ACTION_EMPTY_BT>("Default fleeing BT", nullptr);

	BWAPI::Unit m_unit;
	std::vector<BWAPI::Unit> m_squadUnit;
	std::shared_ptr<Task> m_task;

	UnitAgentType m_type;
	UnitAgentState m_state = IDLING;

private:
	static UnitAgentType getUnitAgentType(BWAPI::Unit unit) {
		if (unit->getType() == BWAPI::UnitTypes::Protoss_Probe) {
			return UnitAgentType::WORKER;
		}
		if (unit->getType() == BWAPI::UnitTypes::Protoss_Observer) {
			return OBSERVER;

		}
		if ((std::set<BWAPI::UnitType> { BWAPI::UnitTypes::Protoss_Archon,
			BWAPI::UnitTypes::Protoss_Dark_Archon,
			BWAPI::UnitTypes::Protoss_Dark_Templar,
			BWAPI::UnitTypes::Protoss_Dragoon,
			BWAPI::UnitTypes::Protoss_High_Templar,
			BWAPI::UnitTypes::Protoss_Reaver,
			BWAPI::UnitTypes::Protoss_Scarab,
			BWAPI::UnitTypes::Protoss_Zealot
		}).contains(unit->getType())) {
			return GROUNDMOBILE;
		}
		if ((std::set<BWAPI::UnitType> { BWAPI::UnitTypes::Protoss_Arbiter,
			BWAPI::UnitTypes::Protoss_Carrier,
			BWAPI::UnitTypes::Protoss_Corsair,
			BWAPI::UnitTypes::Protoss_Interceptor,
			BWAPI::UnitTypes::Protoss_Scout,
			BWAPI::UnitTypes::Protoss_Shuttle,
		}).contains(unit->getType())) {
			return FLYINGMOBILE;
		}
		if ((std::set<BWAPI::UnitType> { BWAPI::UnitTypes::Protoss_Arbiter_Tribunal,
			BWAPI::UnitTypes::Protoss_Assimilator,
			BWAPI::UnitTypes::Protoss_Citadel_of_Adun,
			BWAPI::UnitTypes::Protoss_Cybernetics_Core,
			BWAPI::UnitTypes::Protoss_Fleet_Beacon,
			BWAPI::UnitTypes::Protoss_Forge,
			BWAPI::UnitTypes::Protoss_Gateway,
			BWAPI::UnitTypes::Protoss_Nexus,
			BWAPI::UnitTypes::Protoss_Observatory,
			BWAPI::UnitTypes::Protoss_Photon_Cannon,
			BWAPI::UnitTypes::Protoss_Pylon,
			BWAPI::UnitTypes::Protoss_Robotics_Facility,
			BWAPI::UnitTypes::Protoss_Robotics_Support_Bay,
			BWAPI::UnitTypes::Protoss_Shield_Battery,
			BWAPI::UnitTypes::Protoss_Stargate,
			BWAPI::UnitTypes::Protoss_Templar_Archives,
		}).contains(unit->getType())) {
			return BUILDING;
		}

		return NONE_TYPE;

	}

};

