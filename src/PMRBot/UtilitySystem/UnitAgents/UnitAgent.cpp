#include "UnitAgent.h"

#include "FarmerUnitAgent.h"
#include "ObserverUnitAgent.h"
#include "GroundWarriorUnitAgent.h"
#include "FlyingWarriorUnitAgent.h"
#include "BuildingUnitAgent.h"

#include "Task.h"


void UnitAgent::execute(Data* pData) {
	// Check if not in a squad.
	//..


	std::shared_ptr<BT_NODE> bt =
		(m_state == FLEEING) ? m_fleeingBT :
		(m_state == WORKING) ? m_task->getBT() : nullptr;

	if (bt != nullptr) {
		const BT_NODE::State state = bt->Evaluate(pData);
		bt->Reset();
		if (state == BT_NODE::FAILURE)
		{
			BWAPI::Broodwar->printf(("Warning: the Unit Agent " + std::to_string(m_unit->getID()) + " ended incorrectly while executing behaviour tree...").c_str());
		}
		if (state == BT_NODE::SUCCESS && m_state == WORKING) {
			if (m_task->getTaskEmitter() == nullptr) {
				BWAPI::Broodwar->printf(("Warning: the Task " + m_task->getName() + " doesn't have a Task Emitter associated...").c_str());
			}
			else {
				m_task->getTaskEmitter()->onTaskFinished(m_task);
			}
			m_task.reset();
			m_state = IDLING;
		}

	}
}

std::shared_ptr<UnitAgent> UnitAgent::createUnitAgent(BWAPI::Unit unit) {

	assert(unit != nullptr && "Error: the unit is null");

	const UnitAgentType type = getUnitAgentType(unit);

	std::shared_ptr<UnitAgent> agent = nullptr;

	switch (type) {
	case WORKER:
		agent = std::make_shared<FarmerUnitAgent>(unit);
		break;
	case OBSERVER:
		agent = std::make_shared<ObserverUnitAgent>(unit);
		break;
	case GROUNDMOBILE:
		agent = std::make_shared<GroundWarriorUnitAgent>(unit);
		break;
	case FLYINGMOBILE:
		agent = std::make_shared<FlyingWarriorUnitAgent>(unit);
		break;
	case BUILDING:
		agent = std::make_shared<BuildingUnitAgent>(unit);
		break;
	case NONE_TYPE:
		BWAPI::Broodwar->printf(("Error: the unit " + std::to_string(unit->getID()).append(" (") + (unit->getType().getName()) + ") is not a reckognized Protoss unit, and thus should not be assciated to a UnitAgent").c_str());
		break;
	}

	if (agent != nullptr)
		agent->m_type = type;
	return agent;
}
