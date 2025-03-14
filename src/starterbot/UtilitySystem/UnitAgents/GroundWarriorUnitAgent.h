#pragma once

#include "MovingUnitAgent.h"

class GroundWarriorUnitAgent : public MovingUnitAgent {
public:
	GroundWarriorUnitAgent(BWAPI::Unit unit) : MovingUnitAgent(unit) {}
	GroundWarriorUnitAgent(BWAPI::Unit unit, std::shared_ptr<BT_NODE> fleeingBT) : MovingUnitAgent(unit, fleeingBT) {}

};