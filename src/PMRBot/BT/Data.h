#pragma once

class Data;
#include <unordered_set>
#include <map>
#include "UnitAgent.h"
#include "Task.h"
#include "EventManagerTE.h"
#include "ResourcesManager.h"


#define THRESHOLD1_MINERALS 200
#define THRESHOLD1_UNUSED_SUPPLY 2

#define NWANTED_WORKERS_TOTAL 20
#define NWANTED_WORKERS_FARMING_MINERALS 16

class TaskEmitter;
enum class EmitterType;

class Data {
public:
	Data() = default;
	int currMinerals;
	int thresholdMinerals;
	int currSupply;
	int thresholdSupply;

	int nWantedWorkersTotal;
	int nWantedWorkersFarmingMinerals;

	std::unordered_set<BWAPI::Unit> unitsFarmingMinerals;

	std::vector<std::shared_ptr<Task>> m_taskList;
	std::map<int, std::shared_ptr<UnitAgent>> unitAgentsList;

	std::map<EmitterType, std::shared_ptr<TaskEmitter>> m_task_emitter_map;
	std::shared_ptr<EventManagerTE> m_eventManagerTE;

	std::shared_ptr<ResourcesManager> resourcesManager;

	int goalMineralGatheringWorkforce = 10;
	int goalVespeneGatheringWorkforce = 4;
	int goalScoutWorkforce = 1;
};
