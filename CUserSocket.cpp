
#include "CUserSocket.h"
#include "CUser.h"
#include "CLog.h"
#include "SkillEnchantOperator.h"
#include "Utils.h"
#include "CSkillEnchantInfo.h"
#include "CSkillEnchantDB.h"
#include "EnchantDataInfo.h"
#include "MyExt64.h"

typedef bool (__cdecl *UserSocketPacketHandler)(CUserSocket*, const BYTE*, BYTE);

UserSocketPacketHandler *exHandlers = reinterpret_cast<UserSocketPacketHandler*>(0x121C0D60);

CUserSocketAssemble_t CUserSocket::Assemble = reinterpret_cast<CUserSocketAssemble_t>(0x68F99C);
CUserSocketDisassemble_t CUserSocket::Disassemble = reinterpret_cast<CUserSocketDisassemble_t>(0x68ED10);

namespace {

void ReplaceOutExOpcode(unsigned int address, BYTE opcode)
{
	WriteMemoryBYTE(address + 2, static_cast<BYTE>(opcode));
	WriteMemoryBYTE(address + 9, static_cast<BYTE>(0xFE - opcode));
}

}

void CUserSocket::HookPacketHandlers()
{
	for (size_t i(0) ; i < 0x100 ; ++i) {
		if (!exHandlers[i]) {
			exHandlers[i] = DummyPacketEx;
		}
	}
	if (MyExt64::GetProtocolVersion() == MyExt64::ProtocolVersionGraciaFinalUpdate1) {
		ReplaceOutExOpcode(0x7ED0D8, 0xA7); // FE:A6 -> FE:A7
		ReplaceOutExOpcode(0x7ED213, 0xA7); // FE:A6 -> FE:A7
		ReplaceOutExOpcode(0x7ED3DB, 0xA7); // FE:A6 -> FE:A7
		ReplaceOutExOpcode(0x7ED537, 0xA7); // FE:A6 -> FE:A7
		ReplaceOutExOpcode(0x7EDA07, 0xA7); // FE:A6 -> FE:A7
		ReplaceOutExOpcode(0x7EDF2F, 0xA7); // FE:A6 -> FE:A7
		ReplaceOutExOpcode(0x47613C, 0xA8); // FE:A7 -> FE:A8
		ReplaceOutExOpcode(0x476383, 0xA8); // FE:A7 -> FE:A8
		ReplaceOutExOpcode(0x915BE1, 0xA9); // FE:A8 -> FE:A9
		ReplaceOutExOpcode(0x596FD1, 0xAA); // FE:A9 -> FE:AA
		ReplaceOutExOpcode(0x5AB7D2, 0xAA); // FE:A9 -> FE:AA
		ReplaceOutExOpcode(0x5ABD02, 0xAA); // FE:A9 -> FE:AA
		ReplaceOutExOpcode(0x7EE2EB, 0xAA); // FE:A9 -> FE:AA
		ReplaceOutExOpcode(0x7EE44F, 0xAA); // FE:A9 -> FE:AA
		ReplaceOutExOpcode(0x7EE6EA, 0xAA); // FE:A9 -> FE:AA
		ReplaceOutExOpcode(0x7EE8CD, 0xAA); // FE:A9 -> FE:AA
		ReplaceOutExOpcode(0x9124B5, 0xAA); // FE:A9 -> FE:AA
		ReplaceOutExOpcode(0x912545, 0xAA); // FE:A9 -> FE:AA
		ReplaceOutExOpcode(0x91257A, 0xAA); // FE:A9 -> FE:AA
		ReplaceOutExOpcode(0x485364, 0xAB); // FE:AA -> FE:AB
		ReplaceOutExOpcode(0x971667, 0xAB); // FE:AA -> FE:AB
		ReplaceOutExOpcode(0x8CFBC3, 0xAD); // FE:AB -> FE:AD
	}
	if (MyExt64::GetProtocolVersion() >= MyExt64::ProtocolVersionGraciaEpilogue) {
		// client packets:
		exHandlers[0x46] = RequestExSkillEnchantInfoDetailGraciaEpilogue;
		exHandlers[0x78] = exHandlers[0x65];
		exHandlers[0x79] = exHandlers[0x66];
		exHandlers[0x7A] = exHandlers[0x67];
		exHandlers[0x7B] = exHandlers[0x68];
		exHandlers[0x65] = exHandlers[0x66] = exHandlers[0x67] = exHandlers[0x68] = DummyPacketEx;

		// server packets:
		WriteInstructionCall(0x8B0E7B, reinterpret_cast<UINT32>(AssembleInventoryUpdateItem1GraciaEpilogue));
		WriteInstructionCall(0x8B133C, reinterpret_cast<UINT32>(AssembleInventoryUpdateItem2GraciaEpilogue));
		WriteInstructionCall(0x8F2446, reinterpret_cast<UINT32>(AssembleSkillListItemGraciaEpilogue));
		WriteInstructionCall(0x8E33BE, reinterpret_cast<UINT32>(AssembleItemListItem1GraciaEpilogue));
		WriteInstructionCall(0x8E2A82, reinterpret_cast<UINT32>(AssembleItemListItem2GraciaEpilogue));
		
		ReplaceOutExOpcode(0x7ED0D8, 0xB8); // FE:A6 -> FE:B8
		ReplaceOutExOpcode(0x7ED213, 0xB8); // FE:A6 -> FE:B8
		ReplaceOutExOpcode(0x7ED3DB, 0xB8); // FE:A6 -> FE:B8
		ReplaceOutExOpcode(0x7ED537, 0xB8); // FE:A6 -> FE:B8
		ReplaceOutExOpcode(0x7EDA07, 0xB8); // FE:A6 -> FE:B8
		ReplaceOutExOpcode(0x7EDF2F, 0xB8); // FE:A6 -> FE:B8
		ReplaceOutExOpcode(0x47613C, 0xB9); // FE:A7 -> FE:B9
		ReplaceOutExOpcode(0x476383, 0xB9); // FE:A7 -> FE:B9
		ReplaceOutExOpcode(0x915BE1, 0xBA); // FE:A8 -> FE:BA
		ReplaceOutExOpcode(0x596FD1, 0xBB); // FE:A9 -> FE:BB
		ReplaceOutExOpcode(0x5AB7D2, 0xBB); // FE:A9 -> FE:BB
		ReplaceOutExOpcode(0x5ABD02, 0xBB); // FE:A9 -> FE:BB
		ReplaceOutExOpcode(0x7EE2EB, 0xBB); // FE:A9 -> FE:BB
		ReplaceOutExOpcode(0x7EE44F, 0xBB); // FE:A9 -> FE:BB
		ReplaceOutExOpcode(0x7EE6EA, 0xBB); // FE:A9 -> FE:BB
		ReplaceOutExOpcode(0x7EE8CD, 0xBB); // FE:A9 -> FE:BB
		ReplaceOutExOpcode(0x9124B5, 0xBB); // FE:A9 -> FE:BB
		ReplaceOutExOpcode(0x912545, 0xBB); // FE:A9 -> FE:BB
		ReplaceOutExOpcode(0x91257A, 0xBB); // FE:A9 -> FE:BB
		ReplaceOutExOpcode(0x485364, 0xBC); // FE:AA -> FE:BC
		ReplaceOutExOpcode(0x971667, 0xBC); // FE:AA -> FE:BC
		ReplaceOutExOpcode(0x8CFBC3, 0xBE); // FE:AB -> FE:BE
		ReplaceOutExOpcode(0x8ADEB8, 0xBE); // FE:AC -> FE:BD
	}

	WriteMemoryBYTES(0x912880, "\x30\xC0", 2); // ONLY FOR TESTING - DummyPacket not to disconnect user
}

bool __cdecl CUserSocket::DummyPacketEx(CUserSocket *self, const BYTE *packet, BYTE opcode)
{
	CLog::Add(CLog::Blue, L"[DummyPacketEx] %02X: %02X %02X %02X %02X %02X %02X %02X %02X",
		opcode, packet[0], packet[1], packet[2], packet[3], packet[4], packet[5], packet[6], packet[7]);
	return false;
}

bool __cdecl CUserSocket::RequestExSkillEnchantInfoDetailGraciaEpilogue(CUserSocket *self, const BYTE *packet, BYTE opcode)
{
	(void) opcode;

	UINT32 enchantType = 0;
	UINT32 skillId = 0;
	UINT32 skillLevel = 0;

	Disassemble(packet, "ddd", &enchantType, &skillId, &skillLevel);

	//CLog::Add(CLog::Blue, L"[RequestExSkillEnchantInfoDetail] enchantType=%d skillId=%d skillLevel=%d",
	//	enchantType, skillId, skillLevel);

	if (enchantType > 3) {
		CLog::Add(CLog::Red, L"[RequestExSkillEnchantInfoDetail] exploit attempt, invalid enchant operator type [%d]", enchantType);
		return true;
	}

	SkillEnchantOperator *op = SkillEnchantOperator::GetOperator(enchantType);

	//CLog::Add(CLog::Blue, L"[RequestExSkillEnchantInfoDetail] SkillEnchantOperator %p", op);

	if (op) {
		if (!self->GetUser()) {
			CLog::Add(CLog::Red, L"[RequestExSkillEnchantInfoDetail] user null at file %s line %d", __FILEW__, __LINE__);
			return false;
		}

		CSkillEnchantInfo *info = 0;
		if (enchantType == 2) {
			int acquiredLevel = self->GetUser()->GetAcquiredSkillLevel(skillId);
			if (acquiredLevel % 100 > 1) {
				--acquiredLevel;
			}
			//CLog::Add(CLog::Blue, L"[RequestExSkillEnchantInfoDetail] GetSkillEnchantInfo(%d, %d)", skillId, acquiredLevel);
			info = CSkillEnchantDB::GetInstance()->GetSkillEnchantInfo(skillId, acquiredLevel);
		} else {
			//CLog::Add(CLog::Blue, L"[RequestExSkillEnchantInfoDetail] GetSkillEnchantInfo(%d, %d)", skillId, skillLevel);
			info = CSkillEnchantDB::GetInstance()->GetSkillEnchantInfo(skillId, skillLevel);
		}

		//CLog::Add(CLog::Blue, L"[RequestExSkillEnchantInfoDetail] CSkillEnchantInfo %p", info);

		if (info) {
			int probability = op->CalculateProb(info, self->GetUser()->GetLevel());

			//CLog::Add(CLog::Blue, L"[RequestExSkillEnchantInfoDetail] probability %d", probability);

			int index = info->newEnchantLevel - 1;

			//CLog::Add(CLog::Blue, L"[RequestExSkillEnchantInfoDetail] index %d", index);

			if (index >= 30 || index < 0) {
				CLog::Add(CLog::Red,
					L"[RequestExSkillEnchantInfoDetail] invalid index skillId=%d skillLevel=%d index=%d user [%s]",
					skillId, skillLevel, index, self->GetUser()->GetName());
				return false;
			}

			//CLog::Add(CLog::Blue, L"[RequestExSkillEnchantInfoDetail] index=%d", index);

			int requiredSP = EnchantDataInfo::enchantRequirements[index].sp * op->requirementModifier;
			INT64 requiredAdena = EnchantDataInfo::enchantRequirements[index].adena * op->requirementModifier;
			if (op->operatorType == 1) {
				requiredSP *= 5;
				requiredAdena *= 5;
			}

			//CLog::Add(CLog::Blue, L"[RequestExSkillEnchantInfoDetail] requiredSP=%d requiredAdena=%d", requiredSP, requiredAdena);

			int itemId = info->requiredItems[enchantType];
			int itemCount = (int)info->requiredItemCounts[enchantType];

			//CLog::Add(CLog::Blue, L"[RequestExSkillEnchantInfoDetail] itemId=%d itemCount=%d", itemId, itemCount);

			self->Send("chdddddddddd", 0xFE, 0x5E, enchantType, skillId, skillLevel,
				requiredSP, probability, 2, 57, requiredAdena, itemId, itemCount);
			// 0x5e should be class ID but maybe it's not necessary
		} else {
			CLog::Add(CLog::Red, L"[RequestExSkillEnchantInfoDetail] null skill info for skillId=%d skillLevel=%d", skillId, skillLevel);
		}
	} else {
		CLog::Add(CLog::Red, L"[RequestExSkillEnchantInfoDetail] null skill enchant operator");
	}
	return false;
}

int __cdecl CUserSocket::AssembleInventoryUpdateItem1GraciaEpilogue(char *buffer, int maxSize, const char *format, UINT32 a, UINT32 b, UINT32 c, UINT64 d, UINT16 e, UINT16 f, UINT16 g, UINT32 h, UINT64 i, UINT16 j, UINT16 k, UINT16 l, UINT16 m, UINT16 n, UINT16 o, UINT16 p, UINT16 q)
{
	//                                abcdefghijklmnopqr000
	return Assemble(buffer, maxSize, "dddQhhhdQhhhhhhhhhhh", a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, 0, 0, 0);
}

int __cdecl CUserSocket::AssembleInventoryUpdateItem2GraciaEpilogue(char *buffer, int maxSize, const char *format, UINT32 a, UINT32 b, UINT32 c, UINT64 d, UINT16 e, UINT16 f, UINT16 g, UINT32 h, UINT64 i, UINT64 j,	UINT16 k, UINT16 l, UINT16 m, UINT16 n, UINT16 o, UINT16 p, UINT16 q, UINT16 r)
{
	//                                abcdefghijklmnopq000
	return Assemble(buffer, maxSize, "dddQhhhdQQhhhhhhhhhhh", a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, 0, 0, 0);
}

int __cdecl CUserSocket::AssembleSkillListItemGraciaEpilogue(char *buffer, int maxSize, const char *format, UINT32 a, UINT32 b, UINT32 c, UINT8 d)
{
	//                                abcd0
	return Assemble(buffer, maxSize, "dddcc", a, b, c, d, 0);
}

int __cdecl CUserSocket::AssembleItemListItem1GraciaEpilogue(char *buffer, int maxSize, const char *format, UINT16 a, UINT32 b, UINT32 c, UINT32 d, UINT64 e, UINT16 f, UINT16 g, UINT16 h, UINT32 i, UINT16 j, UINT16 k, UINT16 l, UINT16 m, UINT32 n, UINT16 o, UINT16 p, UINT16 q, UINT16 r, UINT16 s, UINT16 t, UINT16 u, UINT16 v, UINT32 w)
{
	//                                abcdefghijklmnopqrstuvw
	return Assemble(buffer, maxSize, "hdddQhhhdhhhhdhhhhhhhhdhhh", a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, 0, 0, 0);
}

int __cdecl CUserSocket::AssembleItemListItem2GraciaEpilogue(char *buffer, int maxSize, const char *format, UINT16 a, UINT16 b, UINT32 c, UINT32 d, UINT32 e, UINT64 f, UINT16 g, UINT16 h, UINT16 i, UINT32 j, UINT16 k, UINT16 l, UINT16 m, UINT16 n, UINT32 o, UINT16 p, UINT16 q, UINT16 r, UINT16 s, UINT16 t, UINT16 u, UINT16 v, UINT16 w, UINT32 x)
{
	//                                abcdefghijklmnopqrstuvwx
	return Assemble(buffer, maxSize, "hhdddQhhhdhhhhdhhhhhhhhdhhh", a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, 0, 0, 0);
}

CUser* CUserSocket::GetUser()
{
	return user;
}

void CUserSocket::Send(const char *format, ...)
{
	va_list va;
	va_start(va, format);
	SendV(format, va);
	va_end(va);
}

void CUserSocket::SendV(const char *format, va_list va)
{
	typedef void (__thiscall *t)(CUserSocket*, const char*, va_list);
	t f = reinterpret_cast<t>(0x859934);
	f(this, format, va);
}

