#include "ArmyTE.h"
#include "BT_ACTION_EXECUTE_METHOD.h"

#include "BT.h"

#include "Data.h"
#include "Tools.h"	

#include "SoldierAttackBaseTask.h"

bool ArmyTE::checkIfEnoughSoldiers(void* data) {
	Data* pData = static_cast<Data*>(data);

	// Check if enough soldiers (zealots and dragoons)

	const int zealotsOwned = Tools::CountUnitsOfType(BWAPI::UnitTypes::Protoss_Zealot, BWAPI::Broodwar->self()->getUnits());
	const int dragoonsOwned = Tools::CountUnitsOfType(BWAPI::UnitTypes::Protoss_Dragoon, BWAPI::Broodwar->self()->getUnits());

	if (zealotsOwned + dragoonsOwned - pData->numSoldierSent >= pData->nMinSoldiersBeforeAttack)
		return true;

	return false;
}

BT_NODE::State ArmyTE::emitCreateSoldiersTask(void* data) {
	Data* pData = static_cast<Data*>(data);

	std::cout << "Sending " << pData->nMinSoldiersBeforeAttack << " soldiers to attack" << std::endl;

	// Send pData->nMinSoldiersBeforeAttack soldiers to attack
	for (int i = 0; i < static_cast<Data*>(pData)->nMinSoldiersBeforeAttack; i++) {
		// Create a soldier task
		std::shared_ptr<Task> t = std::make_shared <SoldierAttackBaseTask>(pData->m_task_emitter_map[EmitterType::ARMY]);
		pData->m_task_emitter_map[EmitterType::ARMY]->emitTask(data, t);
	}

	pData->numSoldierSent += pData->nMinSoldiersBeforeAttack;

	return BT_NODE::State::SUCCESS;
}

void ArmyTE::createBT() {
	pTaskEmitterBT = new BT_DECORATOR("EntryPoint", nullptr);

	BT_SEQUENCER* pSequencer = new BT_SEQUENCER("sequencer", pTaskEmitterBT, 2);
	BT_DECO_RETURN_SUCCESS* pSoldierSection = new BT_DECO_RETURN_SUCCESS("SoldierSection", pSequencer);
	BT_DECO_CONDITION* pCheckIfEnoughSoldiers = new BT_DECO_CONDITION("CheckIfEnoughSoldiersCondition", pSoldierSection, checkIfEnoughSoldiers);

	// Emit create soldiers task
	BT_ACTION_EXECUTE_METHOD* pEmitCreateSoldiersTask = new BT_ACTION_EXECUTE_METHOD("EmitCreateSoldiersTask", pCheckIfEnoughSoldiers, emitCreateSoldiersTask);

}
