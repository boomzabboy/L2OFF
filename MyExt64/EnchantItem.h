
#pragma once

#include <windows.h>

class EnchantItem {
public:
	static void Init();
	static void Load();

protected:
	static double __cdecl GetFighterWeaponChance(const int level);
	static double __cdecl GetMageWeaponChance(const int level);
	static double __cdecl GetNormalArmorChance(const int level);
	static double __cdecl GetOnePieceArmorChance(const int level);
};

