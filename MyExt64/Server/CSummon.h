
#pragma once

#include <Server/CCreature.h>

class CSummon : public CCreature {
public:
	static void Init();

	bool IsEnemyTo(CCreature *creature);
	void OutOfSight(CObject *object, bool b);
	class CUser* GetUserOrMaster();

	static bool IsEnemyToWrapper(CSummon *self, CCreature *creature);
	static void __cdecl OutOfSightWrapper(CSummon *self, CObject *object, bool b);
};

