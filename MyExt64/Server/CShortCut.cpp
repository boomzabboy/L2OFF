
#include <Server/CShortCut.h>

void CShortCut::SendShortCutInfo()
{
	reinterpret_cast<void(*)(CShortCut*)>(0x816D1C)(this);
}

