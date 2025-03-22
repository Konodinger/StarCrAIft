#include "BT_ACTION_ASK_FOR_NEW_PYLONS.h"
#include <BWAPI.h>
#include "Data.h"

std::string BT_ACTION_ASK_FOR_NEW_PYLONS::GetDescription()
{
	return "Ask for new pylons.";
}

BT_NODE::State BT_ACTION_ASK_FOR_NEW_PYLONS::Evaluate(void* data)
{
	Data* pData = static_cast<Data*>(data);
	if (pData->askingForNewPylons == Data::UNNEEDED)
		pData->askingForNewPylons = Data::REQUESTED;
	return SUCCESS;
}