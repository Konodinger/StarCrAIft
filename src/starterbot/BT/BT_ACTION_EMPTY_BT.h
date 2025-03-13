#pragma once
#include <cassert>
#include "BT.h"

//Do nothing (for undefined BT)
//--------------------
class BT_ACTION_EMPTY_BT : public BT_ACTION {
public:
    BT_ACTION_EMPTY_BT(std::string name, BT_NODE* parent);
private:
    State Evaluate(void* data) override;
    std::string GetDescription() override;

    static BT_NODE::State DoNothing(void* data);
};
//----------