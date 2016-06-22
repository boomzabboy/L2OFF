
#include "SkillEnchantOperator.h"
#include "CSkillEnchantInfo.h"
#include "Utils.h"
#include "MyExt64.h"
#include "CUser.h"
#include "CUserSocket.h"

SkillEnchantOperatorGetOperator_t SkillEnchantOperator::OriginalGetOperator = reinterpret_cast<SkillEnchantOperatorGetOperator_t>(0x44BD0C);

void SkillEnchantOperator::Init()
{
	WriteInstructionCall(0x75374C+0xC3, reinterpret_cast<UINT32>(FixedGetOperator));
	WriteInstructionCall(0x7538C4+0xB5, reinterpret_cast<UINT32>(FixedGetOperator));
	WriteInstructionCall(0x7539CC+0xCB, reinterpret_cast<UINT32>(FixedGetOperator));
	WriteInstructionCall(0x91A5EC+0xDC, reinterpret_cast<UINT32>(FixedGetOperator));
	WriteInstructionCall(0x91A734+0xDC, reinterpret_cast<UINT32>(FixedGetOperator));
	WriteInstructionCall(0x91A87C+0xB8, reinterpret_cast<UINT32>(FixedGetOperator));
	WriteInstructionCall(0x91A984+0xB8, reinterpret_cast<UINT32>(FixedGetOperator));
	WriteInstructionCall(0x91AA8C+0xB8, reinterpret_cast<UINT32>(FixedGetOperator));
	WriteInstructionCall(0x91AB94+0xB8, reinterpret_cast<UINT32>(FixedGetOperator));
}

SkillEnchantOperator* __cdecl SkillEnchantOperator::FixedGetOperator(void *self, UINT32 &type)
{
	UINT32 type_ = type > 3 ? 0 : type;
	return OriginalGetOperator(self, type_);
}

SkillEnchantOperator* __cdecl SkillEnchantOperator::GetOperator(UINT32 type)
{
	typedef void* (__cdecl *t1)();
	t1 f1 = reinterpret_cast<t1>(0x472C08);
	return FixedGetOperator(f1(), type);
}

int SkillEnchantOperator::CalculateProb(CSkillEnchantInfo *info, int level)
{
	typedef int (__thiscall *t)(SkillEnchantOperator*, CSkillEnchantInfo*, int);
	t f = reinterpret_cast<t>(
		*reinterpret_cast<void**>(
			reinterpret_cast<unsigned char*>(vtable) + 0x38));
	return f(this, info, level);
}

