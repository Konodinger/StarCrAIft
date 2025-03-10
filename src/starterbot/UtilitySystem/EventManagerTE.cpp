#include "EventManagerTE.h"

// Called when the bot starts!
void EventManagerTE::onStart() {

}

// Called on each frame of the game
void EventManagerTE::onFrame() {

}

// Called whenever the game ends and tells you if you won or not
void EventManagerTE::onEnd(bool isWinner) {

}

// Called whenever a unit is destroyed, with a pointer to the unit
void EventManagerTE::onUnitDestroy(BWAPI::Unit unit) {
	//if the unit is farming then remove it from data structure
	if (pData->unitsFarmingMinerals.contains(unit))
		pData->unitsFarmingMinerals.erase(unit);

	if (pData->unitAgentsList.contains(unit->getID()))
		pData->unitAgentsList.erase(unit->getID());
}

// Called whenever a unit is morphed, with a pointer to the unit
// Zerg units morph when they turn into other units
void EventManagerTE::onUnitMorph(BWAPI::Unit unit) {

}

// Called whenever a text is sent to the game by a user
void EventManagerTE::onSendText(std::string text) {

}

// Called whenever a unit is created, with a pointer to the destroyed unit
// Units are created in buildings like barracks before they are visible, 
// so this will trigger when you issue the build command for most units
void EventManagerTE::onUnitCreate(BWAPI::Unit unit) {
	// SIMPLIFIED, WILL NEED TO ADD UNITAGENTTYPES...

	auto pUnitAgent = UnitAgent::getUnitAgent(unit);
	pData->unitAgentsList[pUnitAgent->getUnit()->getID()] = pUnitAgent; // Warning, the unit isn't necessarily constructed yet
}

// Called whenever a unit finished construction, with a pointer to the unit
void EventManagerTE::onUnitComplete(BWAPI::Unit unit) {

}

// Called whenever a unit appears, with a pointer to the destroyed unit
// This is usually triggered when units appear from fog of war and become visible
void EventManagerTE::onUnitShow(BWAPI::Unit unit) {

}

// Called whenever a unit gets hidden, with a pointer to the destroyed unit
// This is usually triggered when units enter the fog of war and are no longer visible
void EventManagerTE::onUnitHide(BWAPI::Unit unit) {

}

// Called whenever a unit switches player control
// This usually happens when a dark archon takes control of a unit
void EventManagerTE::onUnitRenegade(BWAPI::Unit unit) {

}