
#include "COlympiadDefaultSetting.h"
#include "Utils.h"

const double COlympiadDefaultSetting::Three = 3.0;

void COlympiadDefaultSetting::Init()
{
	WriteInstructionCall(0x76D90F, reinterpret_cast<UINT32>(GetTransferingPointWrapper));
	WriteInstructionCall(0x76DFB9, reinterpret_cast<UINT32>(GetPenaltyPointWrapper));
	WriteInstructionCall(0x76DFDD, reinterpret_cast<UINT32>(GetPenaltyPointWrapper));
	WriteInstructionCall(0x76E451, reinterpret_cast<UINT32>(GetPenaltyPointWrapper));
	WriteAddress(0x768FAC, reinterpret_cast<UINT32>(&Three));
}

int COlympiadDefaultSetting::GetTransferingPointWrapper(COlympiadDefaultSetting *self, int a, int b, int c)
{
	return self->GetTransferingPoint(a, b, c);
}

int COlympiadDefaultSetting::GetTransferingPoint(int a, int b, int c)
{
	int result = reinterpret_cast<int(*)(COlympiadDefaultSetting*, int, int, int)>(0x768E48)(this, a, b, c);
	return result < 10 ? result : 10;
}

int COlympiadDefaultSetting::GetPenaltyPointWrapper(COlympiadDefaultSetting *self, int a, int b)
{
	return self->GetPenaltyPoint(a, b);
}

int COlympiadDefaultSetting::GetPenaltyPoint(int a, int b)
{
	int result = reinterpret_cast<int(*)(COlympiadDefaultSetting*, int, int)>(0x768F78)(this, a, b);
	return result < 10 ? result : 10;
}

