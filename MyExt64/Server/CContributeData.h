
#pragma once

#include <Server/CObject.h>
#include <map>

class CContributeData : public CObject {
public:
	bool PickableIn5Sec(class CCreature *creature);
	double GetContributeInfos(std::map<UINT32, double> &infos);

	/* 0x0000 */ unsigned char padding0x0000[0x0060 - 0x0000];
	/* 0x0060 */ std::map<UINT32, double> data;
	/* 0x0078 */ UINT32 looterObjectId;
};

