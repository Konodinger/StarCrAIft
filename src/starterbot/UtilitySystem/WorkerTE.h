#pragma once

#include "TaskEmitter.h"

class WorkerTE : public TaskEmitter {
public:
	WorkerTE() { m_name = "WorkerTE"; };
};