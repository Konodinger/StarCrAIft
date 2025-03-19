#include "BT_ACTION_ATTACK_CLOSEST_ENEMY.h"
#include <BWAPI.h>

std::string BT_ACTION_ATTACK_CLOSEST_ENEMY::GetDescription()
{
	return "Attack the closest enemy.";
}

BT_NODE::State BT_ACTION_ATTACK_CLOSEST_ENEMY::Evaluate(void* data)
{
	// TO IMPLEMENT
	BWAPI::Broodwar->printf("BT_ACTION_ATTACK_CLOSEST_ENEMY NOT IMPLEMENTED");
	return FAILURE;
}