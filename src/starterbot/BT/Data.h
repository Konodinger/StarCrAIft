#pragma once
#include <unordered_set>
#include <BWAPI.h>
#include "UtilitySystem/UnitAgent.h"
#include "UtilitySystem/Task.h"
//#include "../../windows/visualstudio/UnitAgent.h"

#define THRESHOLD1_MINERALS 200
#define THRESHOLD1_UNUSED_SUPPLY 2

#define NWANTED_WORKERS_TOTAL 20
#define NWANTED_WORKERS_FARMING_MINERALS 10

class Data {
public:
	int currMinerals;
	int thresholdMinerals;
	int currSupply;
	int thresholdSupply;

	int nWantedWorkersTotal;
	int nWantedWorkersFarmingMinerals;

	std::unordered_set<BWAPI::Unit> unitsFarmingMinerals;

	std::vector<std::shared_ptr<Task>> m_taskList;
	std::unordered_set<std::shared_ptr<UnitAgent>> unitAgentsList;
};
