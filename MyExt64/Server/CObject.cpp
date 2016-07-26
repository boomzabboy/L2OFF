
#include <Server/CObject.h>

CObject* CObject::GetObject(const UINT32 objectId)
{
	return reinterpret_cast<CObject*(*)(UINT64, const UINT32)>(0x41A3A4)(0xF1B250, objectId);
}

