#include "BT_ACTION_EMIT_CREATE_PYLON_TASK.h"
#include <functional>
#include "Data.h"
#include "CreateBuildingTask.h"


BT_ACTION_EMIT_CREATE_PYLON_TASK::BT_ACTION_EMIT_CREATE_PYLON_TASK(std::string name, BT_NODE* parent, TaskEmitter* taskEmitter)
	: BT_ACTION_EXECUTE_METHOD(name, parent, std::bind(emitCreatePylonTask, std::placeholders::_1, taskEmitter))
{ }

std::string BT_ACTION_EMIT_CREATE_PYLON_TASK::GetDescription()
{
	return "EMIT CreatePylonTask";
}


BT_NODE::State BT_ACTION_EMIT_CREATE_PYLON_TASK::emitCreatePylonTask(void* data, TaskEmitter* pTaskEmitter) {
	//TODO
	Data* pData = static_cast<Data*>(data);
	std::shared_ptr<TaskEmitter> te = pData->m_task_emitter_map[EmitterType::WORKER];
	std::shared_ptr<Task> t = std::make_shared<CreateBuildingTask>(te, BWAPI::UnitTypes::Protoss_Pylon);
	te->emitTask(data, t);
	return BT_NODE::State::SUCCESS;
}