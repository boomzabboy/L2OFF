
#pragma once

class CIntList {
public:
	CIntList()
	{
		reinterpret_cast<CIntList*(*)(CIntList*)>(0x4BF028)(this);
	}

	~CIntList()
	{
		if (*reinterpret_cast<void**>(&padding0x0008[0x10])) {
			reinterpret_cast<void(*)(void*, void*, int)>(0x4835DC)(
				reinterpret_cast<void*>(0x1C1F040),
				*reinterpret_cast<void**>(&padding0x0008[0x10]),
				1);
		}
	}

	virtual void RegisterFunctions(void *registry)
	{
	}

	virtual void RegisterVariables(void *registry)
	{
		reinterpret_cast<void(*)(CIntList*, void*)>(0x4E48DC)(this, registry);
	}

	unsigned char padding0x0008[0x40];
};

