
#pragma once

#include <Server/CCreature.h>

class CNPC : public CCreature {
public:
	static void Init();
	static bool __cdecl DieWrapper(CNPC *self, CCreature *killer);

	bool Die(CCreature *killer);
};

