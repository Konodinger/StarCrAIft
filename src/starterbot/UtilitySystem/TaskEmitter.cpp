#include "TaskEmitter.h"

void TaskEmitter::ExecuteTaskEmissionBT(Data* pData) {
    if (pTaskEmitterBT == nullptr) {
        BWAPI::Broodwar->printf(("Warning: the task emitter " + m_name + " doesn't have a behaviour tree associated...").c_str());
        return;
    }
    if (pTaskEmitterBT->Evaluate(pData) != BT_NODE::SUCCESS)
    {
        BWAPI::Broodwar->printf(("Warning: the task emitter " + m_name + " ended incorrectly...").c_str());
    }
}

void TaskEmitter::computeTaskReward() {
    for (auto task : m_taskEmitted) {
        task->reward();
    }
}