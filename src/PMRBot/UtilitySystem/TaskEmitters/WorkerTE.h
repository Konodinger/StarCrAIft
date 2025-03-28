#pragma once

#include "TaskEmitter.h"
#include "BT.h"


/*
* Uses a Behaviour Tree and the data stored on the Blackboard to emit tasks specific to workers.
*/
class WorkerTE : public TaskEmitter {
public:
	WorkerTE() {
		m_name = "WorkerTE";
		createBT();
	};

	static bool checkIfEnoughMineralGathering(void* pData);
	//static BT_NODE::State emitMineralGatheringTask(void* pData);

	static bool checkIfEnoughVespeneGathering(void* pData);
	static BT_NODE::State emitVespeneGatheringTask(void* pData);

	static bool checkIfEnoughScout(void* pData);
	static BT_NODE::State emitScoutingTask(void* pData);

private:
	void createBT();

	static inline std::vector<BWAPI::TilePosition>* enemyBaseList = new std::vector<BWAPI::TilePosition>();
	static inline std::shared_ptr<int> nbScoutsMonitoring = std::make_shared<int>(0);

};