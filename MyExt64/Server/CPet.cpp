
#include <Server/CPet.h>
#include <Server/CUser.h>
#include <Server/NpcServer.h>
#include <Server/CItem.h>
#include <Common/Utils.h>
#include <Common/Config.h>

void CPet::Init()
{
	WriteMemoryQWORD(0xBCCC38, reinterpret_cast<UINT64>(OutOfSightWrapper));
	WriteMemoryQWORD(0xBCCD98, reinterpret_cast<UINT64>(ExpIncWrapper));
	if (Config::Instance()->custom->dontDropPetItems) {
		NOPMemory(0x7B6079, 2);
	}
	WriteInstructionCall(0x7B5F99, reinterpret_cast<UINT32>(GiveAllItemToMasterHelper));
	WriteMemoryBYTES(0x7B5F9E, "\x85\xC0\x74\x60", 4); // test eax, eax; je 0x7B6002
	WriteInstructionCall(0x5D33CC + 0x373, reinterpret_cast<UINT32>(GiveAllItemToMasterWrapper));
	WriteInstructionCall(0x8FCF50 + 0x184, reinterpret_cast<UINT32>(GiveAllItemToMasterWrapper));
	WriteInstructionCall(0x8FDB18 + 0x1A8, reinterpret_cast<UINT32>(GiveAllItemToMasterWrapper));
	if (Config::Instance()->server->epiloguePetInventoryBehaviour) {
		NOPMemory(0x8FD0D4, 5);
	}
}

INT64 __cdecl CPet::ExpIncWrapper(CPet *self, const INT64 exp, const bool b)
{
	return self->ExpInc(exp, b);
}

INT64 CPet::ExpInc(const INT64 exp, const bool b)
{
	GUARDED;

	bool isExpOff = false;
	CUser *user = GetUserOrMaster();
	if (user && user->ext.isPetExpOff) {
		isExpOff = true;
	}

	return reinterpret_cast<INT64(*)(CPet*, const INT64, const bool)>(0x7ADC4C)(
        this, (exp < 0 || !isExpOff) ? exp : 0, b);
}

void CPet::GiveAllItemToMasterWrapper(CPet *self, bool b)
{
	self->GiveAllItemToMaster(b);
}

void CPet::GiveAllItemToMaster(bool b)
{
	CUser *user = GetUserOrMaster();
	if (user) {
		user->TradeCancel();
	}
	reinterpret_cast<void(*)(CPet*, bool)>(0x7B5E58)(this, b);
}

UINT32 CPet::GiveAllItemToMasterHelper(CItem *item)
{
	switch (Config::Instance()->custom->keepFoodInPetInventory ? item->itemId : 0) {
	case 2515: // wolf food
	case 4038: // food for hatchling
	case 5168: // food for strider
	case 5169: // deluxe food for strider
	case 7582: // baby spice
	case 9668: // great wolf food
	case 10425: // improved baby pet food
		return 0;
	default:
		return (*reinterpret_cast<UINT32(***)(CItem*)>(item))[0x8C](item);
	}
}

