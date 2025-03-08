#include "UnitAgent.h"


void UnitAgent::execute(Data* pData) {
	// Check if not in a squad.
    //..


	std::shared_ptr<BT_NODE> bt =
		(m_state == FLEEING) ? m_fleeingBT :
		(m_state == WORKING) ? m_task->getBT() : m_idlingBT;

    if (bt == nullptr) {
        BWAPI::Broodwar->printf(("Warning: the Unit Agent " + std::to_string(m_unit->getID()) + " found an empty behaviour tree...").c_str());
        return;
    }
    BT_NODE::State state = bt->Evaluate(pData);
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
    }
}