
#include <NPCd/CNPC.h>
#include <NPCd/NPCFunction.h>
#include <NPCd/CreatureData2.h>
#include <NPCd/CreatureData2Type.h>
#include <NPCd/CIntListType.h>
#include <NPCd/CStrList.h>
#include <NPCd/CStrListType.h>
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

	WriteMemoryDWORD(0x579267 + 3, Type::TYPE_NPCEVENT * 8);
	WriteMemoryDWORD(0x57996F + 3, Type::TYPE_NPCEVENT * 8);
	WriteMemoryDWORD(0x57AED6 + 3, Type::TYPE_NPCEVENT * 8);
	WriteMemoryDWORD(0x57AEEB + 3, Type::TYPE_NPCEVENT * 8);
	WriteMemoryDWORD(0x5BE261 + 3, Type::TYPE_NPCEVENT * 8);
	WriteMemoryDWORD(0x5C9BB9 + 3, Type::TYPE_NPCEVENT * 8);

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
	WriteMemoryQWORD(0x6CAFE0, reinterpret_cast<UINT32>(RegisterSharedCreatureVariables));

	WriteInstructionCall(0x5C7ABA, reinterpret_cast<UINT32>(UnBlockTimerFix));
	WriteInstructionCall(0x5C7FBF, reinterpret_cast<UINT32>(UnBlockTimerFix));
	WriteInstructionCall(0x5C89B4, reinterpret_cast<UINT32>(UnBlockTimerFix));

	CompileTimeOffsetCheck(Ext, sm2, 0x15C0 - offsetof(CNPC, ext));
	CompileTimeOffsetCheck(Ext, db_str_list10, 0x1930 - offsetof(CNPC, ext));
}

void CNPC::RegisterVariable(void *obj, void *registry, const wchar_t *name, size_t offset, UINT32 fn)
{
	reinterpret_cast<void(*)(void*, const wchar_t*, size_t, char*)>(fn)(
		registry, name, offset, reinterpret_cast<char*>(obj) + offset - 0x28);
}

void CNPC::RegisterVariables(void *obj, void *registry)
{
	reinterpret_cast<void(*)(void*, void*)>(0x4CD200)(obj, registry);
	RegisterVariable(obj, registry, L"i_ai5", offsetof(CNPC, ext.i_ai5), 0x481A98);
	RegisterVariable(obj, registry, L"i_ai6", offsetof(CNPC, ext.i_ai6), 0x481A98);
	RegisterVariable(obj, registry, L"i_ai7", offsetof(CNPC, ext.i_ai7), 0x481A98);
	RegisterVariable(obj, registry, L"i_ai8", offsetof(CNPC, ext.i_ai8), 0x481A98);
	RegisterVariable(obj, registry, L"i_ai9", offsetof(CNPC, ext.i_ai9), 0x481A98);
	RegisterVariable(obj, registry, L"i_quest5", offsetof(CNPC, ext.i_quest5), 0x481A98);
	RegisterVariable(obj, registry, L"i_quest6", offsetof(CNPC, ext.i_quest6), 0x481A98);
	RegisterVariable(obj, registry, L"i_quest7", offsetof(CNPC, ext.i_quest7), 0x481A98);
	RegisterVariable(obj, registry, L"i_quest8", offsetof(CNPC, ext.i_quest8), 0x481A98);
	RegisterVariable(obj, registry, L"i_quest9", offsetof(CNPC, ext.i_quest9), 0x481A98);
	RegisterVariable(obj, registry, L"sm2", offsetof(CNPC, ext.sm2), reinterpret_cast<UINT32>(
		CreatureData2Type::RegisterVariable));
	RegisterVariable(obj, registry, L"str_list", offsetof(CNPC, ext.str_list), reinterpret_cast<UINT32>(
		CStrListType::RegisterVariable));
	RegisterVariable(obj, registry, L"db_int_list", offsetof(CNPC, ext.db_int_list), reinterpret_cast<UINT32>(
		CIntListType::RegisterVariable));
	RegisterVariable(obj, registry, L"db_str_list1", offsetof(CNPC, ext.db_str_list1), reinterpret_cast<UINT32>(
		CStrListType::RegisterVariable));
	RegisterVariable(obj, registry, L"db_str_list2", offsetof(CNPC, ext.db_str_list2), reinterpret_cast<UINT32>(
		CStrListType::RegisterVariable));
	RegisterVariable(obj, registry, L"db_str_list3", offsetof(CNPC, ext.db_str_list3), reinterpret_cast<UINT32>(
		CStrListType::RegisterVariable));
	RegisterVariable(obj, registry, L"db_str_list4", offsetof(CNPC, ext.db_str_list4), reinterpret_cast<UINT32>(
		CStrListType::RegisterVariable));
	RegisterVariable(obj, registry, L"db_str_list5", offsetof(CNPC, ext.db_str_list5), reinterpret_cast<UINT32>(
		CStrListType::RegisterVariable));
	RegisterVariable(obj, registry, L"db_str_list6", offsetof(CNPC, ext.db_str_list6), reinterpret_cast<UINT32>(
		CStrListType::RegisterVariable));
	RegisterVariable(obj, registry, L"db_str_list7", offsetof(CNPC, ext.db_str_list7), reinterpret_cast<UINT32>(
		CStrListType::RegisterVariable));
	RegisterVariable(obj, registry, L"db_str_list8", offsetof(CNPC, ext.db_str_list8), reinterpret_cast<UINT32>(
		CStrListType::RegisterVariable));
	RegisterVariable(obj, registry, L"db_str_list9", offsetof(CNPC, ext.db_str_list9), reinterpret_cast<UINT32>(
		CStrListType::RegisterVariable));
	RegisterVariable(obj, registry, L"db_str_list10", offsetof(CNPC, ext.db_str_list10), reinterpret_cast<UINT32>(
		CStrListType::RegisterVariable));
}

void CNPC::RegisterSharedCreatureVariables(void *obj, void *registry)
{
	reinterpret_cast<void(*)(void*, void*)>(0x593D44)(obj, registry);
	RegisterSharedCreatureVariable(obj, registry, L"absolute_defence", offsetof(CSharedCreatureData, absolute_defence), 0x423160);
	RegisterSharedCreatureVariable(obj, registry, L"no_attack_damage", offsetof(CSharedCreatureData, no_attack_damage), 0x423160);
	RegisterSharedCreatureVariable(obj, registry, L"quest_inv_items", offsetof(CSharedCreatureData, quest_inv_items), 0x423160);
	RegisterSharedCreatureVariable(obj, registry, L"m_nPvP_Event_Kills", offsetof(CSharedCreatureData, m_nPvP_Event_Kills), 0x423160);
	RegisterSharedCreatureVariable(obj, registry, L"m_nPvP_Event_Deaths", offsetof(CSharedCreatureData, m_nPvP_Event_Deaths), 0x423160);
	RegisterSharedCreatureVariable(obj, registry, L"m_nPvP_Event_EventId", offsetof(CSharedCreatureData, m_nPvP_Event_EventId), 0x423160);
	RegisterSharedCreatureVariable(obj, registry, L"m_nPvP_Event_TeamId", offsetof(CSharedCreatureData, m_nPvP_Event_TeamId), 0x423160);
	RegisterSharedCreatureVariable(obj, registry, L"m_nPvP_Event_KillsSequenced", offsetof(CSharedCreatureData, m_nPvP_Event_KillsSequenced), 0x423160);
	RegisterSharedCreatureVariable(obj, registry, L"m_nPvP_Event_MemberId", offsetof(CSharedCreatureData, m_nPvP_Event_MemberId), 0x423160);
	RegisterSharedCreatureVariable(obj, registry, L"m_nMultiBoxSessionCount", offsetof(CSharedCreatureData, m_nMultiBoxSessionCount), 0x423160);
	RegisterSharedCreatureVariable(obj, registry, L"wedding_partner_name", offsetof(CSharedCreatureData, wedding_partner_name), 0x423238);
	RegisterSharedCreatureVariable(obj, registry, L"wedding_relation", offsetof(CSharedCreatureData, wedding_relation), 0x423160);
}

void CNPC::RegisterSharedCreatureVariable(void *obj, void *registry, const wchar_t *name, size_t offset, UINT32 fn)
{
	reinterpret_cast<void(*)(void*, const wchar_t*, size_t, char*)>(fn)(
		registry, name, offset, reinterpret_cast<char*>(obj) + offset);
}

void CNPC::RegisterTypes()
{
	reinterpret_cast<void(*)()>(0x57ADD8)();
	{
		CreatureData2Type *type = new CreatureData2Type();
		type->type = Type::TYPE_CREATURE2;
		type->name = L"CreatureData2";
		void *ptr = reinterpret_cast<void*(*)()>(0x420A74)();
		*reinterpret_cast<void**(*)(void*, Type::TypeID)>(0x422E0C)(ptr, Type::TYPE_CREATURE2) = type;
	}
	{
		CStrListType *type = new CStrListType();
		type->type = Type::TYPE_STRLIST;
		type->name = L"StrList";
		void *ptr = reinterpret_cast<void*(*)()>(0x420A74)();
		*reinterpret_cast<void**(*)(void*, Type::TypeID)>(0x422E0C)(ptr, Type::TYPE_STRLIST) = type;
	}
}

CNPC* __cdecl CNPC::Constructor(CNPC *self)
{
	CNPC *ret = reinterpret_cast<CNPC*(*)(CNPC*)>(0x4E4B64)(self);
	new (&ret->ext) Ext();
	return ret;
}

CNPC::Ext::Ext()
{
	sm2 = new CreatureData2();
}

CNPC* __cdecl CNPC::Destructor(CNPC *self, bool isMemoryFreeUsed)
{
	self->ext.~Ext();
	return reinterpret_cast<CNPC*(*)(CNPC*, bool)>(0x4CC184)(self, isMemoryFreeUsed);
}

CNPC::Ext::~Ext()
{
	delete sm2;
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

void* __cdecl CNPC::UnBlockTimerFix(void *a, wchar_t *fn)
{
	if (!wcscmp(fn, L"UnBlockTimer")) {
		fn[2] = L'b';
	}
	return reinterpret_cast<void*(*)(void*, wchar_t*)>(0x5716EC)(a, fn);
}

CompileTimeOffsetCheck(CNPC, ext, 0x1570);

} // namespace NPC

