#pragma once

#include "BT_ACTION.h"

class BT_ACTION_ATTACK_CLOSEST_ENEMY : public BT_ACTION {
public:
	BT_ACTION_ATTACK_CLOSEST_ENEMY(std::string name, BT_NODE* parent)
		: BT_ACTION(name, parent) {};
private:
	State Evaluate(void* data) override;
	std::string GetDescription() override;
};