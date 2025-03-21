#pragma once
#include "Task.h"

class CreateBuildingTask : public Task {
public:
	CreateBuildingTask(std::shared_ptr<TaskEmitter> taskEmitter, BWAPI::UnitType building, BWAPI::TilePosition idealPosition = BWAPI::TilePositions::None);

	static BT_NODE::State checkIfConstructingPylon(void* pData, CreateBuildingTask* task);
	static BT_NODE::State constructPylon(void* pData, CreateBuildingTask* task);
	// Identical for now, but we might want to build Pylons on optimized places, for instance.
	static BT_NODE::State constructOtherBuilding(void* pData, CreateBuildingTask* task);
	
	BWAPI::UnitType m_building;
	BWAPI::TilePosition m_buildingIdealPosition;
	bool m_isBuildingBeingConstructed = false;
};

