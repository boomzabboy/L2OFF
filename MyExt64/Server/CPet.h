
#pragma once

#include <Server/CSummon.h>

class CPet : public CSummon {
public:
	static void Init();
	static INT64 __cdecl ExpIncWrapper(CPet *self, const INT64 exp, const bool b);
	INT64 ExpInc(const INT64 exp, const bool b);
};