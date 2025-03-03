#include "TaskEmitter.h"

void TaskEmitter::ExecuteTaskEmissionBT(Data* pData) {
    if (pTaskEmitterBT != nullptr && pTaskEmitterBT->Evaluate(pData) != BT_NODE::SUCCESS)
    {
        BWAPI::Broodwar->printf("Warning: the IDLE Manager ended incorrectly...");
    }
}

void TaskEmitter::computeTaskReward() {
    for (auto task : m_taskEmitted) {
        task->reward();
    }
}