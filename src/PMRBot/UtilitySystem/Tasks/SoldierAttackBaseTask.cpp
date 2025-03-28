#include "SoldierAttackBaseTask.h"

#include "BT_ACTION_EXECUTE_METHOD.h"

SoldierAttackBaseTask::SoldierAttackBaseTask(std::shared_ptr<TaskEmitter> taskEmitter, std::vector<BWAPI::TilePosition>* enemyBaseList) : Task("Soldier Attack Base Task", taskEmitter) {
	
	this->enemyBaseList = enemyBaseList;

	void* data;

	soldier = this->getExecutor()->getUnit();

	m_compatibilityUnitAgentType = { UnitAgent::GROUNDMOBILE, UnitAgent::FLYINGMOBILE };

	m_taskBT = std::make_shared<BT_DECORATOR>("Entry Point", nullptr);

	BT_NODE* pAttackBaseMainSelector = new BT_SELECTOR("Attack base sequencer", m_taskBT.get(), 6);

	BT_NODE* pMoveToPos = new BT_ACTION_EXECUTE_METHOD("Move to pos", pAttackBaseMainSelector, std::bind(moveToPosition, this, std::placeholders::_1)); // => ACTION TO CREATE

	BT_NODE* pAttackEnemySoldiersSequencer = new BT_SEQUENCER("Attack enemy soldiers sequencer", pAttackBaseMainSelector, 2); // => ACTION TO CREATE
	BT_NODE* pCondSeesEnemy = new BT_DECO_CONDITION("Sees enemy condition", pAttackEnemySoldiersSequencer, areEnemyInSight); // => CONDITION TO CREATE (also in idle task)
	BT_NODE* pAttackSoldierAction = new BT_ACTION_EXECUTE_METHOD("Attack seen enemy", pAttackEnemySoldiersSequencer, std::bind(attackSeenEnemy, this, std::placeholders::_1)); // => CREATE ACTION

	BT_NODE* pAttackDefendingBuildingsSequencer = new BT_SEQUENCER("Attack defending buildings sequencer", pAttackBaseMainSelector, 2);
	BT_NODE* pCondSeesDefendingBuildings = new BT_DECO_CONDITION("Sees defending building condition", pAttackDefendingBuildingsSequencer, areDefensiveBuildingsInSight); // => CONDITION TO CREATE
	BT_NODE* pAttackDefendingBuildingsAction = new BT_ACTION_EXECUTE_METHOD("Attack defending building", pAttackDefendingBuildingsSequencer, std::bind(attackDefensiveBuildings, this, std::placeholders::_1)); // => ACTION TO CREATE

	BT_NODE* pAttackSupplyProvidersSequencer = new BT_SEQUENCER("Attack supply providers sequencer", pAttackBaseMainSelector, 2);
	BT_NODE* pSeesSupplyProviders = new BT_DECO_CONDITION("Sees suply provider condition", pAttackSupplyProvidersSequencer, areSupplyProviderInSight); // => CONDITION TO CREATE
	BT_NODE* pAttackSupplyProviderAction = new BT_ACTION_EXECUTE_METHOD("Attack supply provider", pAttackSupplyProvidersSequencer, std::bind(attackSupplyProvider, this, std::placeholders::_1)); // => ACTION TO CREATE

	BT_NODE* pAttackWorkersOrStocksSequencer = new BT_SEQUENCER("Attack worker or ressource stocks", pAttackBaseMainSelector, 2);
	BT_NODE* pCondSeesWorkersOrStocks = new BT_DECO_CONDITION("Sees workers or ressources stock condition", pAttackWorkersOrStocksSequencer, areWorkerOrRessourceStocksInSight); // => CONDITION TO CREATE
	BT_NODE* pAttackWorkerOrStockAction = new BT_ACTION_EXECUTE_METHOD("Attack wortker or ressource stock", pAttackWorkersOrStocksSequencer, std::bind(attackWorkerOrStocksInSight, this, std::placeholders::_1)); // => CREATE ACTION

	BT_NODE* pAttackOther = new BT_ACTION_EXECUTE_METHOD("Attack something else", pAttackBaseMainSelector, std::bind(attackAll, this, std::placeholders::_1)); // => CREATE ACTION to attack soemthing else
}

BT_NODE::State SoldierAttackBaseTask::moveToPosition(void* data)
{
	Data* pData = (Data*)data;

	this->getExecutor()->getUnit()->move((BWAPI::Position(enemyBaseList->at(0))));

	return BT_NODE::State::SUCCESS;
}

bool SoldierAttackBaseTask::areEnemyInSight(void* data)
{
	Data* pData = (Data*)data;

	BWAPI::Unitset enemyUnits = BWAPI::Broodwar->enemy()->getUnits();
	for (auto& unit : enemyUnits) {
		if(!unit->getType().isBuilding() && !unit->getType().isWorker()) {
			return true;
		}
	}

	return false;
}

BT_NODE::State SoldierAttackBaseTask::attackSeenEnemy(void* data)
{
	Data* pData = (Data*)data;

	BWAPI::Unitset enemyUnits = BWAPI::Broodwar->enemy()->getUnits();
	for (auto& unit : enemyUnits) {
		if (!unit->getType().isBuilding() && !unit->getType().isWorker()) {
			soldier->attack(unit);
			return BT_NODE::State::SUCCESS;
		}
	}

	return BT_NODE::State::FAILURE;
}

bool SoldierAttackBaseTask::areDefensiveBuildingsInSight(void* data)
{
	Data* pData = (Data*)data;

	BWAPI::Unitset enemyUnits = BWAPI::Broodwar->enemy()->getUnits();
	for (auto& unit : enemyUnits) {
		BWAPI::UnitType type = unit->getType();
		if (unit->getType().isBuilding() && (type == BWAPI::UnitTypes::Terran_Missile_Turret || type == BWAPI::UnitTypes::Protoss_Photon_Cannon || type == BWAPI::UnitTypes::Zerg_Spore_Colony || type == BWAPI::UnitTypes::Protoss_Shield_Battery)) {
			return true;
		}	
	}

	return false;
}

BT_NODE::State SoldierAttackBaseTask::attackDefensiveBuildings(void* data)
{
	Data* pData = (Data*)data;

	BWAPI::Unitset enemyUnits = BWAPI::Broodwar->enemy()->getUnits();
	for (auto& unit : enemyUnits) {
		BWAPI::UnitType type = unit->getType();
		if (unit->getType().isBuilding() && (type == BWAPI::UnitTypes::Terran_Missile_Turret || type == BWAPI::UnitTypes::Protoss_Photon_Cannon || type == BWAPI::UnitTypes::Zerg_Spore_Colony || type == BWAPI::UnitTypes::Protoss_Shield_Battery)) {
			soldier->attack(unit);
			return BT_NODE::State::SUCCESS;
		}
	}

	return BT_NODE::State::FAILURE;
}

bool SoldierAttackBaseTask::areSupplyProviderInSight(void* data)
{
	Data* pData = (Data*)data;

	BWAPI::Unitset enemyUnits = BWAPI::Broodwar->enemy()->getUnits();
	for (auto& unit : enemyUnits) {
		BWAPI::UnitType type = unit->getType();
		if (unit->getType().isBuilding() && (type == BWAPI::UnitTypes::Terran_Supply_Depot || type == BWAPI::UnitTypes::Protoss_Pylon || type == BWAPI::UnitTypes::Zerg_Overlord)) {
			return true;
		}
	}

	return false;
}

BT_NODE::State SoldierAttackBaseTask::attackSupplyProvider(void* data)
{
	Data* pData = (Data*)data;

	BWAPI::Unitset enemyUnits = BWAPI::Broodwar->enemy()->getUnits();
	for (auto& unit : enemyUnits) {
		BWAPI::UnitType type = unit->getType();
		if (unit->getType().isBuilding() && (type == BWAPI::UnitTypes::Terran_Supply_Depot || type == BWAPI::UnitTypes::Protoss_Pylon || type == BWAPI::UnitTypes::Zerg_Overlord)) {
			soldier->attack(unit);
			return BT_NODE::State::SUCCESS;
		}
	}

	return BT_NODE::State::FAILURE;
}

bool SoldierAttackBaseTask::areWorkerOrRessourceStocksInSight(void* data)
{
	Data* pData = (Data*)data;

	BWAPI::Unitset enemyUnits = BWAPI::Broodwar->enemy()->getUnits();
	for (auto& unit : enemyUnits) {
		BWAPI::UnitType type = unit->getType();
		if (unit->getType().isBuilding() && (type == BWAPI::UnitTypes::Protoss_Nexus || type == BWAPI::UnitTypes::Protoss_Assimilator || type == BWAPI::UnitTypes::Terran_Refinery || type == BWAPI::UnitTypes::Zerg_Extractor || type == BWAPI::UnitTypes::Terran_Command_Center || type == BWAPI::UnitTypes::Zerg_Hatchery)) {
			return true;
		}
	}

	return false;
}

BT_NODE::State SoldierAttackBaseTask::attackWorkerOrStocksInSight(void* data)
{
	Data* pData = (Data*)data;

	BWAPI::Unitset enemyUnits = BWAPI::Broodwar->enemy()->getUnits();
	for (auto& unit : enemyUnits) {
		BWAPI::UnitType type = unit->getType();
		if (unit->getType().isBuilding() && (type == BWAPI::UnitTypes::Protoss_Nexus || type == BWAPI::UnitTypes::Protoss_Assimilator || type == BWAPI::UnitTypes::Terran_Refinery || type == BWAPI::UnitTypes::Zerg_Extractor || type == BWAPI::UnitTypes::Terran_Command_Center || type == BWAPI::UnitTypes::Zerg_Hatchery)) {
			soldier->attack(unit);
			return BT_NODE::State::SUCCESS;
		}
	}

	return BT_NODE::State::FAILURE;
}

BT_NODE::State SoldierAttackBaseTask::attackAll(void* data)
{
	Data* pData = (Data*)data;

	BWAPI::Unitset enemyUnits = BWAPI::Broodwar->enemy()->getUnits();
	for (auto& unit : enemyUnits) {
		soldier->attack(unit);
		return BT_NODE::State::SUCCESS;
	}

	return BT_NODE::State::FAILURE;
}
