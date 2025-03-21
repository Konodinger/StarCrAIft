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
		int numWorkersOnMinerals = 0;
		for (auto& unit : BWAPI::Broodwar->self()->getUnits()) {
			if (unit->getType().isWorker() && unit->isGatheringMinerals()) {
				numWorkersOnMinerals++;
			}
		}

		for (auto& agent : pData->unitAgentsList) {
			auto& unitAgent = agent.second;
			const auto& unit = unitAgent->getUnit();
			if (unitAgent->getState() == UnitAgent::UnitAgentState::IDLING && unit->isIdle()) {
				if (unit->getType().isWorker()) {
					if (numWorkersOnMinerals < pData->nWantedWorkersFarmingMinerals) {
						BWAPI::Unit closestMineral = Tools::GetClosestUnitTo(unit, BWAPI::Broodwar->getMinerals());
						if (closestMineral) {
							unit->rightClick(closestMineral);
							numWorkersOnMinerals++;
						}
					}
					else { // On Vespene
						BWAPI::Unit closestGeyser = Tools::GetClosestUnitTo(unit, BWAPI::Broodwar->getGeysers());
						if (closestGeyser) {
							unit->rightClick(closestGeyser);
						}
					}
				}
			}
		}
	}

private:
	Data* pData;
};
