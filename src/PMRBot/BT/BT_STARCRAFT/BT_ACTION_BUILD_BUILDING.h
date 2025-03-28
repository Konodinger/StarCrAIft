#pragma once
#include <cassert>
#include "BT_ACTION.h"
#include <vector>
#include <BWAPI.h>

class BuildingTask;

//--------------------
class BT_ACTION_BUILD_BUILDING : public BT_ACTION {
public:
	BT_ACTION_BUILD_BUILDING(std::string name, BT_NODE* parent, BuildingTask* task, BWAPI::TilePosition idealPosition = BWAPI::TilePositions::None);

private:
	State Evaluate(void* data) override;
	std::string GetDescription() override;
	BT_NODE::State BuildBuilding(void* data);
	BuildingTask* m_task;

	bool m_have_borrowed = false;
	BWAPI::TilePosition m_idealPosition;
	
};
//----------