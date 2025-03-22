#pragma once

#include "TaskEmitter.h"
#include "BT.h"

class UnitProducerTE : public TaskEmitter {
public:
	UnitProducerTE() {
		m_name = "UnitProducerTE";
		createBT();
	};

	static bool checkIfEnoughWorker(void* data);
	static bool checkIfEnoughPylonForNewWorker(void* data);
	static BT_NODE::State emitCreateWorkerTask(void* pData);

private:
	void createBT();

};