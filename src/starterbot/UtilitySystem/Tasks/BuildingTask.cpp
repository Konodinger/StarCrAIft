#include "BuildingTask.h"

BuildingTask::BuildingTask() : Task("Building") {

	m_compatibilityUnitAgentType = { UnitAgent::WORKER };

	m_taskBT = std::make_shared<BT_DECORATOR>(BT_DECORATOR("EntryPoint", nullptr));

	BT_NODE* pBuildAtPos = new BT_SEQUENCER("Build at pos", m_taskBT.get(), 2);

	//BT_NODE* pCondValidPos = new BT_DECO_COND_VALID_POSITION_TO_BUILD("Valid Position to build", pBuildAtPos, ...); // => CONDITION A CREER
	//
	//BT_NODE* pBuildWithRessources = new BT_SEQUENCER("Build with ressources", pBuildAtPos, 2);

	//BT_NODE* pCondEnoughRessources = new BT_DECO_COND_ENOUGH_RESSOURCES("Enough ressources to build", pBuildWithRessources, ...); // => CONDITION A CREER
	//BT_NODE* pBuild = new BT_ACTION_BUILD("Build", pBuildWithRessources, ...); // => ACTION A CREER

}