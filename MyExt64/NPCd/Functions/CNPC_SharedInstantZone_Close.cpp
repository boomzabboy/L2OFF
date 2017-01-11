
#include <NPCd/Functions/CNPC_SharedInstantZone_Close.h>
#include <Common/CLog.h>

CNPC_SharedInstantZone_Close::CNPC_SharedInstantZone_Close() :
	NPCFunction(L"SharedInstantZone_Close", &SharedInstantZone_Close)
{
}

void* CNPC_SharedInstantZone_Close::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*)>(functionPtr.functionPtr)(
		caller, params[0]);
}

void CNPC_SharedInstantZone_Close::SetTypes()
{
	SetReturnType(Type::TYPE_VOID);
	AddParameter(Type::TYPE_INT);
}

int CNPC_SharedInstantZone_Close::SharedInstantZone_Close(CNPC *npc, int inZoneTypeId)
{
    CLog::Add(CLog::Blue, L"CNPC::SharedInstantZone_Close stub");
	return 0;
}

