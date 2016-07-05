
#include "EventDrop.h"
#include "Utils.h"
#include "CLog.h"

CriticalSection EventDrop::reloadCS;
EventDrop::Data *EventDrop::dataA = 0;
EventDrop::Data *EventDrop::dataB = 0;
EventDrop::Data *EventDrop::data = 0;

void EventDrop::Init()
{
	dataA = new EventDrop::Data;
	dataB = new EventDrop::Data;
	data = dataA;

	WriteInstructionCall(0x4802B0, reinterpret_cast<UINT32>(ReloadEventINIFile));
	WriteInstructionCall(0x480388, reinterpret_cast<UINT32>(ReloadEventINIFile));
	WriteInstructionCall(0x480430, reinterpret_cast<UINT32>(ReloadEventINIFile));
	WriteInstructionCall(0x480508, reinterpret_cast<UINT32>(ReloadEventINIFile));
	WriteInstructionCall(0x4805E0, reinterpret_cast<UINT32>(ReloadEventINIFile));
	WriteInstructionCall(0x4806B8, reinterpret_cast<UINT32>(ReloadEventINIFile));
	WriteInstructionCall(0x481654, reinterpret_cast<UINT32>(ReloadEventINIFile));
	WriteInstructionCall(0x6B0525, reinterpret_cast<UINT32>(ReloadEventINIFile));
}

std::wstring EventDrop::GetConfig(const wchar_t *section, const wchar_t *name, const wchar_t *defaultValue)
{
    static wchar_t buffer[4096];
    GetPrivateProfileString(section, name, defaultValue, buffer, sizeof(buffer), L"..\\script\\eventdata.ini");
	return std::wstring(buffer);
}

void EventDrop::ReloadEventINIFile()
{
	reinterpret_cast<void(*)()>(0x641168)();
	Load();
}

void EventDrop::Load()
{
	ScopedLock lock(reloadCS);
	CLog::Add(CLog::Blue, L"Load event drop");
	Data *newData = (data == dataA ? dataB : dataA);
	newData->maxLevelDifference = _wtoi(GetConfig(L"drop", L"maxleveldifference", L"8").c_str());
	newData->items.clear();
	size_t count = _wtoi(GetConfig(L"drop", L"count", L"0").c_str());
	for (size_t i = 0 ; i < count ; ++i) {
		wchar_t buffer[64];
		wsprintf(buffer, L"item%d", i);
		int itemId = _wtoi(GetConfig(L"drop", buffer, L"0").c_str());
		if (itemId) {
			wsprintf(buffer, L"chance%d", i);
			double chance = _wtof(GetConfig(L"drop", buffer, L"0.0").c_str());
			if (chance > 0) {
				Data::DropItem dropItem;
				dropItem.itemId = itemId;
				dropItem.chance = chance;
				newData->items.push_back(dropItem);
			}
		}
	}
	data = newData;
}

