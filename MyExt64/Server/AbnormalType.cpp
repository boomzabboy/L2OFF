
#include <Server/AbnormalType.h>
#include <Common/Utils.h>
#include <Common/CLog.h>

AbnormalType AbnormalType::abnormalTypes[1024];
size_t AbnormalType::abnormalTypesSize = 0x150;

AbnormalType::AbnormalType(const int id, const wchar_t *name) : id(id), name(name)
{
}

void AbnormalType::Init()
{
	Copy();
	//Add(L"attack_speed_up_bow");
	Setup();
}

void AbnormalType::Add(const wchar_t *name)
{
	const int id = abnormalTypesSize++;
	abnormalTypes[id].id = id;
	abnormalTypes[id].name = name;
}

void AbnormalType::Copy()
{
	memcpy(reinterpret_cast<void*>(abnormalTypes), reinterpret_cast<void*>(0xE64CF0), sizeof(AbnormalType) * abnormalTypesSize);
}

void AbnormalType::Setup()
{
	WriteAddress(0x9B3772, reinterpret_cast<UINT32>(abnormalTypes) + 8);
	WriteAddress(0x9B37D6, reinterpret_cast<UINT32>(abnormalTypes + abnormalTypesSize) + 8);
}

