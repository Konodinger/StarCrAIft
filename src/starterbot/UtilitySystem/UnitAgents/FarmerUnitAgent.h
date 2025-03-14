#pragma once

#include "MovingUnitAgent.h"

class FarmerUnitAgent : public MovingUnitAgent {
public:
	FarmerUnitAgent(BWAPI::Unit unit) : MovingUnitAgent(unit) {}
	FarmerUnitAgent(BWAPI::Unit unit, std::shared_ptr<BT_NODE> fleeingBT) : MovingUnitAgent(unit, fleeingBT) {}

};