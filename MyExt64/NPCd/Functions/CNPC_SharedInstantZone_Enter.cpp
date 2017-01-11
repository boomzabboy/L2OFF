
#include <NPCd/Functions/CNPC_SharedInstantZone_Enter.h>
#include <Common/CLog.h>

CNPC_SharedInstantZone_Enter::CNPC_SharedInstantZone_Enter() :
	NPCFunction(L"SharedInstantZone_Enter", &SharedInstantZone_Enter)
{
}

void* CNPC_SharedInstantZone_Enter::Call(void *caller, void **params)
{
	return reinterpret_cast<void*(*)(void*, void*, void*, void*, void*, void*, void*)>(functionPtr.functionPtr)(
		caller, params[0], params[1], params[2], params[3], params[4], params[5]);
}

void CNPC_SharedInstantZone_Enter::SetTypes()
{
	SetReturnType(Type::TYPE_VOID);
	AddParameter(Type::TYPE_CREATURE);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
	AddParameter(Type::TYPE_INT);
}

int CNPC_SharedInstantZone_Enter::SharedInstantZone_Enter(CNPC *npc, CSharedCreatureData *c, int inZoneTypeId, int enterType, int x, int y, int z)
{
    CLog::Add(CLog::Blue, L"CNPC::SharedInstantZone_Enter stub");
	return 0;
}

