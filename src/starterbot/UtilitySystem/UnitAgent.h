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
	OBSERVER,
	GROUNDMOBILE,
	FLYINGMOBILE,
	BUILDING
};

class UnitAgent
{
public:
	UnitAgent() = delete;
	UnitAgent(BWAPI::Unit unit)
		: m_unit(unit)
	{
		setUnitAgentType();
	}

	UnitAgent(BWAPI::Unit unit, std::shared_ptr<BT_NODE> fleeingBT)
		: m_unit(unit), m_fleeingBT(fleeingBT)
	{
		setUnitAgentType();
	}

	BWAPI::Unit getUnit() const { return m_unit; }
	UnitAgentState getState() const { return m_state; }
	UnitAgentType getType() const { return m_type; }

	const std::shared_ptr<BT_NODE> getIdlingBT() { return m_idlingBT; }
	void setIdlingBT(std::shared_ptr<BT_NODE> const bt) { m_idlingBT = bt; }

	// Called by [] in order to check if the unit is available
	virtual bool checkFlee(Data* pData) = 0;

	void execute(Data* pData);

	virtual float computeInterest(std::shared_ptr<Task> task /*pData*/) = 0;

	virtual void drawDebug() = 0;

	void setTask(std::shared_ptr<Task> task) {
		m_state = UnitAgentState::WORKING;
		m_task = task;
	}
public:
	// Create a UnitAgent from a BWAPI::Unit using the correct class
	static std::shared_ptr<UnitAgent> createUnitAgent(BWAPI::Unit unit);

private:
	bool m_isSquad = false;

	void setUnitAgentType() {
		assert(m_unit != nullptr && "Warning: the setUnitAgentType should only be called after a unit was associated with the agent.");
		if (m_unit->getType() == BWAPI::UnitTypes::Protoss_Probe) {
			m_type = WORKER;
			return;
		}
		if (m_unit->getType() == BWAPI::UnitTypes::Protoss_Observer) {
			m_type = OBSERVER;
			return;
		}
		if ((std::set<BWAPI::UnitType> { BWAPI::UnitTypes::Protoss_Archon,
			BWAPI::UnitTypes::Protoss_Dark_Archon,
			BWAPI::UnitTypes::Protoss_Dark_Templar,
			BWAPI::UnitTypes::Protoss_Dragoon,
			BWAPI::UnitTypes::Protoss_High_Templar,
			BWAPI::UnitTypes::Protoss_Reaver,
			BWAPI::UnitTypes::Protoss_Scarab,
			BWAPI::UnitTypes::Protoss_Zealot
		}).contains(m_unit->getType())) {
			m_type = GROUNDMOBILE;
		}
		if ((std::set<BWAPI::UnitType> { BWAPI::UnitTypes::Protoss_Arbiter,
			BWAPI::UnitTypes::Protoss_Carrier,
			BWAPI::UnitTypes::Protoss_Corsair,
			BWAPI::UnitTypes::Protoss_Interceptor,
			BWAPI::UnitTypes::Protoss_Scout,
			BWAPI::UnitTypes::Protoss_Shuttle,
		}).contains(m_unit->getType())) {
			m_type = FLYINGMOBILE;
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
		}).contains(m_unit->getType())) {
			m_type = BUILDING;
		}
		BWAPI::Broodwar->printf(("Error: the unit " + std::to_string(m_unit->getID()).append(" (") + (m_unit->getType().getName()) + ") is not a reckognized Protoss unit, and thus should not be assciated to a UnitAgent").c_str());
	}

	std::shared_ptr<BT_NODE> m_fleeingBT = std::make_shared<BT_ACTION_EMPTY_BT>("Default fleeing BT", nullptr);
	std::shared_ptr<BT_NODE> m_idlingBT = std::make_shared<BT_ACTION_EMPTY_BT>("Default idling BT", nullptr);

	BWAPI::Unit m_unit;
	std::vector<BWAPI::Unit> m_squadUnit;
	std::shared_ptr<Task> m_task;

	UnitAgentType m_type;
	UnitAgentState m_state;


};

