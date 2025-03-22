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
		int numWorkersOnGas = 0;
		for (auto& unit : BWAPI::Broodwar->self()->getUnits()) {
			if (unit->getType().isWorker()) {
				if (unit->isGatheringMinerals()) {
					numWorkersOnMinerals++;
				}
				if (unit->isGatheringGas()) {
					numWorkersOnGas++;
				}
			}
		}

		for (auto& agent : pData->unitAgentsList) {
			auto& unitAgent = agent.second;
			const auto& unit = unitAgent->getUnit();
			if (unitAgent->getState() == UnitAgent::UnitAgentState::IDLING && unit->isIdle()) {
				if (unit->getType().isWorker()) {
					if (numWorkersOnMinerals < pData->nWantedWorkersFarmingMineralsBeforeGas
						|| numWorkersOnGas >= pData->nWantedWorkersFarmingGas) {
						BWAPI::Unit closestMineral = Tools::GetClosestUnitTo(unit, BWAPI::Broodwar->getMinerals());
						if (closestMineral) {
							unit->gather(closestMineral);
							numWorkersOnMinerals++;
						}
					}
					else { // On Vespene
						BWAPI::Broodwar->self()->getUnits();
						auto assimilatorSet = Tools::GetUnitsOfType(BWAPI::UnitTypes::Protoss_Assimilator);
						BWAPI::Unit closestAssimilator = Tools::GetClosestUnitTo(unit, assimilatorSet);
						if (closestAssimilator) {
							unit->gather(closestAssimilator);
						}
					}
				}
			}
		}
	}

private:
	Data* pData;
};
