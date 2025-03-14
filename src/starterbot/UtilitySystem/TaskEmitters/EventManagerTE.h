#pragma once

#include "TaskEmitter.h"

class Data;

class EventManagerTE : public TaskEmitter {
private:
	Data* pData;
public:
	EventManagerTE() {
		m_name = "Event Manager";
	};

	void setData(Data* pData) {
		this->pData = pData;
	}

	// LOT TO BE DONE: methods for task generation, reattribution, suppression, modification...

	// 

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