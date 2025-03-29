#pragma once

class Data;
#include <unordered_set>
#include <map>
#include "UnitAgent.h"
#include "Task.h"
#include "EventManagerTE.h"
#include "ResourcesManager.h"
#include "MapTools.h"


#define THRESHOLD_MINERALS 200
#define THRESHOLD_UNUSED_SUPPLY 6

#define NWANTED_WORKERS_TOTAL 25
#define NWANTED_WORKERS_FARMING_MINERALS_BEFORE_GAS 11
#define NWANTED_WORKERS_FARMING_GAS 4
#define NMIN_WORKERS_BEFORE_SCOUTING 8

#define NWANTED_ZEALOTS_TOTAL 16

#define NMIN_SOLDIERS_BEFORE_ATTACK 8

class TaskEmitter;
enum class EmitterType;

class Data {
public:
	enum Request {
		UNNEEDED,
		REQUESTED,
		TREATED,
	};


	Data() = default;

	MapTools mapTools;

	int currMinerals;
	int thresholdMinerals;
	int currSupply;
	int thresholdSupply;

	int nWantedWorkersTotal;
	int nWantedWorkersFarmingMineralsBeforeGas;
	int nWantedWorkersFarmingGas;

	int nWantedZealotsTotal;

	int nMinWorkersBeforeScouting;

	int nMinSoldiersBeforeAttack;

	int numSoldierSent = 0;

	// Ordered by necessity, and paired with the expected number of workers
	std::vector<std::pair<int, BWAPI::UnitType>> buildOrderTechTree = {
		{10, BWAPI::UnitTypes::Protoss_Assimilator},
		{11, BWAPI::UnitTypes::Protoss_Gateway},
		{14, BWAPI::UnitTypes::Protoss_Forge},
		{15, BWAPI::UnitTypes::Protoss_Cybernetics_Core},
		{16, BWAPI::UnitTypes::Protoss_Stargate},
		{18, BWAPI::UnitTypes::Protoss_Fleet_Beacon},
	};

	Request askingForNewPylons;
	BWAPI::TilePosition askingForNewPylonsIdealPosition;

	std::unordered_set<BWAPI::Unit> unitsFarmingMinerals;

	std::vector<std::shared_ptr<Task>> m_taskList;
	std::unordered_set<std::shared_ptr<UnitAgent>> constructedUnitAgentsList;
	std::map<int, std::shared_ptr<UnitAgent>> unitAgentsList;

	std::map<EmitterType, std::shared_ptr<TaskEmitter>> m_task_emitter_map;
	std::shared_ptr<EventManagerTE> m_eventManagerTE;

	std::shared_ptr<ResourcesManager> resourcesManager;

	BWAPI::Unit attackTarget = nullptr;
	bool emitedScoutTask = false;

	int goalMineralGatheringWorkforce = 10;
	int goalVespeneGatheringWorkforce = 4;
	int goalScoutWorkforce = 1;
};
