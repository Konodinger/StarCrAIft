#include "Task.h"
#include "UnitAgent.h"

unsigned int Task::count = 0;

bool Task::ongoing() const
{
	return m_executor != nullptr && m_executor->getState() == UnitAgent::WORKING;
}
