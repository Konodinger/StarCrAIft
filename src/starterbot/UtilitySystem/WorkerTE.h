#pragma once

#include "TaskEmitter.h"

class WorkerTE : public TaskEmitter {
public:
	WorkerTE() {
		m_name = "WorkerTE";
		createBT();
	};

	static bool checkIfEnoughMineralGathering(void* pData);
	static BT_NODE::State emitMineralGatheringTask(void* pData);

	static bool checkIfEnoughVespeneGathering(void* pData);
	static BT_NODE::State emitVespeneGatheringTask(void* pData);

	static bool checkIfEnoughScout(void* pData);
	static BT_NODE::State emitScoutingTask(void* pData);

private:
	void createBT();

};
