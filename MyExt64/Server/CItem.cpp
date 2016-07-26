
#include <Server/CItem.h>
#include <Server/CContributeData.h>
#include <Common/Utils.h>

CContributeData* CItem::GetContributeData()
{
	return reinterpret_cast<CContributeData*(*)(UINT32*)>(0x86E3D0)(&contributeDataObjectId);
}

CompileTimeOffsetCheck(CItem, worldInfo, 0x0048);
CompileTimeOffsetCheck(CItem, contributeDataObjectId, 0x00B8);

