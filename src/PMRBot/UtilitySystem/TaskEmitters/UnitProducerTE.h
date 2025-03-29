#pragma once

#include "TaskEmitter.h"
#include "BT.h"


/*
* Uses a Behaviour Tree and the data stored on the Blackboard to emit tasks specific to producing units.
*/
class UnitProducerTE : public TaskEmitter {
public:
	UnitProducerTE() {
		m_name = "UnitProducerTE";
		createBT();
	};

	static bool checkIfGateway(void* data);
	static bool checkIfEnoughWorker(void* data);
	static bool checkIfEnoughZealot(void* data);
	static BT_NODE::State checkIfEnoughPylonForNewUnit(void* data, BWAPI::UnitType unitType);
	static BT_NODE::State emitCreateWorkerTask(void* pData);
	static BT_NODE::State emitCreateZealotTask(void* pData);

private:
	void createBT();

};