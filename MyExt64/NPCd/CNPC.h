
#pragma once

#include <NPCd/CreatureData2.h>
#include <Common/CSharedCreatureData.h>

namespace NPC {

class CNPC {
public:
	static void Init();
	static void RegisterVariables(void *obj, void *registry);
	static void RegisterVariable(void *obj, void *registry, const wchar_t *name, size_t offset, UINT32 fn);
	static void RegisterTypes();
	static void** GetTypeWrapper(void *registry, int type);

	static CNPC* __cdecl Constructor(CNPC *self);
	static CNPC* __cdecl Destructor(CNPC *self, bool isMemoryFreeUsed);

	/* 0x0000 */ void** vtable0x0000;
	/* 0x0008 */ unsigned char padding0x0008[0x0028-0x0008];
	/* 0x0028 */ void** vtable0x0028;
	/* 0x0030 */ INT64 p_state;
	/* 0x0038 */ INT64 i_quest0;
	/* 0x0040 */ INT64 i_quest1;
	/* 0x0048 */ INT64 i_quest2;
	/* 0x0050 */ INT64 i_quest3;
	/* 0x0058 */ INT64 i_quest4;
	/* 0x0060 */ INT64 i_ai0;
	/* 0x0068 */ INT64 i_ai1;
	/* 0x0070 */ INT64 i_ai2;
	/* 0x0078 */ INT64 i_ai3;
	/* 0x0080 */ INT64 i_ai4;
	/* 0x0088 */ INT64 attack_tick;
	/* 0x0090 */ INT64 c_quest0;
	/* 0x0098 */ INT64 c_quest1;
	/* 0x00A0 */ INT64 c_quest2;
	/* 0x00A8 */ INT64 c_quest3;
	/* 0x00B0 */ INT64 c_quest4;
	/* 0x00B8 */ INT64 c_ai0;
	/* 0x00C0 */ INT64 c_ai1;
	/* 0x00C8 */ INT64 c_ai2;
	/* 0x00D0 */ INT64 c_ai3;
	/* 0x00D8 */ INT64 c_ai4;
	/* 0x00E0 */ unsigned char padding0x00E0[0x0120-0x00E0];
	/* 0x0120 */ INT64 av_quest0;
	/* 0x0128 */ INT64 av_quest1;
	/* 0x0130 */ INT64 av_ai0;
	/* 0x0138 */ unsigned char padding0x0138[0x0188-0x0138];
	/* 0x0188 */ void *int_list;
	/* 0x0190 */ void *m_WorldTrapState;
	/* 0x0198 */ CSharedCreatureData *sm;
	/* 0x01A0 */ void *master;
	/* 0x01A8 */ void *boss;
	/* 0x01B0 */ void *top_desire_target;
	/* 0x01B8 */ void *top_skill_name_id;
	/* 0x01C0 */ INT32 padding0x01C0;
	/* 0x01C4 */ INT32 start_x;
	/* 0x01C8 */ INT32 start_y;
	/* 0x01CC */ INT32 start_z;
	/* 0x01D0 */ unsigned char padding0x01D0[0x1570-0x01D0];
	/* 0x1570 */ INT64 i_ai5;
	/* 0x1578 */ INT64 i_ai6;
	/* 0x1580 */ INT64 i_ai7;
	/* 0x1588 */ INT64 i_ai8;
	/* 0x1590 */ INT64 i_ai9;
	/* 0x1598 */ INT64 i_quest5;
	/* 0x15A0 */ INT64 i_quest6;
	/* 0x15A8 */ INT64 i_quest7;
	/* 0x15B0 */ INT64 i_quest8;
	/* 0x15B8 */ INT64 i_quest9;
	/* 0x15C0 */ CreatureData2 *sm2;
};

} // namespace NPC

using NPC::CNPC;

