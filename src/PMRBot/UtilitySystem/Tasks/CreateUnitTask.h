#pragma once
#include "Task.h"


/*
* Represent a task to be accomplished, specific to creating a unit.
* Allow to compute the reward associated with completing it.
* Holds a Behaviour Tree that states how to accomplish the task.
*/
class CreateUnitTask : public Task {
public:
	CreateUnitTask(std::shared_ptr<TaskEmitter> taskEmitter, BWAPI::UnitType unitToCreate, BWAPI::UnitType buildingTraining);

	inline BWAPI::UnitType getType() { return unitToTrain; }
	static BT_NODE::State trainUnit(void* pData, CreateUnitTask* task);
private:
	bool m_have_borrowed = false;
	BWAPI::UnitType unitToTrain;
};
