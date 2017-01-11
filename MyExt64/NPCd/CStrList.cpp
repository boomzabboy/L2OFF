
#include <NPCd/CStrList.h>
#include <NPCd/NPCFunction.h>
#include <Common/Utils.h>

CStrList::CStrList()
{
}

void CStrList::RegisterFunctions(void *registry)
{
    NPCFunction::RegisterFunctions<0, Type::TYPE_STRLIST>(this, registry);
}

void CStrList::RegisterVariables(void *registry)
{
}

