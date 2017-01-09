
#include <NPCd/Type.h>

Type::Type()
{
	reinterpret_cast<void(*)(Type*)>(0x576180)(this);
}

Type::~Type()
{
	name.clear();
	reinterpret_cast<void(*)(Type*, bool)>(0x5762B4)(this, false);
}

