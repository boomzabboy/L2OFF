
#pragma once

#include "CCreature.h"

class CSummon : public CCreature {
public:
	static void Init();

	bool IsEnemyTo(CCreature *creature);
	class CUser* GetUserOrMaster();

	static bool IsEnemyToWrapper(CSummon *self, CCreature *creature);
};

