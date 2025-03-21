#pragma once
#include <cassert>
#include <BWAPI.h>
#include "BT_ACTION_EXECUTE_METHOD.h"
#include "TaskEmitter.h"

//--------------------
class BT_ACTION_EMIT_CREATE_PYLON_TASK : public BT_ACTION_EXECUTE_METHOD {
public:
    BT_ACTION_EMIT_CREATE_PYLON_TASK(std::string name, BT_NODE* parent, TaskEmitter* taskEmitter);

private:
    std::string GetDescription() override;
    static BT_NODE::State emitCreatePylonTask(void* data, TaskEmitter* pTaskEmitter);
};
//----------