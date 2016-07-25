
#include <Server/CItem.h>
#include <Server/CContributeData.h>

CContributeData* CItem::GetContributeData()
{
	return reinterpret_cast<CContributeData*(*)(UINT32*)>(0x86E3D0)(&contributeDataObjectId);
}

