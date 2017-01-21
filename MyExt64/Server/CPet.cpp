
#include <Server/CPet.h>
#include <Server/CUser.h>
#include <Server/NpcServer.h>
#include <Common/Utils.h>

void CPet::Init()
{
	WriteMemoryQWORD(0xBCCC38, reinterpret_cast<UINT64>(OutOfSightWrapper));
	WriteMemoryQWORD(0xBCCD98, reinterpret_cast<UINT64>(ExpIncWrapper));
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

