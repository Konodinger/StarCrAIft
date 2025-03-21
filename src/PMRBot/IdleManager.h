#pragma once

#include "Data.h"

class IdleManager {
public:
	IdleManager(Data* data) : pData(data) {}
private:
	Data* pData;
};

