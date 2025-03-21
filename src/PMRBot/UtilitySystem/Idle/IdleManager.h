#pragma once

#include <BT.h>
#include <memory>

namespace IdleManager {
	std::shared_ptr<BT_NODE> create() {
		std::shared_ptr<BT_NODE> pEntry = std::make_shared<BT_DECORATOR>(BT_DECORATOR("Entry Point", nullptr));
		BT_NODE* pActionGatherNearestMineral = new BT_ACTION_EXECUTE_METHOD("Action execute gatherNearestMaterial", pIdleManager.get(), std::bind(gatherNearestMineral, std::placeholders::_1, this));
		return pIdleManager;
	}
}
