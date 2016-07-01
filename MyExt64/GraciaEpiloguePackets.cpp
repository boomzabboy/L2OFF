
#include "GraciaEpilogue.h"
#include "CSkillEnchantInfo.h"
#include "CSkillEnchantDB.h"
#include "CLog.h"

void GraciaEpilogue::InitPackets()
{
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

