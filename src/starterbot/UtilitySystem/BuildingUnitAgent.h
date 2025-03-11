#pragma once

#include "GenericUnitAgent.h"

class BuildingUnitAgent : public GenericUnitAgent {
public:
	BuildingUnitAgent(BWAPI::Unit unit) : GenericUnitAgent(unit) {}
	BuildingUnitAgent(BWAPI::Unit unit, std::shared_ptr<BT_NODE> fleeingBT) : GenericUnitAgent(unit, fleeingBT) {}

	virtual void drawDebug() {
		BWAPI::Position pos = getUnit()->getPosition();
		//BWAPI::Broodwar->drawCircleMap(pos, 10, BWAPI::Colors::Green);
		BWAPI::Broodwar->drawTriangleMap(pos.x - 10, pos.y - 10, pos.x + 10, pos.y - 10, pos.x, pos.y + 10, BWAPI::Colors::Green);
	}
};