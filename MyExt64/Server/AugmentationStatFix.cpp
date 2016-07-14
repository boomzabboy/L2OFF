
#include <Server/AugmentationStatFix.h>
#include <Common/Utils.h>

void AugmentationStatFix::Init()
{
	WriteInstructionCall(0x95267D, reinterpret_cast<UINT32>(Fix));
}

BYTE* __cdecl AugmentationStatFix::Fix(BYTE *a, BYTE *b, int c, int d, int e, int f, int g, BYTE h)
{
	unsigned char *ret = reinterpret_cast<BYTE*(*)(BYTE*, BYTE*, int, int, int, int, int, BYTE)>(
		0x6A9600)(a, b, c, d, e, f, g, h);

	for (size_t i(0) ; i < 6 ; ++i) {
		if (ret[i] > 1) {
			ret[i] = 1;
		}
	}

	return ret;
}

