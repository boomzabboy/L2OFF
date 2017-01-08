
#include <NPCd/Functions/CNPC_IsToggleSkillOnOff.h>
#include <Common/CLog.h>

CNPC_IsToggleSkillOnOff::CNPC_IsToggleSkillOnOff() :
	NPCFunction(L"IsToggleSkillOnOff", &IsToggleSkillOnOff)
{
}

void* CNPC_IsToggleSkillOnOff::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*, void*)>(functionPtr.functionPtr)(
		caller, params[0], params[1]);
}

void CNPC_IsToggleSkillOnOff::SetTypes()
{
	SetReturnType(TYPE_VOID);
	AddParameter(TYPE_CREATURE);
	AddParameter(TYPE_INT);
}

int CNPC_IsToggleSkillOnOff::IsToggleSkillOnOff(CNPC *npc, CSharedCreatureData *target, int skillId)
{
    CLog::Add(CLog::Blue, L"CNPC::IsToggleSkillOnOff stub");
	return 0;
}

