
#pragma once

#include "CriticalSection.h"
#include <string>
#include <vector>
#include <windows.h>

class EventDrop {
public:
	struct Data {
		struct DropItem {
			UINT32 itemId;
			double chance;
		};
		std::vector<DropItem> items;
		int maxLevelDifference;
	};

	static void Init();
	static std::wstring GetConfig(const wchar_t *section, const wchar_t *name, const wchar_t *defaultValue);
	static void ReloadEventINIFile();
	static void Load();

	static Data *data;

protected:
	static CriticalSection reloadCS;
	static Data *dataA;
	static Data *dataB;
};

