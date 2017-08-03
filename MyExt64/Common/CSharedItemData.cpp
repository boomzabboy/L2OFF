
#include "CSharedItemData.h"

void CSharedItemData::InitServer()
{
	WriteMemoryDWORD(0x812E13 + 3, sizeof(CSharedItemData));
	WriteMemoryDWORD(0x812E60 + 3, sizeof(CSharedItemData));
	WriteMemoryDWORD(0x69A5AB + 3, sizeof(CSharedItemData));
	WriteMemoryDWORD(0x69D707 + 3, sizeof(CSharedItemData));
	WriteMemoryDWORD(0x812AAD + 3, sizeof(CSharedItemData));
}

void CSharedItemData::InitNpc()
{
	WriteMemoryDWORD(0x591B57 + 3, sizeof(CSharedItemData));
	WriteMemoryDWORD(0x5923D5 + 3, sizeof(CSharedItemData));
}

