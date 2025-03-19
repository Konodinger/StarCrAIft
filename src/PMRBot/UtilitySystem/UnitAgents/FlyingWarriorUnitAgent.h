#pragma once

#include "MovingUnitAgent.h"

class FlyingWarriorUnitAgent : public MovingUnitAgent {
public:
	FlyingWarriorUnitAgent(BWAPI::Unit unit) : MovingUnitAgent(unit) {}
	FlyingWarriorUnitAgent(BWAPI::Unit unit, std::shared_ptr<BT_NODE> fleeingBT) : MovingUnitAgent(unit, fleeingBT) {}

};