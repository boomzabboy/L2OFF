
#include <Server/CParserForSkill.h>
#include <Server/CLexerForSkill.h>
#include <Server/CSkillInfo.h>
#include <Server/CSkillOperateCondition_op_skill_acquire.h>
#include <Common/Utils.h>
#include <Common/CLog.h>

void CParserForSkill::Init()
{
	WriteMemoryQWORD(0xD068E0, FnPtr(&CParserForSkill::yyaction_));
	WriteMemoryBYTES(0x9B4E02, "\x48\x8B\x96\xF8\x00\x00\x00", 7);
	WriteInstructionCallJmpEax(0x9B4E0D, FnPtr(CParserForSkill::AbnormalVisualEffectHelper));
}

void CParserForSkill::yyaction_(int action)
{
	if (CLexerForSkill::substAction
		&& CLexerForSkill::substAction != CLexerForSkill::i_p_attack
		&& CLexerForSkill::substAction != CLexerForSkill::i_p_soul_attack
		&& CLexerForSkill::substAction != CLexerForSkill::i_energy_attack
		&& CLexerForSkill::substAction != CLexerForSkill::t_hp
		&& CLexerForSkill::substAction != CLexerForSkill::op_check_abnormal
		&& CLexerForSkill::substAction != CLexerForSkill::i_call_pc
		&& CLexerForSkill::substAction != CLexerForSkill::abnormal_visual_effect) {

		if (CLexerForSkill::substOwn) {
			action = CLexerForSkill::substAction;
			switch (action) {
			case CLexerForSkill::olympiad_use:
				skillInfo->ext.olympiadUse = bool(_wtoi(yylexerptr->yytext));
				break;
			case CLexerForSkill::op_skill_acquire:
				int skillId = GetYYAttr<int>(-1);
				int learned = GetYYAttr<int>(0);
				skillInfo->PushCondition(new CSkillOperateCondition_op_skill_acquire(skillId, learned), operateConditionTarget);
				break;
			}
		} else {
			reinterpret_cast<void(*)(CParserForSkill*, int)>(0x9B39D0)(this, CLexerForSkill::substAction);
		}
		CLexerForSkill::substAction = 0;
	} else {
		reinterpret_cast<void(*)(CParserForSkill*, int)>(0x9B39D0)(this, action);
	}

	/*if (action == 53) {
		CLog::Add(CLog::Blue, L"target_type = %s -> %d", yylexerptr->yytext, skillInfo->targetType);
	}*/
}

UINT32 CParserForSkill::AbnormalVisualEffectHelper(const wchar_t *effect, CSkillInfo *skillInfo)
{
	if (!wcscmp(effect, reinterpret_cast<wchar_t*>(0xD07620))) {
		skillInfo->abnormalVisualEffect2 = 4;
	} else if (!wcscmp(effect, L"ave_stigma_of_silen")) {
		skillInfo->abnormalVisualEffect2 = 0x100;
	} else {
		return 0x9B4E2C;
	}
	return 0x9BF99A;
}

CompileTimeOffsetCheck(CParserForSkill, skillInfo, 0xF8);
CompileTimeOffsetCheck(CParserForSkill, operateConditionTarget, 0x104);

