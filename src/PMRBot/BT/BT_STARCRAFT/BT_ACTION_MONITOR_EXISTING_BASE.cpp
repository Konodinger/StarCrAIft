#include "BT_ACTION_MONITOR_EXISTING_BASE.h"
#include "Task.h"

BT_ACTION_MONITOR_EXISTING_BASE::BT_ACTION_MONITOR_EXISTING_BASE(std::string name, BT_NODE* parent, std::shared_ptr<int> nbScouts, std::vector<BWAPI::TilePosition>* enemyBaseList, Task* task) :
	BT_ACTION(name, parent), nbScouts(nbScouts), enemyBaseList(enemyBaseList), taskPtr(task) {}

std::string BT_ACTION_MONITOR_EXISTING_BASE::GetDescription()
{
	return "MONITOR ENEMY BASE";
}

BT_NODE::State BT_ACTION_MONITOR_EXISTING_BASE::Evaluate(void* data)
{
	return ReturnState(MonitorEnemyBase(data));
}

BT_NODE::State BT_ACTION_MONITOR_EXISTING_BASE::MonitorEnemyBase(void* data) {

	int nbScoutsTemp = *nbScouts;
	*nbScouts += 1;
	for (int i = 0; i < enemyBaseList->size(); i++) {
		if (nbScoutsTemp == 0) {
			BWAPI::Position position = BWAPI::Position(enemyBaseList->at(i));
			taskPtr->getExecutor()->getUnit()->move(position);

			return BT_NODE::RUNNING;
		}
		else {
			nbScoutsTemp -= 1;
		}
	}

	return BT_NODE::FAILURE;

}
