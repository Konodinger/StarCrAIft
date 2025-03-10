#pragma once

#include "UnitAgent.h"

/// <summary>
/// Class that represents a generic unit agent, it doesn't do anything (for all unimplemented units);
/// </summary>
class GenericUnitAgent : public UnitAgent {
public:

	GenericUnitAgent(BWAPI::Unit unit) : UnitAgent(unit) {}
	GenericUnitAgent(BWAPI::Unit unit, std::shared_ptr<BT_NODE> fleeingBT) : UnitAgent(unit, fleeingBT) {}

	virtual bool checkFlee(Data* pData) override {
		return false;
	}

	virtual float computeInterest(std::shared_ptr<Task> task) {
		return 0;
	}
private:
};