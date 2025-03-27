#include "BT_DECO_MULTIPLEXER.h"
#include <iostream>

BT_DECO_MULTIPLEXER::BT_DECO_MULTIPLEXER(std::string name, BT_NODE* parent)
	: BT_NODE(name, parent, 3) {}

BT_NODE::State BT_DECO_MULTIPLEXER::Evaluate(void* data) {

	if (!(Children && ChildrenCount == 3)) {
		std::cout << "Error! The Multiplexer was called but doesn't have three well-defined child.\n";
	}
	//BT_NODE::State childState = BT_NODE::Evaluate(data);
	if (Children[0]->Evaluate(data) == BT_NODE::SUCCESS) return ReturnState(Children[1]->Evaluate(data));
	else return ReturnState(Children[2]->Evaluate(data));
}

std::string BT_DECO_MULTIPLEXER::GetDescription()
{
	return "DECO MULTIPLEXER";
}