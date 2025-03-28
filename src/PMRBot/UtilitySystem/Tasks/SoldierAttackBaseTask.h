#pragma once
#include "Task.h"


/*
* Represent a task to be accomplished, specific to attacking.
* Allow to compute the reward associated with completing it.
* Holds a Behaviour Tree that states how to accomplish the task.
*/
class SoldierAttackBaseTask :
    public Task
{
public:

    SoldierAttackBaseTask(std::shared_ptr<TaskEmitter> taskEmitter, std::vector<BWAPI::TilePosition>* enemyBaseList);

    BT_NODE::State moveToPosition(void* data);

    static bool areEnemyInSight(void* data);
    BT_NODE::State attackSeenEnemy(void* data);

    static bool areDefensiveBuildingsInSight(void* data);
    BT_NODE::State attackDefensiveBuildings(void* data);

    static bool areSupplyProviderInSight(void* data);
    BT_NODE::State attackSupplyProvider(void* data);

    static bool areWorkerOrRessourceStocksInSight(void* data);
    BT_NODE::State attackWorkerOrStocksInSight(void* data);

    BT_NODE::State attackAll(void* data);

    std::vector<BWAPI::TilePosition>* enemyBaseList;
    BWAPI::Unit soldier;

};

