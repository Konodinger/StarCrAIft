#pragma once

#include "MovingUnitAgent.h"

class ObserverUnitAgent : public MovingUnitAgent {
public:
	ObserverUnitAgent(BWAPI::Unit unit) : MovingUnitAgent(unit) {}
	ObserverUnitAgent(BWAPI::Unit unit, std::shared_ptr<BT_NODE> fleeingBT) : MovingUnitAgent(unit, fleeingBT) {}

};