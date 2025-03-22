#include "BuildingTask.h"

BuildingTask::BuildingTask(std::shared_ptr<TaskEmitter> taskEmitter, BWAPI::UnitType type, std::shared_ptr<ResourcesManager> resourcesManager, BWAPI::TilePosition idealPosition)
	: Task("Building Task", taskEmitter), m_type(type) {

	m_compatibilityUnitAgentType = { UnitAgent::WORKER };

	//m_taskBT = std::make_shared<BT_DECORATOR>(BT_DECORATOR("EntryPoint", nullptr));

	m_taskBT = std::make_shared<BT_DECO_UNTIL_SUCCESS>("Building Task", nullptr);

	BT_NODE* buildBuildinNode = new BT_ACTION_BUILD_BUILDING("Build at pos", m_taskBT.get(), this, idealPosition);

	//BT_NODE* pBuildAtPos = new BT_SEQUENCER("Build at pos", m_taskBT.get(), 2);

	//BT_NODE* pCondValidPos = new BT_DECO_COND_VALID_POSITION_TO_BUILD("Valid Position to build", pBuildAtPos, ...); // => CONDITION A CREER
	//
	//BT_NODE* pBuildWithRessources = new BT_SEQUENCER("Build with ressources", pBuildAtPos, 2);

	//BT_NODE* pCondEnoughRessources = new BT_DECO_COND_ENOUGH_RESSOURCES("Enough ressources to build", pBuildWithRessources, ...); // => CONDITION A CREER
	//BT_NODE* pBuild = new BT_ACTION_BUILD("Build", pBuildWithRessources, ...); // => ACTION A CREER

}