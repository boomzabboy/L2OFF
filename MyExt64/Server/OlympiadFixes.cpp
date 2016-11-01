
#include <Server/OlympiadFixes.h>
#include <Server/CUser.h>
#include <Common/Utils.h>
#include <Common/Config.h>
#include <Common/CLog.h>
#include <time.h>

void OlympiadFixes::Init()
{
	WriteInstructionCall(0x7D96EB, reinterpret_cast<UINT32>(PledgeSkillLock));
	WriteInstructionCall(0x7D9737, reinterpret_cast<UINT32>(PledgeSkillLock));
	WriteInstructionCall(0x6067B8, reinterpret_cast<UINT32>(SetOlympiadTermWrapper));
}

void __cdecl OlympiadFixes::PledgeSkillLock(unsigned long &a, int b, CUser *user, bool d, bool e, bool &f)
{ GUARDED

	if (!user) {
		return;
	}
	if (user->IsInOlympiad()) {
		b = -1;
	}
	reinterpret_cast<void(*)(unsigned long&, int, CUser*, bool, bool, bool&)>(0x7CDB90)(a, b, user, d, e, f);
}

void __cdecl OlympiadFixes::SetOlympiadTermWrapper(OlympiadFixes *self, bool b1, bool b2, int i1, int i2, int i3, int i4, int i5, int i6, int i7, bool b3)
{
	self->SetOlympiadTerm(b1, b2, i1, i2, i3, i4, i5, i6, i7, b3);
}

void OlympiadFixes::SetOlympiadTerm(bool b1, bool b2, int i1, int i2, int i3, int i4, int i5, int i6, int i7, bool b3)
{
	if (Config::Instance()->fixes->forceMonthlyOlympiad) {
		CLog::Debug(CLog::Blue, L"Force monthly olympiad:");
		CLog::Debug(CLog::Blue, L"ORG Olympiad start = %d", *reinterpret_cast<UINT32*>(0xE3DB8A4));
		CLog::Debug(CLog::Blue, L"ORG SetOlympiadTerm(monthly = %s, ? = %s, period = %d, startSec = %d, bonus1 = %d, bonus2 = %d, bonus3 = %d, bonus4 = %d, nominate = %d, ? = %s)",
			b1 ? L"true" : L"false", b2 ? L"true" : L"false", i1, i2, i3, i4, i5, i6, i7, b3 ? L"true" : L"false");

		const time_t now = time(0);
		struct tm t;
		localtime_s(&t, &now);
		t.tm_mday = 1;
		t.tm_hour = 0;
		t.tm_min = 0;
		t.tm_sec = 0;
		const time_t olympiadStartTime = mktime(&t);
		if (++t.tm_mon > 11) {
			t.tm_mon = 0;
			++t.tm_year;
		}
		const time_t nextMonthStart = mktime(&t);

		*reinterpret_cast<UINT32*>(0xE3DB8A4) = olympiadStartTime;
		b1 = true;
		i7 = nextMonthStart - olympiadStartTime;

		CLog::Debug(CLog::Blue, L"NEW Olympiad start = %d", *reinterpret_cast<UINT32*>(0xE3DB8A4));
		CLog::Debug(CLog::Blue, L"NEW SetOlympiadTerm(monthly = %s, ? = %s, period = %d, startSec = %d, bonus1 = %d, bonus2 = %d, bonus3 = %d, bonus4 = %d, nominate = %d, ? = %s)",
			b1 ? L"true" : L"false", b2 ? L"true" : L"false", i1, i2, i3, i4, i5, i6, i7, b3 ? L"true" : L"false");
	}
	reinterpret_cast<void(*)(OlympiadFixes*, bool, bool, int, int, int, int, int, int, int, bool)>(0x76B2C4)(
		this, b1, b2, i1, i2, i3, i4, i5, i6, i7, b3);
}
