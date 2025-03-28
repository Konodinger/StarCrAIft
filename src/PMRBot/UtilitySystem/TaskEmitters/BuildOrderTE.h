#pragma once
#include "TaskEmitter.h"


/*
* Uses a Behaviour Tree and the data stored on the Blackboard to emit tasks specific to following the build order.
*/
class BuildOrderTE : public TaskEmitter {
public:
	BuildOrderTE() {
		m_name = "BuildOrderTE";
	};


	void ExecuteTaskEmissionBT(Data* pData) override;
private:
	int m_numRegisteredWorkers = 0;
};

