#pragma once
#include "TaskEmitter.h"

class BuildOrderTE : public TaskEmitter {
public:
	BuildOrderTE() {
		m_name = "BuildOrderTE";
	};


	void ExecuteTaskEmissionBT(Data* pData) override;
private:
	int m_numRegisteredWorkers = 0;
};

