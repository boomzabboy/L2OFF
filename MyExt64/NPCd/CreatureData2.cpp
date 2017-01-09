
#include <NPCd/CreatureData2.h>
#include <Common/Utils.h>

CreatureData2::CreatureData2()
{
}

void CreatureData2::RegisterFunctions(void *registry)
{
}

void CreatureData2::RegisterVariables(void *registry)
{
	RegisterVariable(registry, L"absolute_defence", offsetof(CreatureData2, absolute_defence));
	RegisterVariable(registry, L"no_attack_damage", offsetof(CreatureData2, no_attack_damage));
	RegisterVariable(registry, L"quest_inv_items", offsetof(CreatureData2, quest_inv_items));
}

void CreatureData2::RegisterVariable(void *registry, const wchar_t *name, size_t offset)
{
	reinterpret_cast<void(*)(void*, const wchar_t*, size_t, char*)>(0x423160)(
		registry, name, offset, reinterpret_cast<char*>(this) + offset);
}

