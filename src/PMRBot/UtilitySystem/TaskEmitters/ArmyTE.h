#pragma once
#include "TaskEmitter.h"
class ArmyTE : public TaskEmitter {
public:

	ArmyTE() {
		m_name = "ArmyTE";
		createBT();
	};

	static bool checkIfEnoughSoldiers(void* data);
	static BT_NODE::State emitCreateSoldiersTask(void* pData);
private:
	void createBT();
	int m_numSoldierSent = 0;
};

