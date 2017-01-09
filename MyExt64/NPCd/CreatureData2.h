
#pragma once

#include <windows.h>

class CreatureData2 {
public:
	CreatureData2();
	virtual void RegisterFunctions(void *registry);
	virtual void RegisterVariables(void *registry);

	void RegisterVariable(void *registry, const wchar_t *name, size_t offset);

	/* 0x0008 */ unsigned char padding0x0008[0x05E0-0x0008];
	/* 0x05E0 */ UINT32 absolute_defence;
	/* 0x05E4 */ UINT32 no_attack_damage;
	/* 0x05E8 */ unsigned char padding0x05E8[0x0828-0x05E8];
	/* 0x0828 */ UINT32 quest_inv_items;
};

