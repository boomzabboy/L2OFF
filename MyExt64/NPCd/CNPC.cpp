
#include <NPCd/CNPC.h>
#include <NPCd/NPCFunction.h>
#include <NPCd/CreatureData2.h>
#include <NPCd/CreatureData2Type.h>
#include <Common/Utils.h>
#include <Common/CLog.h>

namespace NPC {

void CNPC::Init()
{
	WriteMemoryDWORD(0x401602 + 8, sizeof(CNPC));
	WriteMemoryDWORD(0x408D53 + 1, sizeof(CNPC));
	WriteMemoryDWORD(0x408D9E + 1, sizeof(CNPC));
	WriteMemoryDWORD(0x578147 + 1, sizeof(CNPC));
	WriteMemoryDWORD(0x5781BF + 1, sizeof(CNPC));
	WriteMemoryDWORD(0x590709 + 1, sizeof(CNPC));
	WriteInstructionCall(0x408B18 + 0x255, reinterpret_cast<UINT32>(Constructor));
	WriteInstructionCall(0x408B18 + 0x2A0, reinterpret_cast<UINT32>(Constructor));
	WriteInstructionCall(0x578134 + 0x2C, reinterpret_cast<UINT32>(Constructor));
	WriteInstructionCall(0x5781AC + 0x2C, reinterpret_cast<UINT32>(Constructor));
	WriteInstructionCall(0x5903FC + 0x327, reinterpret_cast<UINT32>(Constructor));
	WriteInstructionCall(0x4E532C + 0xC, reinterpret_cast<UINT32>(Destructor));
	WriteMemoryDWORD(0x420AAD + 1, 8 * (Type::TYPES_END + 2));
	WriteMemoryDWORD(0x420AC1 + 2, 8 * Type::TYPES_END);
	WriteMemoryDWORD(0x420ACF + 3, 8 * Type::TYPES_END);
	WriteMemoryDWORD(0x420ADA + 3, 8 * (Type::TYPES_END + 1));
	WriteMemoryBYTE(0x422E1C + 3, Type::TYPES_END);
	WriteMemoryBYTE(0x57AE9F + 2, Type::TYPES_END);
	WriteInstructionCall(0x57AEA8, reinterpret_cast<UINT32>(GetTypeWrapper));
	WriteMemoryBYTE(0x5752D9 + 2, Type::TYPES_END - 1);
	WriteInstructionCall(0x5752E4, reinterpret_cast<UINT32>(GetTypeWrapper));
	WriteMemoryBYTE(0x575305 + 2, Type::TYPES_END);
	WriteMemoryBYTE(0x575973 + 3, Type::TYPES_END - 1);
	WriteInstructionCall(0x57597F, reinterpret_cast<UINT32>(GetTypeWrapper));
	WriteMemoryBYTE(0x5759EC + 3, Type::TYPES_END);
	WriteMemoryQWORD(0x690D48, reinterpret_cast<UINT32>(RegisterVariables));
	WriteInstructionCall(0x57AE8F, reinterpret_cast<UINT32>(RegisterTypes));
}

void CNPC::RegisterVariable(void *obj, void *registry, const wchar_t *name, size_t offset, UINT32 fn)
{
	reinterpret_cast<void(*)(void*, const wchar_t*, size_t, char*)>(fn)(
		registry, name, offset, reinterpret_cast<char*>(obj) + offset - 0x28);
}

void CNPC::RegisterVariables(void *obj, void *registry)
{
	reinterpret_cast<void(*)(void*, void*)>(0x4CD200)(obj, registry);
	RegisterVariable(obj, registry, L"i_ai5", offsetof(CNPC, i_ai5), 0x481A98);
	RegisterVariable(obj, registry, L"i_ai6", offsetof(CNPC, i_ai6), 0x481A98);
	RegisterVariable(obj, registry, L"i_ai7", offsetof(CNPC, i_ai7), 0x481A98);
	RegisterVariable(obj, registry, L"i_ai8", offsetof(CNPC, i_ai8), 0x481A98);
	RegisterVariable(obj, registry, L"i_ai9", offsetof(CNPC, i_ai9), 0x481A98);
	RegisterVariable(obj, registry, L"i_quest5", offsetof(CNPC, i_quest5), 0x481A98);
	RegisterVariable(obj, registry, L"i_quest6", offsetof(CNPC, i_quest6), 0x481A98);
	RegisterVariable(obj, registry, L"i_quest7", offsetof(CNPC, i_quest7), 0x481A98);
	RegisterVariable(obj, registry, L"i_quest8", offsetof(CNPC, i_quest8), 0x481A98);
	RegisterVariable(obj, registry, L"i_quest9", offsetof(CNPC, i_quest9), 0x481A98);
	RegisterVariable(obj, registry, L"sm2", offsetof(CNPC, sm2), reinterpret_cast<UINT32>(
		CreatureData2Type::RegisterVariable));
}

void CNPC::RegisterTypes()
{
	reinterpret_cast<void(*)()>(0x57ADD8)();
	CreatureData2Type *type = new CreatureData2Type();
	type->type = Type::TYPE_CREATURE2;
	type->name = L"CreatureData2";
	void *ptr = reinterpret_cast<void*(*)()>(0x420A74)();
	*reinterpret_cast<void**(*)(void*, Type::TypeID)>(0x422E0C)(ptr, Type::TYPE_CREATURE2) = type;
}

CNPC* __cdecl CNPC::Constructor(CNPC *self)
{
	CNPC *ret = reinterpret_cast<CNPC*(*)(CNPC*)>(0x4E4B64)(self);
	ret->sm2 = new CreatureData2();
	return ret;
}

CNPC* __cdecl CNPC::Destructor(CNPC *self, bool isMemoryFreeUsed)
{
	delete self->sm2;
	return reinterpret_cast<CNPC*(*)(CNPC*, bool)>(0x4CC184)(self, isMemoryFreeUsed);
}

void** CNPC::GetTypeWrapper(void *registry, int type)
{
	static UINT64 zero = 0;
	switch (type) {
	case Type::TYPE_NPCEVENT:
	case Type::TYPE_MAKEREVENT:
		return reinterpret_cast<void**>(&zero);
	}
	return reinterpret_cast<void**(*)(void*, int)>(0x422E0C)(registry, type);
}

CompileTimeOffsetCheck(CNPC, sm2, 0x15C0);

} // namespace NPC

