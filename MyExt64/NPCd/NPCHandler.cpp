
#include <NPCd/NPCHandler.h>
#include <Common/Utils.h>

void NPCHandler::Init()
{
	WriteMemoryQWORD(0x6C0D18, reinterpret_cast<UINT32>(RegisterHandlers));
}

void NPCHandler::RegisterHandlers(void *registry)
{
	reinterpret_cast<void(*)(void*)>(0x579020)(registry);
	reinterpret_cast<void(*)(void*, wchar_t*)>(0x5771DC)(registry, L"ON_OLYMPIAD_FIELD_CHANGED");
	reinterpret_cast<void(*)(void*, wchar_t*)>(0x5771DC)(registry, L"BIRTHDAY_EVENT");
	reinterpret_cast<void(*)(void*, wchar_t*)>(0x5771DC)(registry, L"IS_TOGGLE_SKILL_ONOFF");
	reinterpret_cast<void(*)(void*, wchar_t*)>(0x5771DC)(registry, L"REPLY_SET_VIP_USER");
}

