#include "BT_DECO_MULTIPLEXER.h"


BT_DECO_MULTIPLEXER::BT_DECO_MULTIPLEXER(std::string name, BT_NODE* parent)
	: BT_DECORATOR(name, parent) {}

BT_NODE::State BT_DECO_MULTIPLEXER::Evaluate(void* data) {

	assert(Children && ChildrenCount == 3);
	BT_NODE::State childState = BT_DECORATOR::Evaluate(data);
	if (Children[0]->Evaluate(data)) return ReturnState(Children[1]->Evaluate(data));
	else return ReturnState(Children[2]->Evaluate(data));
}

std::string BT_DECO_MULTIPLEXER::GetDescription()
{
	return "DECO MULTIPLEXER";
}