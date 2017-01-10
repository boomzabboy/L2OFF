
#include <NPCd/NPCFunction.h>
#include <NPCd/Functions/CNPC_ShowBuySell.h>
#include <NPCd/Functions/CNPC_Marry.h>
#include <NPCd/Functions/CNPC_Divorce.h>
#include <NPCd/Functions/CNPC_GlobalAnnounce.h>
#include <NPCd/Functions/CNPC_FastBuff.h>
#include <NPCd/Functions/CNPC_SetAbilityItemDrop.h>
#include <NPCd/Functions/CNPC_TeleportTo.h>
#include <NPCd/Functions/CNPC_ChangeMasterName.h>
#include <NPCd/Functions/CNPC_GetNPCLogByID.h>
#include <NPCd/Functions/CNPC_IncreaseNPCLogByID.h>
#include <NPCd/Functions/CNPC_SetAttackable.h>
#include <NPCd/Functions/CNPC_ChangeDir.h>
#include <NPCd/Functions/CNPC_ChangeNickName.h>
#include <NPCd/Functions/CNPC_Whisper.h>
#include <NPCd/Functions/CNPC_BlockTimer.h>
#include <NPCd/Functions/CNPC_UnBlockTimer.h>
#include <NPCd/Functions/CNPC_AddLogByNpc2.h>
#include <NPCd/Functions/CNPC_ChangeUserTalkTarget.h>
#include <NPCd/Functions/CNPC_ChangeNPCState.h>
#include <NPCd/Functions/CNPC_ShowOlympiadMatchList.h>
#include <NPCd/Functions/CNPC_ChangeMoveType2.h>
#include <NPCd/Functions/CNPC_FixMoveType.h>
#include <NPCd/Functions/CNPC_SendPost.h>
#include <NPCd/Functions/CNPC_RegisterAsBirthdayManager.h>
#include <NPCd/Functions/CNPC_IsToggleSkillOnOff.h>
#include <NPCd/Functions/CNPC_GiveEventItem2.h>
#include <NPCd/Functions/CNPC_IsVipUser.h>
#include <NPCd/Functions/CNPC_SetVipUser.h>
#include <NPCd/Functions/GlobalObject_BroadcastOnScreenNpcString.h>
#include <NPCd/Functions/GlobalObject_ShowOnScreenNpcStringMsg.h>
#include <NPCd/Functions/GlobalObject_OwnItemCount2.h>
#include <NPCd/Functions/GlobalObject_OwnItemCountEx2.h>
#include <NPCd/Functions/CIntList_SetMaxSize.h>
#include <NPCd/Functions/CIntList_GetItemIndexNext.h>
#include <Common/Utils.h>

void NPCFunction::AddFunctions()
{
	AddFunction<Type::TYPE_NPC, CNPC_ShowBuySell>();
	AddFunction<Type::TYPE_NPC, CNPC_Marry>();
	AddFunction<Type::TYPE_NPC, CNPC_Divorce>();
	AddFunction<Type::TYPE_NPC, CNPC_GlobalAnnounce>();
	AddFunction<Type::TYPE_NPC, CNPC_FastBuff>();
	AddFunction<Type::TYPE_NPC, CNPC_SetAbilityItemDrop>();
	AddFunction<Type::TYPE_NPC, CNPC_TeleportTo>();
	AddFunction<Type::TYPE_NPC, CNPC_ChangeMasterName>();
	AddFunction<Type::TYPE_NPC, CNPC_GetNPCLogByID>();
	AddFunction<Type::TYPE_NPC, CNPC_IncreaseNPCLogByID>();
	AddFunction<Type::TYPE_NPC, CNPC_SetAttackable>();
	AddFunction<Type::TYPE_NPC, CNPC_ChangeDir>();
	AddFunction<Type::TYPE_NPC, CNPC_ChangeNickName>();
	AddFunction<Type::TYPE_NPC, CNPC_Whisper>();
	AddFunction<Type::TYPE_NPC, CNPC_BlockTimer>();
	AddFunction<Type::TYPE_NPC, CNPC_UnBlockTimer>();
	AddFunction<Type::TYPE_NPC, CNPC_AddLogByNpc2>();
	AddFunction<Type::TYPE_NPC, CNPC_ChangeUserTalkTarget>();
	AddFunction<Type::TYPE_NPC, CNPC_ChangeNPCState>();
	AddFunction<Type::TYPE_NPC, CNPC_ShowOlympiadMatchList>();
	AddFunction<Type::TYPE_NPC, CNPC_ChangeMoveType2>();
	AddFunction<Type::TYPE_NPC, CNPC_FixMoveType>();
	AddFunction<Type::TYPE_NPC, CNPC_SendPost>();
	AddFunction<Type::TYPE_NPC, CNPC_RegisterAsBirthdayManager>();
	AddFunction<Type::TYPE_NPC, CNPC_IsToggleSkillOnOff>();
	AddFunction<Type::TYPE_NPC, CNPC_GiveEventItem2>();
	AddFunction<Type::TYPE_NPC, CNPC_IsVipUser>();
	AddFunction<Type::TYPE_NPC, CNPC_SetVipUser>();
	AddFunction<Type::TYPE_GLOBALOBJECT, GlobalObject_BroadcastOnScreenNpcString>();
	AddFunction<Type::TYPE_GLOBALOBJECT, GlobalObject_ShowOnScreenNpcStringMsg>();
	AddFunction<Type::TYPE_GLOBALOBJECT, GlobalObject_OwnItemCount2>();
	AddFunction<Type::TYPE_GLOBALOBJECT, GlobalObject_OwnItemCountEx2>();
	AddFunction<Type::TYPE_INTLIST, CIntList_SetMaxSize>();
	AddFunction<Type::TYPE_INTLIST, CIntList_GetItemIndexNext>();
}

void NPCFunction::Init()
{
	WriteMemoryQWORD(0x6B2A58, reinterpret_cast<UINT32>(reinterpret_cast<void(*)()>(
		RegisterFunctions<0x546CD8, Type::TYPE_NPCMAKER>)));

	WriteMemoryQWORD(0x690D40, reinterpret_cast<UINT32>(reinterpret_cast<void(*)()>(
		RegisterFunctions<0x4F186C, Type::TYPE_NPC>)));

	WriteMemoryQWORD(0x65E470, reinterpret_cast<UINT32>(reinterpret_cast<void(*)()>(
		RegisterFunctions<0x468CB0, Type::TYPE_GLOBALOBJECT>)));

	WriteMemoryQWORD(0x68F118, reinterpret_cast<UINT32>(reinterpret_cast<void(*)()>(
		RegisterFunctions<0x4E48DC, Type::TYPE_INTLIST>)));

	AddFunctions();
}

std::list<NPCFunction*> NPCFunction::functionsToRegister[Type::TYPES_END];

NPCFunction::NPCFunction(const wchar_t *name, void *functionPtr)
{
	memset(padding0x0008, 0, 8);
	memset(padding0x0048, 0, 0x18);
	this->name = name;
	this->functionPtr.functionPtr = functionPtr;
}

NPCFunction::~NPCFunction()
{
}

void* NPCFunction::CallFn(void *caller, void **params)
{
	UINT64 caller_ = static_cast<UINT64>(static_cast<INT64>(functionPtr.unknown));
	caller_ += reinterpret_cast<UINT64>(caller);
	return Call(reinterpret_cast<void*>(caller_), params);
}

void NPCFunction::SetReturnType(Type::TypeID type)
{
	void *ptr = reinterpret_cast<void*(*)()>(0x420A74)();
	returnType = *reinterpret_cast<void**(*)(void*, Type::TypeID)>(0x422E0C)(ptr, type);
}

void NPCFunction::AddParameter(Type::TypeID type)
{
	void *ptr = reinterpret_cast<void*(*)()>(0x420A74)();
	void *parameter = reinterpret_cast<void*(*)(void*, Type::TypeID)>(0x422E0C)(ptr, type);
	reinterpret_cast<void(*)(void**, void*)>(0x4583D4)(&parameters, parameter);
}

void NPCFunction::Register(void *registry)
{
	SetTypes();
	reinterpret_cast<void(*)(void*, NPCFunction*)>(0x574DD8)(registry, this);
}

NPCFunctionPtr::NPCFunctionPtr()
{
	memset(this, 0, sizeof(*this));
}

CompileTimeOffsetCheck(NPCFunctionPtr, unknown, 0x8);
CompileTimeOffsetCheck(NPCFunction, name, 0x10);
CompileTimeOffsetCheck(NPCFunction, padding0x0048, 0x48);
CompileTimeOffsetCheck(NPCFunction, functionPtr, 0x60);

