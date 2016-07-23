
#include <Server/CPet.h>
#include <Server/CUser.h>
#include <Server/NpcServer.h>
#include <Common/Utils.h>

void CPet::Init()
{
	WriteMemoryQWORD(0xBCCC38, reinterpret_cast<UINT64>(OutOfSightWrapper));
}

