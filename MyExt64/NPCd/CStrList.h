
#pragma once

#include <NPCd/CIntList.h>

class CStrList : public CIntList {
public:
	CStrList();
	virtual void RegisterFunctions(void *registry);
	virtual void RegisterVariables(void *registry);
};

