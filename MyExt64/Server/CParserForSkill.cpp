
#include <Server/CParserForSkill.h>
#include <Server/CLexerForSkill.h>
#include <Server/CSkillInfo.h>
#include <Common/Utils.h>
#include <Common/CLog.h>

void CParserForSkill::Init()
{
	WriteMemoryQWORD(0xD068E0, FnPtr(&CParserForSkill::yyaction_));
}

void CParserForSkill::yyaction_(int action)
{
	if (CLexerForSkill::substAction
		&& CLexerForSkill::substAction != CLexerForSkill::i_p_attack
		&& CLexerForSkill::substAction != CLexerForSkill::i_p_soul_attack
		&& CLexerForSkill::substAction != CLexerForSkill::i_energy_attack
		&& CLexerForSkill::substAction != CLexerForSkill::t_hp
		&& CLexerForSkill::substAction != CLexerForSkill::i_call_pc
		&& CLexerForSkill::substAction != CLexerForSkill::abnormal_visual_effect) {

		if (CLexerForSkill::substOwn) {
			action = CLexerForSkill::substAction;
			//CLog::Add(CLog::Blue, L"CParserForSkill::yyaction (subst) %d -> %s", action, this->yylexerptr->yytext);
			switch (action) {
			case CLexerForSkill::olympiad_use:
				skillInfo->ext.olympiadUse = bool(_wtoi(yylexerptr->yytext));
				//CLog::Add(CLog::Blue, L"olympiad_use -> %s", this->yylexerptr->yytext);
				break;
			}
		} else {
			reinterpret_cast<void(*)(CParserForSkill*, int)>(0x9B39D0)(this, CLexerForSkill::substAction);
		}
		CLexerForSkill::substAction = 0;
	} else {
		//CLog::Add(CLog::Blue, L"CParserForSkill::yyaction (orig) %d -> %s", action, this->yylexerptr->yytext);
		reinterpret_cast<void(*)(CParserForSkill*, int)>(0x9B39D0)(this, action);
	}
}

CompileTimeOffsetCheck(CParserForSkill, skillInfo, 0xF8);

