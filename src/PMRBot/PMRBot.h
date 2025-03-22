#pragma once

class PMRBot;

#include <BWAPI.h>
#include "MapTools.h"
#include "Task.h"
#include "TaskEmitter.h"
#include "EventManagerTE.h"
#include "Idle/IdleManager.h"

class Data;

class PMRBot {
private:
	Data* pData;

	std::shared_ptr<IdleManager> m_IdleManager;
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