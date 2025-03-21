#pragma once

#include <BT.h>
#include <memory>

#include "Data.h"
#include "Tools.h"

class IdleManager {
public:
	IdleManager(Data* data) : pData(data) {

	}

	void Execute() {
		for (auto& agent : pData->unitAgentsList) {
			auto& unitAgent = agent.second;
			const auto& unit = unitAgent->getUnit();
			if (unit->getType().isWorker() && unitAgent->getState() == UnitAgent::UnitAgentState::IDLING && unit->isIdle()) {
				BWAPI::Unit closestMineral = Tools::GetClosestUnitTo(unit, BWAPI::Broodwar->getMinerals());
				if (closestMineral) {
					unit->rightClick(closestMineral);
				}
			}
		}
	}

private:
	Data* pData;
};
