
#pragma once

#include <windows.h>

class CNPCMaker {
public:
	static void Init();
	static void RegisterVariables(void *obj, void *registry);
	static void RegisterVariable(void *obj, void *registry, const wchar_t *name, size_t offset, UINT64 fn);

	/* 0x0000 */ void **vtable0x0000;
	/* 0x0008 */ unsigned char padding0x0008[0x0018-0x0008];
	/* 0x0018 */ void **vtable0x0018;
	/* 0x0020 */ unsigned char padding0x0020[0x0422-0x0020];
	/* 0x0422 */ wchar_t name[25];
	/* 0x0454 */ unsigned char padding0x0454[0x0484-0x0454];
	/* 0x0484 */ UINT32 def_count;
	/* 0x0488 */ UINT32 npc_count;
	/* 0x048C */ UINT32 maximum_npc;
	/* 0x0490 */ INT32 i_ai0;
	/* 0x0494 */ INT32 i_ai1;
	/* 0x0498 */ INT32 i_ai2;
	/* 0x049C */ INT32 i_ai3;
	/* 0x04A0 */ INT32 i_ai4;
	/* 0x04A4 */ unsigned char padding0x04A4[0x04A8-0x4A4];
	/* 0x04A8 */ INT64 i_quest0;
	/* 0x04B0 */ INT64 i_quest1;
	/* 0x04B8 */ INT64 i_quest2;
	/* 0x04C0 */ INT64 i_quest3;
	/* 0x04C8 */ INT64 i_quest4;
	/* 0x04D0 */ INT64 c_ai0;
	/* 0x04D8 */ INT64 c_ai1;
	/* 0x04E0 */ INT64 c_ai2;
	/* 0x04E8 */ INT64 c_ai3;
	/* 0x04F0 */ INT64 c_ai4;
	/* 0x04F8 */ unsigned char padding0x04F8[0x0540-0x04F8];
	/* 0x0540 */ void *int_list;
	/* 0x0548 */ INT32 enabled;
	/* 0x054C */ unsigned char padding0x054C[0x13C0-0x054C];
	/* 0x13C0 */ UINT32 inzone_type_id;
	/* 0x13C4 */ UINT32 inzone_cluster_id;
	/* 0x13C8 */ UINT32 inzone_id;
	/* 0x13CC */ unsigned char padding0x13CC[0x1410-0x13CC];
	/* 0x1410 */ INT32 i_ai5;
	/* 0x1414 */ INT32 i_ai6;
	/* 0x1418 */ INT32 i_ai7;
	/* 0x141C */ INT32 i_ai8;
	/* 0x1420 */ INT32 i_ai9;
	/* 0x1424 */ unsigned char padding0x1424[0x1428-0x1424];
	/* 0x1428 */ INT64 i_quest5;
	/* 0x1430 */ INT64 i_quest6;
	/* 0x1438 */ INT64 i_quest7;
	/* 0x1440 */ INT64 i_quest8;
	/* 0x1448 */ INT64 i_quest9;
};

