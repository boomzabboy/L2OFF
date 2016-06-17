
#pragma once

#include <windows.h>

class EnchantRequirement {
public:
	int sp;
    INT64 adena;
};

class EnchantDataInfo {
public:
	static const EnchantRequirement enchantRequirements[30];
};

