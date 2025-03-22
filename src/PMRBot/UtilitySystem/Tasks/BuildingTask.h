#pragma once
#include "Task.h"
#include <memory>

#include "ResourcesManager.h"

class BuildingTask : public Task {
public:
	BuildingTask(std::shared_ptr<TaskEmitter> taskEmitter, BWAPI::UnitType type, std::shared_ptr<ResourcesManager> resourcesManager, BWAPI::TilePosition idealPosition = BWAPI::TilePositions::None);
	BWAPI::UnitType getType() { return m_type; }

private:
	BWAPI::UnitType m_type;
};

