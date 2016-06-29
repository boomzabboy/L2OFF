
#include "GraciaEpilogue.h"
#include "CSkillEnchantInfo.h"
#include "CSkillEnchantDB.h"
#include "CLog.h"

void GraciaEpilogue::Init()
{
	// packets
	WriteInstructionCall(0x8B0E7B, reinterpret_cast<UINT32>(AssembleInventoryUpdateItem1));
	WriteInstructionCall(0x8B133C, reinterpret_cast<UINT32>(AssembleInventoryUpdateItem2));
	WriteInstructionCall(0x8F2446, reinterpret_cast<UINT32>(AssembleSkillListItem));
	WriteInstructionCall(0x8E33BE, reinterpret_cast<UINT32>(AssembleItemListItem1));
	WriteInstructionCall(0x8E2A82, reinterpret_cast<UINT32>(AssembleItemListItem2));
	WriteInstructionCall(0x95B54D, reinterpret_cast<UINT32>(AssembleWarehouseDepositListItem));
	WriteInstructionCall(0x5B49B0, reinterpret_cast<UINT32>(AssembleWarehouseWithdrawListItem));
	WriteInstructionCall(0x5C46EA, reinterpret_cast<UINT32>(AssembleWarehouseWithdrawListItem));
	WriteInstructionCall(0x5DBBBF, reinterpret_cast<UINT32>(AssembleWarehouseGMListItem));
	WriteInstructionCall(0x88C7D0, reinterpret_cast<UINT32>(SendETCBuffStatusInfo));
	WriteMemoryBYTES(0x8CFBCD, "\x48\x8B\xC8\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90", 14);
	WriteInstructionCall(0x8CFBD0, reinterpret_cast<UINT32>(SendExBrBroadcastEventState));
	WriteMemoryBYTES(0x907FF6, "\x48\x8B\xCF\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90", 13);
	WriteInstructionCall(0x907FF9, reinterpret_cast<UINT32>(SendRelationChanged));
	WriteMemoryBYTES(0x90835A, "\x48\x8B\xCB\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90", 13);
	WriteInstructionCall(0x90835D, reinterpret_cast<UINT32>(SendRelationChanged));
	WriteMemoryBYTES(0x90891E, "\x48\x8B\x4C\x24\x68\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90", 15);
	WriteInstructionCall(0x908923, reinterpret_cast<UINT32>(SendRelationChanged));
	WriteInstructionCall(0x8730D3, reinterpret_cast<UINT32>(AssembleTradeStartItem));
	WriteInstructionCall(0x8BA794, reinterpret_cast<UINT32>(AssemblePrivateStoreListSellItem));
	WriteInstructionCall(0x8B2987, reinterpret_cast<UINT32>(AssemblePrivateStoreManageListBuyItem1));
	WriteInstructionCall(0x8B25A7, reinterpret_cast<UINT32>(AssemblePrivateStoreManageListBuyItem2));
	WriteInstructionCall(0x8B2E16, reinterpret_cast<UINT32>(DisassembleSetPrivateStoreListBuyItem1));
	WriteInstructionCall(0x8B327A, reinterpret_cast<UINT32>(DisassembleSetPrivateStoreListBuyItem1));
	WriteInstructionCall(0x8BB459, reinterpret_cast<UINT32>(AssemblePrivateStoreBuyList));

	// buy/sell
	WriteAddress(0xA26CD0+3, reinterpret_cast<UINT32>(NpcShowBuySellPagePacket));
	WriteAddress(0xA26CA8+3, reinterpret_cast<UINT32>(NpcShowBuySellPagePacket));
	WriteMemoryBYTES(0x747E9B, "\x48\x8B\xCB\x48\x31\xD2\x90\x90\x90\x90\x90\x90\x90\x90", 14);
	WriteInstructionCall(0x747E9B+6, reinterpret_cast<UINT32>(SendBuySellWrapper));
	WriteMemoryBYTES(0x746EF6, "\x48\x31\xD2\x48\xFF\xC2\x90\x90\x90\x90\x90", 11);
	WriteInstructionCall(0x746EF6+6, reinterpret_cast<UINT32>(SendBuySellWrapper));
	WriteInstructionCall(0x747C48, reinterpret_cast<UINT32>(AssembleBuySellListItem));
	WriteInstructionCall(0x746C42, reinterpret_cast<UINT32>(AssembleBuySellListItem));
	WriteInstructionCall(0x5B6388, reinterpret_cast<UINT32>(UserShowHTMLAfterBuySell));
	WriteInstructionCall(0x5B5B42, reinterpret_cast<UINT32>(UserShowHTMLAfterBuySell));
    WriteInstructionCall(0x5B4B14 + 0x18A, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x5B4B14 + 0x249, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x5B4B14 + 0x4C7, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x5B504C + 0x17F, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x5B504C + 0x5B2, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x5B5678 + 0x485, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x5B5BD0 + 0x74E, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x5C48B4 + 0x1AF, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x5C48B4 + 0x790, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x5C50E0 + 0x205, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x5C50E0 + 0x7D8, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    //WriteInstructionCall(0x746318 + 0x3E2, reinterpret_cast<UINT32>(CUserReleaseEconomy)); // not this one
    //WriteInstructionCall(0x747184 + 0x3E7, reinterpret_cast<UINT32>(CUserReleaseEconomy)); // not this one
    WriteInstructionCall(0x748200 + 0x39A, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x8CB090 + 0x525, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x8F2244 + 0x87, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x91D6C0 + 0x266, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x91D9C8 + 0x46A, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x92F924 + 0x1647, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x931090 + 0xCDA, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x93276C + 0x681, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x945A6C + 0x485, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x946018 + 0x470, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x9465A4 + 0x3E8, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x946AB0 + 0x3F8, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x946FCC + 0x2CD, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x947398 + 0x2ED, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x9477A4 + 0x2F9, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x947BC0 + 0x2F9, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x95C039, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x95C97D, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x95CC68, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x95CFDB, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x95D1DD, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x95D452, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x95DA32, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x95E29D, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x95E57B, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x95E8F3, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x95EAFA, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x95ED40, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x95F0DD, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x95F930, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x95FD93, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x95FF83, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x960633, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x960A9F, reinterpret_cast<UINT32>(CUserReleaseEconomy));
    WriteInstructionCall(0x960CA0, reinterpret_cast<UINT32>(CUserReleaseEconomy));
	WriteMemoryBYTES(0x94B1F3, "\x48\x89\xF1\x90\x90\x90\x90", 7); // mov rcx, rsi - get CUser* in rcx
	WriteInstructionCall(0x94B1FA, reinterpret_cast<UINT32>(NpcSocketSendHtmlCmdMenuSelect));
	WriteMemoryBYTE(0x5B5B69 + 2, 0); // don't show inventory after buy
	WriteMemoryBYTE(0x5B5B7A + 2, 0); // don't show inventory after buy
	WriteMemoryBYTE(0x5B63B3 + 2, 0); // don't show inventory after sell
	WriteMemoryBYTE(0x5B63C4 + 2, 0); // don't show inventory after sell

	// skill enchant
	WriteMemoryBYTE(0x82509F, 0xEB); // don't require NPC for RequestExEnchantSkillInfo
	WriteMemoryBYTE(0x827239, 0xEB); // don't require NPC for RequestExEnchantSkill
	WriteMemoryBYTE(0x8248C2, 0xEB); // don't require NPC for RequestExEnchantSkillRouteChange
	WriteMemoryBYTE(0x824916, 0xEB); // don't require NPC for RequestExEnchantSkillRouteChange
	WriteInstructionCall(0x827D60, reinterpret_cast<UINT32>(SkillEnchantOperatorOperateSuccess));
	WriteInstructionCall(0x827FAE, reinterpret_cast<UINT32>(SkillEnchantOperatorOperateFail));
	WriteMemoryQWORD(0xC01AF8, reinterpret_cast<UINT64>(SkillEnchantOperatorOperateNormal));
	WriteInstructionCall(0x8285DE, reinterpret_cast<UINT32>(SkillEnchantOperatorOperateSuccess));
	WriteMemoryQWORD(0xC01B58, reinterpret_cast<UINT64>(SkillEnchantOperatorOperateSafe));
	WriteMemoryQWORD(0xC01BB8, reinterpret_cast<UINT64>(SkillEnchantOperatorOperateUntrain));
	WriteMemoryQWORD(0xC01D78, reinterpret_cast<UINT64>(SkillEnchantOperatorOperateRouteChange));
}

int __cdecl GraciaEpilogue::AssembleInventoryUpdateItem1(char *buffer, int maxSize, const char *format, UINT32 a, UINT32 b, UINT32 c, UINT64 d, UINT16 e, UINT16 f, UINT16 g, UINT32 h, UINT64 i, UINT16 j, UINT16 k, UINT16 l, UINT16 m, UINT16 n, UINT16 o, UINT16 p, UINT16 q)
{
	//                                abcdefghijklmnopqr000
	return Assemble(buffer, maxSize, "dddQhhhdQhhhhhhhhhhh", a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, 0, 0, 0);
}

int __cdecl GraciaEpilogue::AssembleInventoryUpdateItem2(char *buffer, int maxSize, const char *format, UINT32 a, UINT32 b, UINT32 c, UINT64 d, UINT16 e, UINT16 f, UINT16 g, UINT32 h, UINT64 i, UINT64 j,	UINT16 k, UINT16 l, UINT16 m, UINT16 n, UINT16 o, UINT16 p, UINT16 q, UINT16 r)
{
	//                                abcdefghijklmnopq000
	return Assemble(buffer, maxSize, "dddQhhhdQQhhhhhhhhhhh", a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, 0, 0, 0);
}

int __cdecl GraciaEpilogue::AssembleSkillListItem(char *buffer, int maxSize, const char *format, UINT32 a, UINT32 b, UINT32 c, UINT8 d)
{
	bool enchantable = false;
	CSkillEnchantInfo *info = CSkillEnchantDB::GetInstance()->GetSkillEnchantInfo(c, max(101, b));
	if (info) {
		enchantable = info->requiredSkillLevel <= b;
	}
	//                                abcd?
	return Assemble(buffer, maxSize, "dddcc", a, b, c, d, enchantable);
}

int __cdecl GraciaEpilogue::AssembleItemListItem1(char *buffer, int maxSize, const char *format, UINT16 a, UINT32 b, UINT32 c, UINT32 d, UINT64 e, UINT16 f, UINT16 g, UINT16 h, UINT32 i, UINT16 j, UINT16 k, UINT16 l, UINT16 m, UINT32 n, UINT16 o, UINT16 p, UINT16 q, UINT16 r, UINT16 s, UINT16 t, UINT16 u, UINT16 v, UINT32 w)
{
	//                                abcdefghijklmnopqrstuvw000
	return Assemble(buffer, maxSize, "hdddQhhhdhhhhdhhhhhhhhdhhh", a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, 0, 0, 0);
}

int __cdecl GraciaEpilogue::AssembleItemListItem2(char *buffer, int maxSize, const char *format, UINT16 a, UINT16 b, UINT32 c, UINT32 d, UINT32 e, UINT64 f, UINT16 g, UINT16 h, UINT16 i, UINT32 j, UINT16 k, UINT16 l, UINT16 m, UINT16 n, UINT32 o, UINT16 p, UINT16 q, UINT16 r, UINT16 s, UINT16 t, UINT16 u, UINT16 v, UINT16 w, UINT32 x)
{
	//                                abcdefghijklmnopqrstuvwx000
	return Assemble(buffer, maxSize, "hhdddQhhhdhhhhdhhhhhhhhdhhh", a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, 0, 0, 0);
}

int __cdecl GraciaEpilogue::AssembleWarehouseDepositListItem(char *buffer, int maxSize, const char *format, UINT16 a, UINT32 b, UINT32 c, UINT64 d, UINT16 e, UINT16 f, UINT32 g, UINT16 h, UINT16 i, UINT16 j, UINT32 k, UINT32 l, UINT32 m, UINT16 n, UINT16 o, UINT16 p, UINT16 q, UINT16 r, UINT16 s, UINT16 t, UINT16 u, UINT32 v, UINT32 w)
{
	//                                abcdefghijklmnopqrstuvw000
	return Assemble(buffer, maxSize, "hddQhhdhhhdddhhhhhhhhddhhh", a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, 0, 0, 0);
}

int __cdecl GraciaEpilogue::AssembleWarehouseWithdrawListItem(char *buffer, int maxSize, const char *format, UINT16 a, UINT32 b, UINT32 c, UINT64 d, UINT16 e, UINT16 f, UINT32 g, UINT16 h, UINT16 i, UINT16 j, UINT32 k, UINT32 l, UINT32 m, UINT16 n, UINT16 o, UINT16 p, UINT16 q, UINT16 r, UINT16 s, UINT16 t, UINT16 u, UINT32 v, UINT32 w)
{
	//                                abcdefghijklmnopqrstuvw000
	return Assemble(buffer, maxSize, "hddQhhdhhhdddhhhhhhhhddhhh", a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, 0, 0, 0);
}

int __cdecl GraciaEpilogue::AssembleWarehouseGMListItem(char *buffer, int maxSize, const char *format, UINT16 a, UINT32 b, UINT32 c, UINT64 d, UINT16 e, UINT16 f, UINT32 g, UINT16 h, UINT16 i, UINT16 j, UINT32 k, UINT32 l, UINT16 m, UINT16 n, UINT16 o, UINT16 p, UINT16 q, UINT16 r, UINT16 s, UINT16 t, UINT32 u, UINT32 v, UINT32 w)
{
	//                                abcdefghijklmnopqrstuvw000
	return Assemble(buffer, maxSize, "hddQhhdhhhdddhhhhhhhhddhhh", a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, 0, 0, 0);
}

void __cdecl GraciaEpilogue::SendETCBuffStatusInfo(CUserSocket *socket, const char *format, BYTE opcode, UINT32 a, UINT32 b, UINT32 c, UINT32 d, UINT32 e, UINT32 f, UINT32 g, UINT32 h)
{
	(void) e;
	if (!socket) {
		return;
	}
	CUser *user = socket->user;
	if (!user) {
		return;
	}
	UINT32 x = reinterpret_cast<int(*)(CUser*)>(0x53A14C)(user);
	double p = reinterpret_cast<double(*)(CUser*)>(0x536300)(user);
	UINT32 y = 0;
	if (p >= 1.9) { // p is in fact 2
		y = 4;
	} else if (p >= 1.7) { // p is in fact 1.728
		y = 3;
	} else if (p >= 1.4) { // p is in fact 1.44
		y = 2;
	} else if (p >= 1.1) { // p is in face 1.2
		y = 1;
	}
	//             abcdxyfgh
	socket->Send("cddddddddd", opcode, a, b, c, d, x, y, f, g, h);
}

void __cdecl GraciaEpilogue::SendExBrBroadcastEventState(CUserSocket *socket, void *unused, BYTE opcode, UINT16 opcodeEx, UINT32 a, UINT32 b)
{
	//              ab0000000, both h at end should be string (h = 0 is empty string)
	socket->Send("chdddddddhh", opcode, opcodeEx, a, b, 0, 0, 0, 0, 0, 0, 0);
}

void __cdecl GraciaEpilogue::SendRelationChanged(CUserSocket *socket, void *unused, BYTE opcode, UINT32 a, UINT32 b, UINT32 c, UINT32 d, UINT32 e)
{
	//             1abcde
	socket->Send("cdddddd", opcode, 1, a, b, c, d, e);
}

int __cdecl GraciaEpilogue::AssembleTradeStartItem(char *buffer, int maxSize, const char *format, UINT16 a, UINT32 b, UINT32 c, UINT64 d, UINT16 e, UINT16 f, UINT32 g, UINT16 h, UINT64 i, UINT16 j, UINT16 k, UINT16 l, UINT16 m, UINT16 n, UINT16 o, UINT16 p, UINT16 q, UINT16 r)
{
	//                                abcdefghijklmnopqr000
	return Assemble(buffer, maxSize, "hddQhhdhhhhhhhhhhhhhh", a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, 0, 0, 0);
}

int __cdecl GraciaEpilogue::AssemblePrivateStoreListSellItem(char *buffer, int maxSize, const char *format, UINT32 a, UINT32 b, UINT32 c, UINT64 d, UINT16 e, UINT16 f, UINT16 g, UINT32 h, UINT64 i, UINT64 j, UINT16 k, UINT16 l, UINT16 m, UINT16 n, UINT16 o, UINT16 p, UINT16 q, UINT16 r)
{
	//                                abcdefghijklmnopqr000
	return Assemble(buffer, maxSize, "dddQhhhdQQhhhhhhhhhhh", a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, 0, 0, 0);
}

int __cdecl GraciaEpilogue::AssemblePrivateStoreManageListBuyItem1(char *buffer, int maxSize, const char *format, UINT32 a, UINT16 b, UINT64 c, UINT64 d, UINT16 e, UINT32 f, UINT16 g, UINT64 h, UINT64 i, UINT16 j, UINT16 k, UINT16 l, UINT16 m, UINT16 n, UINT16 o, UINT16 p, UINT16 q)
{
	//                                abcdefghijklmnopq000
	return Assemble(buffer, maxSize, "dhQQhdhQQhhhhhhhhhhh", a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, 0, 0, 0);
}

int __cdecl GraciaEpilogue::AssemblePrivateStoreManageListBuyItem2(char *buffer, int maxSize, const char *format, UINT32 a, UINT16 b, UINT64 c, UINT64 d, UINT16 e, UINT32 f, UINT16 g, UINT16 h, UINT16 i, UINT16 j, UINT16 k, UINT16 l, UINT16 m, UINT16 n, UINT16 o)
{
	//                                abcdefghijklmno000
	return Assemble(buffer, maxSize, "dhQQhdhhhhhhhhhhhh", a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, 0, 0, 0);
}

const unsigned char* __cdecl GraciaEpilogue::DisassembleSetPrivateStoreListBuyItem1(const unsigned char *data, const char *format, UINT32 *a, UINT16 *b, UINT16 *c, UINT64 *d, UINT64 *e)
{
	UINT32 f, g, h, i;
	//                        abcde----
	return Disassemble(data, "dhhQQdddd", a, b, c, d, e, &f, &g, &h, &i);
}

int __cdecl GraciaEpilogue::AssemblePrivateStoreBuyList(char *buffer, int maxSize, const char *format, UINT32 a, UINT32 b, UINT16 c, UINT64 d, UINT64 e, UINT16 f, UINT32 g, UINT16 h, UINT64 i, UINT64 j, UINT16 k, UINT16 l, UINT16 m, UINT16 n, UINT16 o, UINT16 p, UINT16 q, UINT16 r)
{
	//                                abcdefghijklmnopqr000
	return Assemble(buffer, maxSize, "ddhQQhdhQQhhhhhhhhhhh", a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, 0, 0, 0);
}

