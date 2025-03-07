#pragma once

#include <BWAPI.h>
#include "MapTools.h"
#include "UtilitySystem/Task.h"
#include "UtilitySystem/TaskEmitter.h"
#include "UtilitySystem/EventManagerTE.h"
#include "UtilitySystem/WorkerTE.h"

class Data;

class PMRBot {
private:
	MapTools m_mapTools;
	Data* pData;
	TaskEmitter m_WorkerTE = WorkerTE(); // Empty TE for now, should serve as a model for the others.
	//TaskEmitter m_ArmyTE;
	//...

	EventManagerTE m_EventTE = EventManagerTE();
	BT_NODE* pIdleManagerBT;
	std::map<std::shared_ptr<Task>, std::map<std::shared_ptr<UnitAgent>, float>> m_taskToAgentInterest;

	void runBotLoop();
	void taskAttribuer();

public:
	PMRBot();



	void drawDebugInformation();

	// functions that are triggered by various BWAPI events from main.cpp
	void onStart();
	void onFrame();
	void onEnd(bool isWinner);
	void onUnitDestroy(BWAPI::Unit unit);
	void onUnitMorph(BWAPI::Unit unit);
	void onSendText(std::string text);
	void onUnitCreate(BWAPI::Unit unit);
	void onUnitComplete(BWAPI::Unit unit);
	void onUnitShow(BWAPI::Unit unit);
	void onUnitHide(BWAPI::Unit unit);
	void onUnitRenegade(BWAPI::Unit unit);
};