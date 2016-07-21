
#pragma once

#include <Server/CUser.h>
#include <Common/CriticalSection.h>
#include <windows.h>
#include <map>

class CInstantZone {
public:
	static void Init();

	static void __cdecl OnReleaseWrapper(CInstantZone *self);
	static bool __cdecl EnterZoneWrapper(CInstantZone *self, class CUser *user, double *position, int enterType);
	static void __cdecl SetBindingAllUserWrapper(CInstantZone *self);
	static void __cdecl SetBindingWrapper(CInstantZone *self, class CUser *user, UINT32 time);

	void OnRelease();
	bool EnterZone(class CUser *user, double *position, int enterType);
	void SetBindingAllUser();
	void SetBinding(class CUser *user, UINT32 time);

	class InZoneUser {
	public:
		std::map<UINT32, CUser::InZoneRestriction> inZoneRestrictionMap1;
		std::map<UINT32, CUser::InZoneRestriction> inZoneRestrictionMap2;
	};

	class InZoneData {
	public:
		std::map<UINT32, InZoneUser> userRestrictions;
	};

	static std::map<CInstantZone*, InZoneData> zones;
	static CriticalSection zonesLock;

	class Data {
	public:
		class Data2 {
		public:
			/* 0x0000 */ UINT32 id;
			/* 0x0004 */ UINT32 unknown;
		};

		/* 0x0000 */ unsigned char padding0x0000[0x0140 - 0x0000];
		/* 0x0140 */ Data2 *data2;
	};

	/* 0x0000 */ unsigned char padding0x0000[0x00B0 - 0x0000];
	/* 0x00B0 */ UINT32 id;
	/* 0x00B4 */ unsigned char padding0x00B4[0x0180 - 0x00B4];
	/* 0x0180 */ Data *data;
};

