
#include "GraciaEpilogue.h"
#include "CUser.h"
#include "CSkillEnchantInfo.h"
#include "CSkillEnchantDB.h"
#include "SkillEnchantOperator.h"
#include "CLog.h"
#include "DataParser.h"
#include <fstream>
#include <map>

namespace {

class EnchantCost {
public:
	class Level {
	public:
		UINT32 adena;
		UINT32 sp;
	};

	Level levels[30];
};

std::map<UINT32, EnchantCost> enchantCosts;

class Parser : public DataParser {
public:
	Parser() : skillId(-1) { }

	int skillId;
    int levels;

	virtual void OnData(const std::map<std::string, std::string> &data)
    {
        if (Exists(data, "skill")) {
            skillId = Get<int>(data, "skill");
            levels = Get<int>(data, "levels", 0);
        } else if (skillId >= 0 && Exists(data, "level")) {
            int level = Get<int>(data, "level");
            if (level < 1 || level > min(levels, 30)) {
				CLog::Add(CLog::Red, L"Invalid skill level %d for skill %d", level, skillId);
                return;
            }
			std::pair<std::map<UINT32, EnchantCost>::iterator, bool> i = enchantCosts.insert(std::make_pair(skillId, EnchantCost()));
			i.first->second.levels[level-1].adena = Get<int>(data, "adena", 0);
			i.first->second.levels[level-1].sp = Get<int>(data, "sp", 0);
        }
    }
};

} // namespace

void GraciaEpilogue::InitSkillEnchant()
{
	WriteMemoryBYTE(0x82509F, 0xEB); // don't require NPC for RequestExEnchantSkillInfo
	WriteMemoryBYTE(0x827239, 0xEB); // don't require NPC for RequestExEnchantSkill
	WriteMemoryBYTE(0x8248C2, 0xEB); // don't require NPC for RequestExEnchantSkillRouteChange
	WriteMemoryBYTE(0x824916, 0xEB); // don't require NPC for RequestExEnchantSkillRouteChange

	WriteInstructionCall(0x827D60, reinterpret_cast<UINT32>(SkillEnchantOperatorOperateSuccess));
	WriteInstructionCall(0x827FAE, reinterpret_cast<UINT32>(SkillEnchantOperatorOperateFail));
	WriteMemoryQWORD(0xC01AF8, reinterpret_cast<UINT64>(SkillEnchantOperatorOperateNormal));

	WriteInstructionCall(0x8285DE, reinterpret_cast<UINT32>(SkillEnchantOperatorOperateSuccess));
	WriteMemoryBYTES(0x8287D1, "\x49\x8B\xCC", 3);
	WriteInstructionCall(0x8287D4, reinterpret_cast<UINT32>(SkillEnchantOperatorOperateSafeFail), 0x8287DE);
	WriteMemoryBYTES(0x82880A, "\x49\x8B\xCC", 3);
	WriteInstructionCall(0x82880D, reinterpret_cast<UINT32>(SkillEnchantOperatorOperateSafeFail), 0x828817);
	WriteMemoryQWORD(0xC01B58, reinterpret_cast<UINT64>(SkillEnchantOperatorOperateSafe));

	WriteInstructionCall(0x82B777, reinterpret_cast<UINT32>(SkillEnchantOperatorOperateSuccess));
	WriteMemoryQWORD(0xC01BB8, reinterpret_cast<UINT64>(SkillEnchantOperatorOperateUntrain));

	WriteInstructionCall(0x8290CD, reinterpret_cast<UINT32>(SkillEnchantOperatorOperateSuccess));
	WriteMemoryQWORD(0xC01D78, reinterpret_cast<UINT64>(SkillEnchantOperatorOperateRouteChange));

	WriteMemoryBYTES(0x827BA3, "\x48\x89\xE9\x48\xC7\xC2\x00\x00\x00\x00\x45\x89\xF8\x45\x89\xF1"
	                           "\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90"
							   "\x90\x90\x90\x90\x90\x90\x84\xC0\x75\x3E", 42);
	WriteInstructionCall(0x827BA3 + 0x10, reinterpret_cast<UINT32>(CheckEnchantItems));
	WriteMemoryBYTES(0x827C0F, "\x48\x89\xE9\x48\xC7\xC2\x00\x00\x00\x00\x45\x89\xF8\x45\x89\xF1"
	                           "\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90", 26);
	WriteInstructionCall(0x827C0F + 0x10, reinterpret_cast<UINT32>(TakeEnchantItems));
	WriteMemoryQWORD(0xC01B20, reinterpret_cast<UINT64>(SkillEnchantOperatorCalculateSP));
	WriteMemoryQWORD(0xC01B18, reinterpret_cast<UINT64>(SkillEnchantOperatorCalculateEXP));

	WriteMemoryBYTES(0x828421, "\x48\x89\xF1\x48\xC7\xC2\x01\x00\x00\x00\x45\x89\xF8\x45\x89\xF1"
	                           "\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90"
							   "\x90\x90\x90\x90\x90\x90\x84\xC0\x75\x3F", 42);
	WriteInstructionCall(0x828421 + 0x10, reinterpret_cast<UINT32>(CheckEnchantItems));
	WriteMemoryBYTES(0x82848E, "\x48\x89\xF1\x48\xC7\xC2\x01\x00\x00\x00\x45\x89\xF8\x45\x89\xF1"
		                       "\x90\x90\x90\x90\x90\x90\x90\x90\x90", 25);
	WriteInstructionCall(0x82848E + 0x10, reinterpret_cast<UINT32>(TakeEnchantItems));
	WriteMemoryQWORD(0xC01B80, reinterpret_cast<UINT64>(SkillEnchantOperatorCalculateSP));
	WriteMemoryQWORD(0xC01B78, reinterpret_cast<UINT64>(SkillEnchantOperatorCalculateEXP));

	WriteMemoryQWORD(0xC01BE0, reinterpret_cast<UINT64>(SkillEnchantOperatorCalculateSP));
	WriteMemoryQWORD(0xC01BD8, reinterpret_cast<UINT64>(SkillEnchantOperatorCalculateEXP));

	WriteMemoryBYTES(0x828EEB, "\x48\x89\xF1\x48\xC7\xC2\x03\x00\x00\x00\x45\x89\xF9\x45\x89\xF0"
		                       "\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90"
							   "\x90\x90\x90\x90\x90\x90\x84\xC0\x75\x3E", 42);
	WriteInstructionCall(0x828EEB + 0x10, reinterpret_cast<UINT32>(CheckEnchantItems));
	WriteMemoryBYTES(0x828F57, "\x48\x89\xF1\x48\xC7\xC2\x03\x00\x00\x00\x45\x89\xF9\x45\x89\xF0"
		                       "\x90\x90\x90\x90\x90\x90\x90\x90\x90", 25);
	WriteInstructionCall(0x828F57 + 0x10, reinterpret_cast<UINT32>(TakeEnchantItems));
	WriteMemoryQWORD(0xC01DA0, reinterpret_cast<UINT64>(SkillEnchantOperatorCalculateSP));
	WriteMemoryQWORD(0xC01D98, reinterpret_cast<UINT64>(SkillEnchantOperatorCalculateEXP));
}

void GraciaEpilogue::LoadSkillEnchant()
{
	CLog::Add(CLog::Blue, L"Reading ..\\Script\\skillenchantcost.txt");
	if (!Parser().parse("..\\Script\\skillenchantcost.txt")) {
		CLog::Add(CLog::Red, L"Failed to load skillenchantcost.txt");
	} else {
		CLog::Add(CLog::Blue, L"Loaded %d skills from ..\\Script\\skillenchantcost.txt", enchantCosts.size());
	}
}

std::pair<int, INT64> GraciaEpilogue::GetEnchantSpAdena(CUser *user, UINT32 &enchantType, int skillId, int skillLevel, CSkillEnchantInfo **info_)
{
	if (enchantType > 3) {
		return std::make_pair(-1, -1);
	}

	int acquiredLevel = -1;
	if (user) {
		acquiredLevel = user->GetAcquiredSkillLevel(skillId);
		if (acquiredLevel < 101) {
			if (enchantType > 1) {
				enchantType = 0;
			}
		} else {
			if (skillLevel == acquiredLevel + 1) {
				if (enchantType > 1) {
					enchantType = 0;
				}
			} else if (skillLevel == acquiredLevel - 1) {
				if (enchantType != 2) {
					enchantType = 2;
				}
			} else if (skillLevel == acquiredLevel) {
				return std::make_pair(-1, -1);
			} else if (skillLevel % 100 == acquiredLevel % 100) {
				if (enchantType != 3) {
					enchantType = 3;
				}
			} else {
				return std::make_pair(-1, -1);
			}
		}
	}

	SkillEnchantOperator *op = SkillEnchantOperator::GetOperator(enchantType);
	if (!op) {
		return std::make_pair(-1, -1);
	}

	CSkillEnchantInfo *info = 0;

	if (acquiredLevel < 0) {
		if (skillLevel % 100 > 1) {
			acquiredLevel = skillLevel - 1;
		} else {
			info = CSkillEnchantDB::GetInstance()->GetSkillEnchantInfo(skillId, 101);
			if (!info) {
				return std::make_pair(-1, -1);
			}
			acquiredLevel = info->requiredSkillLevel;
		}
	}

	if (enchantType == 2) {
		info = CSkillEnchantDB::GetInstance()->GetSkillEnchantInfo(skillId, acquiredLevel);
	} else {
		info = CSkillEnchantDB::GetInstance()->GetSkillEnchantInfo(skillId, skillLevel);
	}
	if (!info) {
		return std::make_pair(-1, -1);
	}

	if (info_) {
		*info_ = info;
	}

	int index = (info->newEnchantLevel - 1) % 100;
	if (index >= 30 || index < 0) {
		return std::make_pair(-1, -1);
	}

	std::map<UINT32, EnchantCost>::const_iterator ienchantCosts = enchantCosts.find(skillId);
	if (ienchantCosts == enchantCosts.end()) {
		return std::make_pair(-1, -1);
	}
	int requiredSP = ienchantCosts->second.levels[index].sp * op->requirementModifier;
	INT64 requiredAdena = ienchantCosts->second.levels[index].adena * op->requirementModifier;
	if (op->operatorType == 1) {
		requiredSP *= 5;
		requiredAdena *= 5;
	} else if (op->operatorType == 2) {
		requiredAdena = 0;
		requiredSP *= 0.8;
	}

	return std::make_pair(requiredSP, requiredAdena);
}

bool __cdecl GraciaEpilogue::RequestExEnchantSkillInfo(CUserSocket *self, const BYTE *packet, BYTE opcode)
{
	(void) opcode;

	CUser *user = self->GetUser();
	if (!user) {
		return false;
	}

	UINT32 skillId = 0;
	UINT32 skillLevel = 0;

	Disassemble(packet, "dd", &skillId, &skillLevel);

	int acquiredLevel = user->GetAcquiredSkillLevel(skillId);
	if (!acquiredLevel) {
		return false;
	}

	if (enchantCosts.find(skillId) == enchantCosts.end()) {
		return false;
	}

	CSkillEnchantInfo *info = CSkillEnchantDB::GetInstance()->GetSkillEnchantInfo(skillId, 101);
	if (!info || info->requiredSkillLevel > skillLevel) {
		self->Send("chddddd", 0xFE, 0x2A, skillId, skillLevel, 0, 0, 0);
		return false;
	}

	UINT32 routes[8];
	size_t route = 0;
	bool maxEnchanted = false;
	for ( ; route < 8 ; ++route) {
		CSkillEnchantInfo *info2 = 0;
		if (acquiredLevel < 101) {
			info2 = CSkillEnchantDB::GetInstance()->GetSkillEnchantInfo(skillId, route * 100 + 101);
		} else {
			info2 = CSkillEnchantDB::GetInstance()->GetSkillEnchantInfo(skillId, route * 100 + 100 + acquiredLevel % 100);
		}
		if (!info2) {
			break;
		}
		if (route == acquiredLevel / 100 - 1) {
			CSkillEnchantInfo *info2 = CSkillEnchantDB::GetInstance()->GetSkillEnchantInfo(skillId, route * 100 + 101 + acquiredLevel % 100);
			if (!info2) {
				maxEnchanted = true;
			}
		}
		routes[route] = info2->newEnchantLevel;
	}
	self->Send("chdddddb", 0xFE, 0x2A, skillId, skillLevel, maxEnchanted ? 0 : 1, acquiredLevel > 100 ? 1 : 0, route, route * sizeof(UINT32), routes);

	return false;
}

bool __cdecl GraciaEpilogue::RequestExEnchantSkillInfoDetail(CUserSocket *self, const BYTE *packet, BYTE opcode)
{
	(void) opcode;

	CUser *user = self->GetUser();
	if (!user) {
		return false;
	}

	UINT32 enchantType = 0;
	UINT32 skillId = 0;
	UINT32 skillLevel = 0;

	Disassemble(packet, "ddd", &enchantType, &skillId, &skillLevel);

	if (enchantType > 3) {
		return true;
	}

	CSkillEnchantInfo *info = 0;
	std::pair<int, INT64> spAdena = GetEnchantSpAdena(user, enchantType, skillId, skillLevel, &info);
	if (spAdena.first < 0) {
		return false;
	}

	int itemId = info->requiredItems[enchantType];
	int itemCount = info->requiredItemCounts[enchantType];

	int acquiredLevel = user->GetAcquiredSkillLevel(skillId);

	int outSkillLevel = skillLevel;
	if (enchantType == 2) {
		if (acquiredLevel % 100 > 1) {
			outSkillLevel = acquiredLevel - 1;
		} else {
			outSkillLevel = info->requiredSkillLevel;
		}
	}

	int probability = SkillEnchantOperator::GetOperator(enchantType)->CalculateProb(info, user->GetLevel());

	self->Send("chdddddddddd", 0xFE, 0x5E, enchantType, skillId, outSkillLevel,
		spAdena.first, probability, 2, 57, spAdena.second, itemId, itemCount);

	return false;
}

bool __cdecl GraciaEpilogue::RequestExEnchantSkillUntrain(CUserSocket *self, const BYTE *packet, BYTE opcode)
{
	(void) opcode;

	UINT32 skillId = 0;
	UINT32 skillLevel = 0;

	Disassemble(packet, "dd", &skillId, &skillLevel);

	if (!(skillLevel % 100)) {
		CSkillEnchantInfo *info = CSkillEnchantDB::GetInstance()->GetSkillEnchantInfo(skillId, skillLevel + 1);
		if (info) {
			skillLevel = info->requiredSkillLevel;
			Assemble(const_cast<char*>(reinterpret_cast<const char*>(packet)), 8, "dd", skillId, skillLevel);
		}
	}

	return CUserSocket::exHandlers[0x33](self, packet, opcode);
}

void GraciaEpilogue::SkillEnchantOperatorOperateSuccess(CUser *user)
{
	if (!user) {
		return;
	}
	typedef void (__thiscall *t)(CUser*);
	t f = reinterpret_cast<t>(0x55CB14);
	f(user);
	CUserSocket *socket = user->socket;
	if (!socket) {
		return;
	}
	socket->Send("chd", 0xFE, 0xA7, 1);
}

void GraciaEpilogue::SkillEnchantOperatorOperateFail(CUser *user)
{
	if (!user) {
		return;
	}
	typedef void (__thiscall *t)(CUser*);
	t f = reinterpret_cast<t>(0x55CB14);
	f(user);
	CUserSocket *socket = user->socket;
	if (!socket) {
		return;
	}
	socket->Send("chd", 0xFE, 0xA7, 0);
}

void GraciaEpilogue::SkillEnchantOperatorOperateSafeFail(CUserSocket *socket, const char *unused, BYTE a, UINT32 b, UINT32 c, UINT32 d, UINT32 e, UINT32 f)
{
	socket->Send("chd", 0xFE, 0xA7, 0);
	socket->Send("cddddd", a, b, c, d, e, f);
}

bool GraciaEpilogue::SkillEnchantOperatorOperateNormal(SkillEnchantOperator *self, CUser *user, int id, int level)
{
	if (!user) {
		return false;
	}
	typedef bool (__thiscall *t)(SkillEnchantOperator*, CUser*, int, int);
	t f = reinterpret_cast<t>(0x82797C);
	if (!f(self, user, id, level)) {
		return false;
	}
	CUserSocket *socket = user->socket;
	if (!socket) {
		return true;
	}
	char buffer[16];
	int acquiredLevel = user->GetAcquiredSkillLevel(id);
	Assemble(buffer, sizeof(buffer), "dd", id, acquiredLevel);
	RequestExEnchantSkillInfo(socket, reinterpret_cast<const BYTE*>(buffer), 0x0E);
	return true;
}

bool GraciaEpilogue::SkillEnchantOperatorOperateSafe(SkillEnchantOperator *self, CUser *user, int id, int level)
{
	if (!user) {
		return false;
	}
	typedef bool (__thiscall *t)(SkillEnchantOperator*, CUser*, int, int);
	t f = reinterpret_cast<t>(0x8281F8);
	if (!f(self, user, id, level)) {
		return false;
	}
	CUserSocket *socket = user->socket;
	if (!socket) {
		return true;
	}
	char buffer[16];
	int acquiredLevel = user->GetAcquiredSkillLevel(id);
	Assemble(buffer, sizeof(buffer), "dd", id, acquiredLevel);
	RequestExEnchantSkillInfo(socket, reinterpret_cast<const BYTE*>(buffer), 0x0E);
	return true;
}

bool GraciaEpilogue::SkillEnchantOperatorOperateUntrain(SkillEnchantOperator *self, CUser *user, int id, int level)
{
	if (!user) {
		return false;
	}
	typedef bool (__thiscall *t)(SkillEnchantOperator*, CUser*, int, int);
	t f = reinterpret_cast<t>(0x82B3AC);
	if (!f(self, user, id, level)) {
		return false;
	}
	CUserSocket *socket = user->socket;
	if (!socket) {
		return true;
	}
	char buffer[16];
	int acquiredLevel = user->GetAcquiredSkillLevel(id);
	Assemble(buffer, sizeof(buffer), "dd", id, acquiredLevel);
	RequestExEnchantSkillInfo(socket, reinterpret_cast<const BYTE*>(buffer), 0x0E);
	return true;
}

bool GraciaEpilogue::SkillEnchantOperatorOperateRouteChange(SkillEnchantOperator *self, CUser *user, int id, int level)
{
	if (!user) {
		return false;
	}
	typedef bool (__thiscall *t)(SkillEnchantOperator*, CUser*, int, int);
	t f = reinterpret_cast<t>(0x828D20);
	if (!f(self, user, id, level)) {
		return false;
	}
	CUserSocket *socket = user->socket;
	if (!socket) {
		return true;
	}
	char buffer[16];
	int acquiredLevel = user->GetAcquiredSkillLevel(id);
	Assemble(buffer, sizeof(buffer), "dd", id, acquiredLevel);
	RequestExEnchantSkillInfo(socket, reinterpret_cast<const BYTE*>(buffer), 0x0E);
	return true;
}

bool __cdecl GraciaEpilogue::CheckEnchantItems(CUser *user, UINT32 enchantType, int skillId, int skillLevel)
{
	CSkillEnchantInfo *info = 0;
	std::pair<int, INT64> spAdena = GetEnchantSpAdena(user, enchantType, skillId, skillLevel, &info);
	if (spAdena.first < 0) {
		return false;
	}

	int itemId = info->requiredItems[enchantType];
	int itemCount = info->requiredItemCounts[enchantType];

	if (itemId && itemCount) {
		if (user->GetItemCount(itemId) < itemCount) {
			return false;
		}
	}

	if (spAdena.second) {
		if (user->GetItemCount(57) < spAdena.second) {
			return false;
		}
	}

	return true;
}

void __cdecl GraciaEpilogue::TakeEnchantItems(CUser *user, UINT32 enchantType, int skillId, int skillLevel)
{
	CSkillEnchantInfo *info = 0;
	std::pair<int, INT64> spAdena = GetEnchantSpAdena(user, enchantType, skillId, skillLevel, &info);
	if (spAdena.first < 0) {
		return;
	}

	int itemId = info->requiredItems[enchantType];
	int itemCount = info->requiredItemCounts[enchantType];

	if (itemId && itemCount) {
		user->TakeItem(itemId, itemCount);
	}

	if (spAdena.second) {
		user->TakeItem(57, spAdena.second);
	}
}

INT64 __cdecl GraciaEpilogue::SkillEnchantOperatorCalculateEXP(SkillEnchantOperator *self, class CSkillEnchantInfo *info, int level)
{
	return 0;
}

int __cdecl GraciaEpilogue::SkillEnchantOperatorCalculateSP(SkillEnchantOperator *self, class CSkillEnchantInfo *info, int level)
{
	std::pair<int, INT64> spAdena = GetEnchantSpAdena(0, self->operatorType, info->skillId, info->newEnchantLevel, 0);
	if (spAdena.first < 0) {
		return 0;
	}
	return spAdena.first;
}

