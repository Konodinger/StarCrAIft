#include "BT_ACTION_SEARCH_NEW_ENEMY_BASE.h"
#include "Data.h"

BT_ACTION_SEARCH_NEW_ENEMY_BASE::BT_ACTION_SEARCH_NEW_ENEMY_BASE(std::string name, BT_NODE* parent, BWAPI::Unit unit, std::vector<BWAPI::TilePosition>* enemyBaseList)
	: BT_ACTION(name, parent), scout(unit), enemyBaseList(enemyBaseList)
{
}

BT_NODE::State BT_ACTION_SEARCH_NEW_ENEMY_BASE::Evaluate(void* data)
{
	return ReturnState(SearchEnemyBase(data));
}

std::string BT_ACTION_SEARCH_NEW_ENEMY_BASE::GetDescription()
{
	return "SEARCH ENEMY BASE";
}

BT_NODE::State BT_ACTION_SEARCH_NEW_ENEMY_BASE::SearchEnemyBase(void* data) {
	
	Data* pData = (Data*)data;
	MapTools map = pData->mapTools;
	
	//Use references instead of pointers for enemyBaseList ?
	const BWAPI::Unitset& enemyUnits = BWAPI::Broodwar->enemy()->getUnits();
	for (auto& unit : enemyUnits) {

		if (unit->getType().isBuilding()) {
			bool isFarFromKnownBases = true;
			BWAPI::TilePosition basePos = unit->getTilePosition();

			for (int i = 0; i < enemyBaseList->size(); i++) {
				if (basePos.getDistance(enemyBaseList->at(i)) < 50.f) { //Ajuster valeur ?
					isFarFromKnownBases = false;
				}
			}
			if (isFarFromKnownBases) {
				enemyBaseList->push_back(basePos);
				return BT_NODE::SUCCESS;
			}
		}
	}

	for (int i = map.width()-1; i>=0; i--) {
		for (int j = map.height() - 1; j >= 0; j--) {
			BWAPI::TilePosition tile = BWAPI::TilePosition(i, j);

			if ((!map.isExplored(tile)) && map.isWalkable(tile)) {
				BWAPI::Position position = BWAPI::Position(tile);
				scout->move(position, false);
				return BT_NODE::RUNNING;
			}
		}
	}

	return BT_NODE::FAILURE;
	

}