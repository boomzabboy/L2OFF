
#pragma once

class OlympiadFixes {
public:
	static void Init();

	static void __cdecl PledgeSkillLock(unsigned long &a, int b, class CUser *user, bool d, bool e, bool &f);
	static void __cdecl SetOlympiadTermWrapper(OlympiadFixes *self, bool b1, bool b2, int i1, int i2, int i3, int i4, int i5, int i6, int i7, bool b3);

	void SetOlympiadTerm(bool b1, bool b2, int i1, int i2, int i3, int i4, int i5, int i6, int i7, bool b3);
};

