#include "BT_ACTION_EXECUTE_METHOD.h"



BT_ACTION_EXECUTE_METHOD::BT_ACTION_EXECUTE_METHOD(std::string name, BT_NODE* parent, std::function<State(void*)> actionMethod)
	: BT_ACTION(name, parent), m_actionMethod(actionMethod)
{ }

BT_NODE::State BT_ACTION_EXECUTE_METHOD::Evaluate(void* data)
{
	return ReturnState(m_actionMethod(data));
}

std::string BT_ACTION_EXECUTE_METHOD::GetDescription()
{
	return "METHOD EXECUTOR " + Name;
}
