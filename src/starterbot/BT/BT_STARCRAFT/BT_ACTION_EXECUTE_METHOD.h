#pragma once

#include <functional>
#include "BT_ACTION.h"

class BT_ACTION_EXECUTE_METHOD : public BT_ACTION
{
public:
	BT_ACTION_EXECUTE_METHOD(std::string name, BT_NODE* parent, std::function<State(void*)> actionMethod);

private:
	State Evaluate(void* data) override;
	std::string GetDescription() override;

	std::function<State(void*)> m_actionMethod;
};