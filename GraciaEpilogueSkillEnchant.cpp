
#include "GraciaEpilogue.h"
#include "CUser.h"
#include "CSkillEnchantInfo.h"
#include "CSkillEnchantDB.h"
#include "SkillEnchantOperator.h"
#include "EnchantDataInfo.h"
#include "CLog.h"

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

	int acquiredLevel = self->GetUser()->GetAcquiredSkillLevel(skillId);
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
			self->Send("ch", 0xFE, 0x5E);
			return false;
		} else if (skillLevel % 100 == acquiredLevel % 100) {
			if (enchantType != 3) {
				enchantType = 3;
			}
		} else {
			self->Send("ch", 0xFE, 0x5E);
			return false;
		}
	}

	SkillEnchantOperator *op = SkillEnchantOperator::GetOperator(enchantType);
	if (!op) {
		return false;
	}

	CSkillEnchantInfo *info = 0;
	if (enchantType == 2) {
		info = CSkillEnchantDB::GetInstance()->GetSkillEnchantInfo(skillId, acquiredLevel);
	} else {
		info = CSkillEnchantDB::GetInstance()->GetSkillEnchantInfo(skillId, skillLevel);
	}
	if (!info) {
		return false;
	}

	int probability = op->CalculateProb(info, self->GetUser()->GetLevel());
	int index = (info->newEnchantLevel - 1) % 100;
	if (index >= 30 || index < 0) {
		return false;
	}

	int requiredSP = EnchantDataInfo::enchantRequirements[index].sp * op->requirementModifier;
	INT64 requiredAdena = EnchantDataInfo::enchantRequirements[index].adena * op->requirementModifier;
	if (op->operatorType == 1) {
		requiredSP *= 5;
		requiredAdena *= 5;
	}

	int itemId = info->requiredItems[enchantType];
	int itemCount = info->requiredItemCounts[enchantType];

	int outSkillLevel = skillLevel;
	if (enchantType == 2) {
		if (acquiredLevel % 100 > 1) {
			outSkillLevel = acquiredLevel - 1;
		} else {
			outSkillLevel = info->requiredSkillLevel;
		}
	}

	self->Send("chdddddddddd", 0xFE, 0x5E, enchantType, skillId, outSkillLevel,
		requiredSP, probability, 2, 57, requiredAdena, itemId, itemCount);

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

