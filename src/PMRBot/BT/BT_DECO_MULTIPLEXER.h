#pragma once
#include <cassert>
#include "BT_DECORATOR.h"

// Evaluates the first child as a "conditional task". If it returns success then the second child task is run and its status is returned.
// Else, the third child task is run and its status is returned.
//--------------------
class BT_DECO_MULTIPLEXER : public BT_DECORATOR {
public:
    BT_DECO_MULTIPLEXER(std::string name, BT_NODE* parent);
    State Evaluate(void* data) override;
    std::string GetDescription() override;
};
//----------