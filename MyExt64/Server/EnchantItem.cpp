
#include <Server/EnchantItem.h>
#include <Common/DataParser.h>
#include <Common/Utils.h>

namespace {

std::map<int, double> chancesFighterWeapon;
std::map<int, double> chancesMageWeapon;
std::map<int, double> chancesNormalArmor;
std::map<int, double> chancesOnePieceArmor;

class Parser : public DataParser {
public:
	Parser() : state(-1) { }

	int state;

	virtual void OnData(const std::map<std::string, std::string> &data)
	{
		if (Exists(data, "weapon")) {
			if (Get<std::string>(data, "weapon") == "fighter") {
				state = 0;
			} else if (Get<std::string>(data, "weapon") == "mage") {
				state = 1;
			} else {
				state = -1;
			}
		} else if (Exists(data, "armor")) {
			if (Get<std::string>(data, "armor") == "normal") {
				state = 2;
			} else if (Get<std::string>(data, "armor") == "onepiece") {
				state = 3;
			} else {
				state = -1;
			}
		} else if (state >= 0) {
			int level = Get<int>(data, "level");
			double chance = Get<double>(data, "chance");
			switch (state) {
			case 0: chancesFighterWeapon[level - 1] = chance; break;
			case 1: chancesMageWeapon[level - 1] = chance; break;
			case 2: chancesNormalArmor[level - 1] = chance; break;
			case 3: chancesOnePieceArmor[level - 1] = chance; break;
			default: break;
			}
		}
	}
};

} // namespace

void EnchantItem::Init()
{
	WriteMemoryBYTES(0x693391 + 0x0, "\x48\x89\xf9", 3); // mov rcx, rdi
	WriteInstructionCall(0x693391 + 0x3, reinterpret_cast<UINT32>(GetFighterWeaponChance)); // get chance
	WriteMemoryBYTES(0x693391 + 0x8, "\xf2\x0f\x10\xf0", 4); // movsd xmm6, xmm0
	WriteInstructionJmp(0x693391 + 0xC, 0x6933AF, 0); // jump to 6933AF

	WriteMemoryBYTES(0x693308 + 0x0, "\x48\x89\xf9", 3); // mov rcx, rdi
	WriteInstructionCall(0x693308 + 0x3, reinterpret_cast<UINT32>(GetMageWeaponChance)); // get chance
	WriteMemoryBYTES(0x693308 + 0x8, "\xf2\x0f\x10\xf0", 4); // movsd xmm6, xmm0
	WriteInstructionJmp(0x693308 + 0xC, 0x693326, 0); // jump to 693326

	NOPMemory(0x69341D, 6); // nop out jump if current armor enchant level < 3 -> success
	NOPMemory(0x69342E, 2); // nop out jump if current armor enchant level > 20 -> fail

	WriteMemoryBYTES(0x693453 + 0x0, "\x48\x89\xf9", 3); // mov rcx, rdi
	WriteInstructionCall(0x693453 + 0x3, reinterpret_cast<UINT32>(GetNormalArmorChance)); // get chance
	WriteMemoryBYTES(0x693453 + 0x8, "\xf2\x0f\x10\xf0", 4); // movsd xmm6, xmm0
	WriteInstructionJmp(0x693453 + 0xC, 0x69348A, 0); // jump to 69348A

	WriteMemoryBYTES(0x693435 + 0x0, "\x48\x89\xf9", 3); // mov rcx, rdi
	WriteInstructionCall(0x693435 + 0x3, reinterpret_cast<UINT32>(GetOnePieceArmorChance)); // get chance
	WriteMemoryBYTES(0x693435 + 0x8, "\xf2\x0f\x10\xf0", 4); // movsd xmm6, xmm0
	WriteInstructionJmp(0x693435 + 0xC, 0x69348A, 0); // jump to 69348A
}

void EnchantItem::Load()
{
	CLog::Add(CLog::Blue, L"Reading ..\\Script\\itemenchant.txt");
	if (!Parser().parse("..\\Script\\itemenchant.txt")) {
		CLog::Add(CLog::Red, L"Failed to load itemenchant.txt");
	} else {
		CLog::Add(CLog::Blue, L"Loaded ..\\Script\\itemenchant.txt");
	}
}

double __cdecl EnchantItem::GetFighterWeaponChance(const int level)
{ GUARDED

	std::map<int, double>::const_iterator i(chancesFighterWeapon.find(level));
	if (i == chancesFighterWeapon.end()) {
		CLog::Add(CLog::Red, L"Chance for enchant fighter weapon +%d -> +%d not found, assuming zero chance", level, level+1);
		return 0.0;
	} else {
		return i->second;
	}
}

double __cdecl EnchantItem::GetMageWeaponChance(const int level)
{ GUARDED

	std::map<int, double>::const_iterator i(chancesMageWeapon.find(level));
	if (i == chancesMageWeapon.end()) {
		CLog::Add(CLog::Red, L"Chance for enchant mage weapon +%d -> +%d not found, assuming zero chance", level, level+1);
		return 0.0;
	} else {
		return i->second;
	}
}

double __cdecl EnchantItem::GetNormalArmorChance(const int level)
{ GUARDED

	std::map<int, double>::const_iterator i(chancesNormalArmor.find(level));
	if (i == chancesNormalArmor.end()) {
		CLog::Add(CLog::Red, L"Chance for enchant normal armor +%d -> +%d not found, assuming zero chance", level, level+1);
		return 0.0;
	} else {
		return i->second;
	}
}


double __cdecl EnchantItem::GetOnePieceArmorChance(const int level)
{ GUARDED

	std::map<int, double>::const_iterator i(chancesOnePieceArmor.find(level));
	if (i == chancesOnePieceArmor.end()) {
		CLog::Add(CLog::Red, L"Chance for enchant one piece armor +%d -> +%d not found, assuming zero chance", level, level+1);
		return 0.0;
	} else {
		return i->second;
	}
}

