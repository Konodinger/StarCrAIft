#include "BT_ACTION_EMPTY_BT.h"


BT_ACTION_EMPTY_BT::BT_ACTION_EMPTY_BT(std::string name, BT_NODE* parent)
    : BT_ACTION(name, parent) {}

BT_NODE::State BT_ACTION_EMPTY_BT::Evaluate(void* data)
{
    return ReturnState(DoNothing(data));
}


std::string BT_ACTION_EMPTY_BT::GetDescription()
{
    return "EMPTY BT";
}


BT_NODE::State BT_ACTION_EMPTY_BT::DoNothing(void* data)
{
    return SUCCESS;
}
