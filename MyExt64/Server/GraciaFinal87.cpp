
#include <Server/GraciaFinal87.h>
#include <Common/Utils.h>
#include <Common/CLog.h>

void GraciaFinal87::Init()
{
    InitPackets();
}

void GraciaFinal87::InitPackets()
{
	WriteInstructionCall(0x77F552, reinterpret_cast<UINT32>(AssemblePartyMember));
}

int __cdecl GraciaFinal87::AssemblePartyMember(char *buffer, int maxSize, const char *format, UINT32 a, const wchar_t *b, UINT32 c, UINT32 d, UINT32 e, UINT32 f, UINT32 g, UINT32 h, UINT32 i, UINT32 j, UINT32 k, UINT32 l)
{
	//                                abcdefghij0l00
	return Assemble(buffer, maxSize, "dSdddddddddddd", a, b, c, d, e, f, g, h, i, j, 0, l, 0, 0);
}

