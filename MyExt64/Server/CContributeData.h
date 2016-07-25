
#pragma once

#include <Server/CObject.h>
#include <windows.h>

class CContributeData : public CObject {
public:
	CObject* GetLooter();
	bool PickableIn5Sec(class CCreature *creature);

	/* 0x0000 */ unsigned char padding0x0000[0x0078 - 0x0000];
	/* 0x0078 */ UINT32 looterObjectId;
};

