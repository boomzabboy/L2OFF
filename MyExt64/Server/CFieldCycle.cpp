
#include <Server/CFieldCycle.h>
#include <Common/Utils.h>

void CFieldCycle::Init()
{
	WriteInstructionCall(0x6203D1, reinterpret_cast<UINT32>(_OnStepChangedWrapper));
	WriteInstructionCall(0x62082B, reinterpret_cast<UINT32>(_OnStepChangedWrapper));
}

void CFieldCycle::_OnStepChangedWrapper(CFieldCycle *self, int step, int time, bool b)
{
	reinterpret_cast<void(*)(CFieldCycle*, int, int, bool)>(0x61F64C)(self, step, time, b);
	if (self->id == 1) {
		self->lastPointChangeTime = time;
	}
}

