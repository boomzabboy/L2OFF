
#include <NPCd/CNPCMaker.h>
#include <Common/Utils.h>

void CNPCMaker::Init()
{
	WriteMemoryDWORD(0x51248A + 8, sizeof(CNPCMaker));
	WriteMemoryDWORD(0x514E3E + 1, sizeof(CNPCMaker));
	WriteMemoryDWORD(0x53B981 + 1, sizeof(CNPCMaker));
	WriteMemoryDWORD(0x5777BF + 1, sizeof(CNPCMaker));
	WriteMemoryDWORD(0x577837 + 1, sizeof(CNPCMaker));
	WriteMemoryDWORD(0x5D5D98 + 1, sizeof(CNPCMaker));
	WriteMemoryQWORD(0x6B2A60, reinterpret_cast<UINT32>(RegisterVariables));
}

void CNPCMaker::RegisterVariable(void *obj, void *registry, const wchar_t *name, size_t offset, UINT64 fn)
{
	reinterpret_cast<void(*)(void*, const wchar_t*, size_t, char*)>(fn)(
		registry, name, offset, reinterpret_cast<char*>(obj) + offset - 0x18);
}

void CNPCMaker::RegisterVariables(void *obj, void *registry)
{
	reinterpret_cast<void(*)(void*, void*)>(0x543C5C)(obj, registry);
	RegisterVariable(obj, registry, L"i_ai5", offsetof(CNPCMaker, i_ai5), 0x423160);
	RegisterVariable(obj, registry, L"i_ai6", offsetof(CNPCMaker, i_ai6), 0x423160);
	RegisterVariable(obj, registry, L"i_ai7", offsetof(CNPCMaker, i_ai7), 0x423160);
	RegisterVariable(obj, registry, L"i_ai8", offsetof(CNPCMaker, i_ai8), 0x423160);
	RegisterVariable(obj, registry, L"i_ai9", offsetof(CNPCMaker, i_ai9), 0x423160);
	RegisterVariable(obj, registry, L"i_quest5", offsetof(CNPCMaker, i_quest5), 0x481A98);
	RegisterVariable(obj, registry, L"i_quest6", offsetof(CNPCMaker, i_quest6), 0x481A98);
	RegisterVariable(obj, registry, L"i_quest7", offsetof(CNPCMaker, i_quest7), 0x481A98);
	RegisterVariable(obj, registry, L"i_quest8", offsetof(CNPCMaker, i_quest8), 0x481A98);
	RegisterVariable(obj, registry, L"i_quest9", offsetof(CNPCMaker, i_quest9), 0x481A98);
}

CompileTimeOffsetCheck(CNPCMaker, i_quest9, 0x1448);

