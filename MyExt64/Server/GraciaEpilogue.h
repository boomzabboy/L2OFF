
#pragma once

#include <Server/CUserSocket.h>
#include <Server/SkillEnchantOperator.h>

class GraciaEpilogue {
public:
	static void Init();
	static void Load();

	static void InitPackets();
	static int __cdecl AssembleInventoryUpdateItem1(char *buffer, int maxSize, const char *format, UINT32 a, UINT32 b, UINT32 c, UINT64 d, UINT16 e, UINT16 f, UINT16 g, UINT32 h, UINT64 i, UINT16 j, UINT16 k, UINT16 l, UINT16 m, UINT16 n, UINT16 o, UINT16 p, UINT16 q);
	static int __cdecl AssembleInventoryUpdateItem2(char *buffer, int maxSize, const char *format, UINT32 a, UINT32 b, UINT32 c, UINT64 d, UINT16 e, UINT16 f, UINT16 g, UINT32 h, UINT64 i, UINT64 j, UINT16 k, UINT16 l, UINT16 m, UINT16 n, UINT16 o, UINT16 p, UINT16 q, UINT16 r);
	static int __cdecl AssembleSkillListItem(char *buffer, int maxSize, CUser *user, UINT32 a, UINT32 b, UINT32 c, UINT32 d);
	static int __cdecl AssembleItemListItem1(char *buffer, int maxSize, const char *format, UINT16 a, UINT32 b, UINT32 c, UINT32 d, UINT64 e, UINT16 f, UINT16 g, UINT16 h, UINT32 i, UINT16 j, UINT16 k, UINT16 l, UINT16 m, UINT32 n, UINT16 o, UINT16 p, UINT16 q, UINT16 r, UINT16 s, UINT16 t, UINT16 u, UINT16 v, UINT32 w);
	static int __cdecl AssembleItemListItem2(char *buffer, int maxSize, const char *format, UINT16 a, UINT16 b, UINT32 c, UINT32 d, UINT32 e, UINT64 f, UINT16 g, UINT16 h, UINT16 i, UINT32 j, UINT16 k, UINT16 l, UINT16 m, UINT16 n, UINT32 o, UINT16 p, UINT16 q, UINT16 r, UINT16 s, UINT16 t, UINT16 u, UINT16 v, UINT16 w, UINT32 x);
	static int __cdecl AssembleWarehouseDepositListItem(char *buffer, int maxSize, const char *format, UINT16 a, UINT32 b, UINT32 c, UINT64 d, UINT16 e, UINT16 f, UINT32 g, UINT16 h, UINT16 i, UINT16 j, UINT32 k, UINT32 l, UINT32 m, UINT16 n, UINT16 o, UINT16 p, UINT16 q, UINT16 r, UINT16 s, UINT16 t, UINT16 u, UINT32 v, UINT32 w);
	static int __cdecl AssembleWarehouseWithdrawListItem(char *buffer, int maxSize, const char *format, UINT16 a, UINT32 b, UINT32 c, UINT64 d, UINT16 e, UINT16 f, UINT32 g, UINT16 h, UINT16 i, UINT16 j, UINT32 k, UINT32 l, UINT32 m, UINT16 n, UINT16 o, UINT16 p, UINT16 q, UINT16 r, UINT16 s, UINT16 t, UINT16 u, UINT32 v, UINT32 w);
	static int __cdecl AssembleWarehouseGMListItem(char *buffer, int maxSize, const char *format, UINT16 a, UINT32 b, UINT32 c, UINT64 d, UINT16 e, UINT16 f, UINT32 g, UINT16 h, UINT16 i, UINT16 j, UINT32 k, UINT32 l, UINT16 m, UINT16 n, UINT16 o, UINT16 p, UINT16 q, UINT16 r, UINT16 s, UINT16 t, UINT32 u, UINT32 v, UINT32 w);
	static void __cdecl SendETCBuffStatusInfo(class CUserSocket *socket, const char *format, BYTE opcode, UINT32 a, UINT32 b, UINT32 c, UINT32 d, UINT32 e, UINT32 f, UINT32 g, UINT32 h);
	static void __cdecl SendExBrBroadcastEventState(CUserSocket *socket, void *unused, BYTE opcode, UINT16 opcodeEx, UINT32 a, UINT32 b);
	static void __cdecl SendRelationChanged(CUserSocket *socket, void *unused, BYTE opcode, UINT32 a, UINT32 b, UINT32 c, UINT32 d, UINT32 e);
	static int __cdecl AssembleTradeStartItem(char *buffer, int maxSize, const char *format, UINT16 a, UINT32 b, UINT32 c, UINT64 d, UINT16 e, UINT16 f, UINT32 g, UINT16 h, UINT64 i, UINT16 j, UINT16 k, UINT16 l, UINT16 m, UINT16 n, UINT16 o, UINT16 p, UINT16 q, UINT16 r);
	static int __cdecl AssemblePrivateStoreListSellItem(char *buffer, int maxSize, const char *format, UINT32 a, UINT32 b, UINT32 c, UINT64 d, UINT16 e, UINT16 f, UINT16 g, UINT32 h, UINT64 i, UINT64 j, UINT16 k, UINT16 l, UINT16 m, UINT16 n, UINT16 o, UINT16 p, UINT16 q, UINT16 r);
	static int __cdecl AssemblePrivateStoreManageListBuyItem1(char *buffer, int maxSize, const char *format, UINT32 a, UINT16 b, UINT64 c, UINT64 d, UINT16 e, UINT32 f, UINT16 g, UINT64 h, UINT64 i, UINT16 j, UINT16 k, UINT16 l, UINT16 m, UINT16 n, UINT16 o, UINT16 p, UINT16 q);
	static int __cdecl AssemblePrivateStoreManageListBuyItem2(char *buffer, int maxSize, const char *format, UINT32 a, UINT16 b, UINT64 c, UINT64 d, UINT16 e, UINT32 f, UINT16 g, UINT16 h, UINT16 i, UINT16 j, UINT16 k, UINT16 l, UINT16 m, UINT16 n, UINT16 o);
	static const unsigned char* __cdecl DisassembleSetPrivateStoreListBuyItem1(const unsigned char *data, const char *format, UINT32 *a, UINT16 *b, UINT16 *c, UINT64 *d, UINT64 *e);
	static int __cdecl AssemblePrivateStoreBuyList(char *buffer, int maxSize, const char *format, UINT32 a, UINT32 b, UINT16 c, UINT64 d, UINT64 e, UINT16 f, UINT32 g, UINT16 h, UINT64 i, UINT64 j, UINT16 k, UINT16 l, UINT16 m, UINT16 n, UINT16 o, UINT16 p, UINT16 q, UINT16 r);
	static int __cdecl AssemblePetItemListItem1(char *buffer, int maxSize, const char *format, UINT16 a, UINT32 b, UINT32 c, UINT64 d, UINT16 e, UINT16 f, UINT16 g, UINT32 h, UINT16 i, UINT16 j, UINT16 k, UINT16 l, UINT16 m, UINT16 n, UINT16 o, UINT16 p, UINT16 q, UINT16 r);
	static int __cdecl AssemblePetItemListItem2(char *buffer, int maxSize, const char *format, UINT16 a, UINT16 b, UINT32 c, UINT32 d, UINT64 e, UINT16 f, UINT16 g, UINT16 h, UINT32 i, UINT16 j, UINT16 k, UINT16 l, UINT16 m, UINT16 n, UINT16 o, UINT16 p, UINT16 q, UINT16 r, UINT16 s);
	static int __cdecl AssemblePartyMember(char *buffer, int maxSize, const char *format, UINT32 a, const wchar_t *b, UINT32 c, UINT32 d, UINT32 e, UINT32 f, UINT32 g, UINT32 h, UINT32 i, UINT32 j, UINT32 k, UINT32 l);
	static int __cdecl AssemblePackageSendableListItem(char *buffer, int maxSize, const char *format, UINT16 a, UINT32 b, UINT32 c, UINT64 d, UINT16 e, UINT16 f, UINT32 g, UINT16 h, UINT16 i, UINT16 j, UINT32 k, UINT16 l, UINT16 m, UINT16 n, UINT16 o, UINT16 p, UINT16 q, UINT16 r, UINT16 s);

	// buy/sell
	static void InitBuySell();
	static int __cdecl AssembleBuySellListItem(char *buffer, int maxSize, const char *format, UINT16 a, UINT32 b, UINT32 c, UINT64 d, UINT16 e, UINT16 f, UINT32 g, UINT16 h, UINT16 i, UINT16 j, UINT64 k, UINT16 l, UINT16 m, UINT16 n, UINT16 o, UINT16 p, UINT16 q, UINT16 r, UINT16 s);
	static bool __cdecl NpcShowBuySellPagePacket(void *npcSocket, const BYTE *packet);
	static void __cdecl SendBuySellWrapper(CUserSocket *socket, const unsigned char isBuy, unsigned char opcode, UINT64 adena, UINT32 buyListId, UINT16 itemCount, UINT32 size, void *data);
	static void __cdecl UserShowHTMLAfterBuySell(class CUser *user, const wchar_t *s1, const wchar_t *s2, unsigned int i);
	static bool __cdecl CUserReleaseEconomy(class CUser *self);
	static bool __cdecl BuyPacket(CUserSocket *socket, const BYTE *packet, BYTE opcode);
	static bool __cdecl SellPacket(CUserSocket *socket, const BYTE *packet, BYTE opcode);
	static void __cdecl NpcSocketSendHtmlCmdMenuSelect(class CUser *user, const char *format, BYTE opcode, UINT32 userSdIndex, UINT32 userObjectId, UINT32 npcSdIndex, INT32 ask, INT64 reply, INT32 state);
	static void __cdecl NpcSocketSendHtmlCmdMenuSelectFirst(class CUser *user, const char *format, BYTE opcode, UINT32 userSdIndex, UINT32 userObjectId, UINT32 npcSdIndex, INT32 ask, INT64 reply, INT32 state, bool first);

	// skill enchant
	static void InitSkillEnchant();
	static void LoadSkillEnchant();
	static std::pair<int, INT64> GetEnchantSpAdena(CUser *user, UINT32 &enchantType, int skillId, int skillLevel, CSkillEnchantInfo **info_);
	static void __cdecl SkillEnchantOperatorOperateSuccess(class CUser *user);
	static void __cdecl SkillEnchantOperatorOperateFail(class CUser *user);
	static bool __cdecl SkillEnchantOperatorOperateNormal(SkillEnchantOperator *self, class CUser *user, int id, int level);
	static void __cdecl SkillEnchantOperatorOperateSafeFail(class CUserSocket *socket, const char *unused, BYTE a, UINT32 b, UINT32 c, UINT32 d, UINT32 e, UINT32 f);
	static bool __cdecl SkillEnchantOperatorOperateSafe(SkillEnchantOperator *self, class CUser *user, int id, int level);
	static bool __cdecl SkillEnchantOperatorOperateUntrain(SkillEnchantOperator *self, class CUser *user, int id, int level);
	static bool __cdecl SkillEnchantOperatorOperateRouteChange(SkillEnchantOperator *self, class CUser *user, int id, int level);
	static bool __cdecl RequestExEnchantSkillInfo(CUserSocket *self, const BYTE *packet, BYTE opcode);
	static bool __cdecl RequestExEnchantSkillInfoDetail(CUserSocket *self, const BYTE *packet, BYTE opcode);
	static bool __cdecl RequestExEnchantSkillUntrain(CUserSocket *self, const BYTE *packet, BYTE opcode);
	static bool __cdecl CheckEnchantItems(CUser *user, UINT32 enchantType, int skillId, int skillLevel);
	static void __cdecl TakeEnchantItems(CUser *user, UINT32 enchantType, int skillId, int skillLevel);
	static INT64 __cdecl SkillEnchantOperatorCalculateEXP(SkillEnchantOperator *self, class CSkillEnchantInfo *info, int level);
	static int __cdecl SkillEnchantOperatorCalculateSP(SkillEnchantOperator *self, class CSkillEnchantInfo *info, int level);
};

