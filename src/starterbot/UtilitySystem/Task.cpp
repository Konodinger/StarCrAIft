#include "Task.h"
#include "UnitAgent.h"

bool Task::ongoing() const
{
	return m_executor != nullptr && m_executor->getState() == UnitAgentState::WORKING;
}
