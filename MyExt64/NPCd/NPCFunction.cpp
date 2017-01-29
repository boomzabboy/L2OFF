
#include <NPCd/NPCFunction.h>
#include <NPCd/Compiler.h>
#include <NPCd/Functions/CNPC_ShowBuySell.h>
#include <NPCd/Functions/CNPC_Marry.h>
#include <NPCd/Functions/CNPC_Engage.h>
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
#include <NPCd/Functions/CNPC_UnblockTimer.h>
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
#include <NPCd/Functions/CNPC_ShowSystemMessage2.h>
#include <NPCd/Functions/CNPC_SharedInstantZone_Enter.h>
#include <NPCd/Functions/CNPC_SharedInstantZone_Close.h>
#include <NPCd/Functions/CNPC_SetDbCookieInt.h>
#include <NPCd/Functions/CNPC_SetDbCookieStr.h>
#include <NPCd/Functions/CNPC_GetDbCookieInt.h>
#include <NPCd/Functions/CNPC_GetDbCookieStr.h>
#include <NPCd/Functions/CNPC_DeleteDbCookie.h>
#include <NPCd/Functions/CNPC_DeleteDbCookieGroup.h>
#include <NPCd/Functions/CNPC_GetDbCookieGroupSize.h>
#include <NPCd/Functions/CNPC_LoadDbCookieGroup.h>
#include <NPCd/Functions/CNPC_LoadDbCookieAllGroups.h>
#include <NPCd/Functions/CNPC_GetDbCookieKeyInt.h>
#include <NPCd/Functions/CNPC_GetDbCookieKeyStr.h>
#include <NPCd/Functions/CNPC_GetDbCookieKeyFirst.h>
#include <NPCd/Functions/CNPC_GetDbCookieKeyNext.h>
#include <NPCd/Functions/CNPC_TeamEventSetStatus.h>
#include <NPCd/Functions/CNPC_TeamEventGetStatus.h>
#include <NPCd/Functions/CNPC_TeamEventGetTeamsCount.h>
#include <NPCd/Functions/CNPC_TeamSetColor.h>
#include <NPCd/Functions/CNPC_TeamAddMember.h>
#include <NPCd/Functions/CNPC_TeamRemoveMember.h>
#include <NPCd/Functions/CNPC_TeamRemoveAllMembers.h>
#include <NPCd/Functions/CNPC_TeamGetMembersCount.h>
#include <NPCd/Functions/CNPC_TeamGetMemberByIndex.h>
#include <NPCd/Functions/CNPC_TeamInstantTeleport.h>
#include <NPCd/Functions/CNPC_TeamSetRestartPoint.h>
#include <NPCd/Functions/CNPC_TeamShowSystemMessage2.h>
#include <NPCd/Functions/CNPC_ShowSystemMessage2.h>
#include <NPCd/Functions/CNPC_TeamEventSetParticipantConditions.h>
#include <NPCd/Functions/CNPC_TeamSetParticipantConditions.h>
#include <NPCd/Functions/CNPC_TeamSetMemberColor.h>
#include <NPCd/Functions/CNPC_TeamMoveMember.h>
#include <NPCd/Functions/CNPC_TeamEventAddMembersWithBalance.h>
#include <NPCd/Functions/CNPC_TeamInstantTeleportWithConditions.h>
#include <NPCd/Functions/CNPC_TeamGetInactiveCharacters.h>
#include <NPCd/Functions/CNPC_RegisterNpcConfirmDlg.h>
#include <NPCd/Functions/CNPC_SendNpcConfirmDlg.h>
#include <NPCd/Functions/CNPC_SendNpcConfirmDlgParty.h>
#include <NPCd/Functions/CNPC_SendNpcConfirmDlgAround.h>
#include <NPCd/Functions/CNPC_SetDbData.h>
#include <NPCd/Functions/CNPC_GetDbData.h>
#include <NPCd/Functions/CNPC_GetCountDbData.h>
#include <NPCd/Functions/CNPC_DelDbData.h>
#include <NPCd/Functions/CNPC_DelDbDataById.h>
#include <NPCd/Functions/GlobalObject_BroadcastOnScreenNpcString.h>
#include <NPCd/Functions/GlobalObject_ShowOnScreenNpcStringMsg.h>
#include <NPCd/Functions/GlobalObject_OwnItemCount2.h>
#include <NPCd/Functions/GlobalObject_OwnItemCountEx2.h>
#include <NPCd/Functions/GlobalObject_Dummy1.h>
#include <NPCd/Functions/GlobalObject_Dummy2.h>
#include <NPCd/Functions/GlobalObject_SendUIEventNpcStr.h>
#include <NPCd/Functions/GlobalObject_BroadCastUIEvent.h>
#include <NPCd/Functions/GlobalObject_BroadCastUIEventNpcStr.h>
#include <NPCd/Functions/GlobalObject_DebugLog.h>
#include <NPCd/Functions/CIntList_SetMaxSize.h>
#include <NPCd/Functions/CIntList_GetItemIndexNext.h>
#include <NPCd/Functions/CIntList_RemoveAt.h>
#include <NPCd/Functions/CStrList_Add.h>
#include <NPCd/Functions/CStrList_Remove.h>
#include <NPCd/Functions/CStrList_Clear.h>
#include <NPCd/Functions/CStrList_Get.h>
#include <NPCd/Functions/CStrList_GetSize.h>
#include <NPCd/Functions/CStrList_GetItemIndex.h>
#include <NPCd/Functions/CStrList_GetItemIndexNext.h>
#include <NPCd/Functions/CStrList_SetMaxSize.h>
#include <NPCd/Functions/CStrList_RemoveAt.h>
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
	AddFunction<Type::TYPE_NPC, CNPC_UnblockTimer>();
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
	AddFunction<Type::TYPE_NPC, CNPC_TeamEventSetStatus>();
	AddFunction<Type::TYPE_NPC, CNPC_TeamEventGetStatus>();
	AddFunction<Type::TYPE_NPC, CNPC_TeamEventGetTeamsCount>();
	AddFunction<Type::TYPE_NPC, CNPC_TeamSetColor>();
	AddFunction<Type::TYPE_NPC, CNPC_TeamAddMember>();
	AddFunction<Type::TYPE_NPC, CNPC_TeamRemoveMember>();
	AddFunction<Type::TYPE_NPC, CNPC_TeamRemoveAllMembers>();
	AddFunction<Type::TYPE_NPC, CNPC_TeamGetMembersCount>();
	AddFunction<Type::TYPE_NPC, CNPC_TeamGetMemberByIndex>();
	AddFunction<Type::TYPE_NPC, CNPC_TeamInstantTeleport>();
	AddFunction<Type::TYPE_NPC, CNPC_TeamSetRestartPoint>();
	AddFunction<Type::TYPE_NPC, CNPC_TeamShowSystemMessage2>();
	AddFunction<Type::TYPE_NPC, CNPC_ShowSystemMessage2>();
	AddFunction<Type::TYPE_NPC, CNPC_RegisterNpcConfirmDlg>();
	AddFunction<Type::TYPE_NPC, CNPC_SendNpcConfirmDlg>();
	AddFunction<Type::TYPE_NPC, CNPC_SendNpcConfirmDlgParty>();
	AddFunction<Type::TYPE_NPC, CNPC_SendNpcConfirmDlgAround>();
	AddFunction<Type::TYPE_NPC, CNPC_SetDbCookieInt>();
	AddFunction<Type::TYPE_NPC, CNPC_SetDbCookieStr>();
	AddFunction<Type::TYPE_NPC, CNPC_GetDbCookieInt>();
	AddFunction<Type::TYPE_NPC, CNPC_GetDbCookieStr>();
	AddFunction<Type::TYPE_NPC, CNPC_DeleteDbCookie>();
	AddFunction<Type::TYPE_NPC, CNPC_DeleteDbCookieGroup>();
	AddFunction<Type::TYPE_NPC, CNPC_GetDbCookieGroupSize>();
	AddFunction<Type::TYPE_NPC, CNPC_LoadDbCookieGroup>();
	AddFunction<Type::TYPE_NPC, CNPC_LoadDbCookieAllGroups>();
	AddFunction<Type::TYPE_NPC, CNPC_GetDbCookieKeyInt>();
	AddFunction<Type::TYPE_NPC, CNPC_GetDbCookieKeyStr>();
	AddFunction<Type::TYPE_NPC, CNPC_GetDbCookieKeyFirst>();
	AddFunction<Type::TYPE_NPC, CNPC_GetDbCookieKeyNext>();
	AddFunction<Type::TYPE_NPC, CNPC_SetDbData>();
	AddFunction<Type::TYPE_NPC, CNPC_GetDbData>();
	AddFunction<Type::TYPE_NPC, CNPC_GetCountDbData>();
	AddFunction<Type::TYPE_NPC, CNPC_DelDbData>();
	AddFunction<Type::TYPE_NPC, CNPC_DelDbDataById>();
	AddFunction<Type::TYPE_NPC, CNPC_TeamEventSetParticipantConditions>();
	AddFunction<Type::TYPE_NPC, CNPC_TeamSetParticipantConditions>();
	AddFunction<Type::TYPE_NPC, CNPC_TeamSetMemberColor>();
	AddFunction<Type::TYPE_NPC, CNPC_TeamMoveMember>();
	AddFunction<Type::TYPE_NPC, CNPC_TeamEventAddMembersWithBalance>();
	AddFunction<Type::TYPE_NPC, CNPC_TeamInstantTeleportWithConditions>();
	AddFunction<Type::TYPE_NPC, CNPC_Engage>();
	AddFunction<Type::TYPE_NPC, CNPC_SharedInstantZone_Enter>();
	AddFunction<Type::TYPE_NPC, CNPC_TeamGetInactiveCharacters>();
	AddFunction<Type::TYPE_NPC, CNPC_SharedInstantZone_Close>();
	AddFunction<Type::TYPE_GLOBALOBJECT, GlobalObject_BroadcastOnScreenNpcString>();
	AddFunction<Type::TYPE_GLOBALOBJECT, GlobalObject_ShowOnScreenNpcStringMsg>();
	AddFunction<Type::TYPE_GLOBALOBJECT, GlobalObject_OwnItemCount2>();
	AddFunction<Type::TYPE_GLOBALOBJECT, GlobalObject_OwnItemCountEx2>();
	AddFunction<Type::TYPE_GLOBALOBJECT, GlobalObject_Dummy1>();
	AddFunction<Type::TYPE_GLOBALOBJECT, GlobalObject_Dummy2>();
	AddFunction<Type::TYPE_GLOBALOBJECT, GlobalObject_SendUIEventNpcStr>();
	AddFunction<Type::TYPE_GLOBALOBJECT, GlobalObject_BroadCastUIEvent>();
	AddFunction<Type::TYPE_GLOBALOBJECT, GlobalObject_BroadCastUIEventNpcStr>();
	AddFunction<Type::TYPE_GLOBALOBJECT, GlobalObject_DebugLog>();
	AddFunction<Type::TYPE_INTLIST, CIntList_SetMaxSize>();
	AddFunction<Type::TYPE_INTLIST, CIntList_GetItemIndexNext>();
	AddFunction<Type::TYPE_INTLIST, CIntList_RemoveAt>();
	AddFunction<Type::TYPE_STRLIST, CStrList_Add>();
	AddFunction<Type::TYPE_STRLIST, CStrList_Remove>();
	AddFunction<Type::TYPE_STRLIST, CStrList_Clear>();
	AddFunction<Type::TYPE_STRLIST, CStrList_Get>();
	AddFunction<Type::TYPE_STRLIST, CStrList_GetSize>();
	AddFunction<Type::TYPE_STRLIST, CStrList_GetItemIndex>();
	AddFunction<Type::TYPE_STRLIST, CStrList_GetItemIndexNext>();
	AddFunction<Type::TYPE_STRLIST, CStrList_SetMaxSize>();
	AddFunction<Type::TYPE_STRLIST, CStrList_RemoveAt>();
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

