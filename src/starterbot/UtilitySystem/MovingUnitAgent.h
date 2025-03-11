#pragma once

#include "GenericUnitAgent.h"

class MovingUnitAgent : public GenericUnitAgent {
public:
	MovingUnitAgent(BWAPI::Unit unit) : GenericUnitAgent(unit) {}
	MovingUnitAgent(BWAPI::Unit unit, std::shared_ptr<BT_NODE> fleeingBT) : GenericUnitAgent(unit, fleeingBT) {}

};