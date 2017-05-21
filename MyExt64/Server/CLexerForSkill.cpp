
#include <Server/CLexerForSkill.h>
#include <Server/CParserForSkill.h>
#include <Server/CSkillInfo.h>
#include <Server/CSkillOperateCondition_op_check_abnormal.h>
#include <Server/CSkillEffect_t_hp.h>
#include <Common/Utils.h>
#include <Common/CLog.h>

yl::yywint_t CLexerForSkill::substAction = 0;
bool CLexerForSkill::substOwn = false;
int CLexerForSkill::substActionState = 0;
std::map<std::wstring, CLexerForSkill::Subst> CLexerForSkill::newTokens;

void CLexerForSkill::Init()
{
	WriteMemoryQWORD(0xCBFA20, FnPtr(&CLexerForSkill::yyaction_));

	AddToken(L"olympiad_use", olympiad_use, is_magic, true);
	AddToken(L"p_resist_abnormal_by_type", p_resist_abnormal_by_category, p_resist_abnormal_by_category, false);
	AddToken(L"op_skill_acquire", op_skill_acquire, op_encumbered, true);
}

void CLexerForSkill::AddToken(const wchar_t *name, const Token action, const Token type, const bool own)
{
	Subst s;
	s.token = type;
	s.action = action;
	s.own = own;
	newTokens.insert(std::make_pair(name, s));
}

yl::yywint_t CLexerForSkill::yyaction_(int action)
{
	if (substAction == abnormal_visual_effect) {
		if (action == 626) {
			if (substActionState == 0) {
				substActionState = 1;
				action = 629;
			} else if (substActionState == 2) {
				substActionState = 0;
				substAction = 0;
				action = 629;
			}
		} else if (action == 628) {
			if (substActionState == 0) {
				substActionState = 0;
				substAction = 0;
			} else if (substActionState == 1) {
				substActionState = 2;
			}
		}
	} else if (substAction == i_p_attack) {
		if (action == 626 && yytext[0] == L';') {
			if (substActionState < 3) {
				++substActionState;
			} else if (substActionState == 3) {
				++substActionState;
				yytext[0] = L'}';
			} else {
				action = 629;
			}
		} else if (action == 626 && yytext[0] == L'}') {
			if (substActionState == 5) {
				action = 629;
			}
			substActionState = 0;
			substAction = 0;
		} else if (action == 623 && substActionState == 4) {
			substActionState = 5;
			// i_p_attack fourth parameter is always zero in Freya (not in Glory Days)
			// I think we may safely ignore it until we want to go beyond Freya
			action = 629;
		}
	} else if (substAction == i_p_soul_attack) {
		if (action == 626 && yytext[0] == L';') {
			if (substActionState < 3) {
				++substActionState;
			} else if (substActionState == 3) {
				++substActionState;
				yytext[0] = L'}';
			} else {
				action = 629;
			}
		} else if (action == 626 && yytext[0] == L'}') {
			if (substActionState == 5) {
				action = 629;
			}
			substActionState = 0;
			substAction = 0;
		} else if (action == 623 && substActionState == 4) {
			substActionState = 5;
			// i_p_soul_attack fourth parameter is always zero in both Freya and Glory Days
			// so I think we may safely ignore it...
			action = 629;
		}
	} else if (substAction == i_energy_attack) {
		if (action == 626 && yytext[0] == L';') {
			if (substActionState < 4) {
				++substActionState;
			} else if (substActionState == 4) {
				++substActionState;
				yytext[0] = L'}';
			} else {
				action = 629;
			}
		} else if (action == 626 && yytext[0] == L'}') {
			if (substActionState == 6) {
				action = 629;
			}
			substActionState = 0;
			substAction = 0;
		} else if (action == 623 && substActionState == 5) {
			substActionState = 6;
			// i_energy_attack fifth parameter is always zero in both Freya and Glory Days
			// so I think we may safely ignore it...
			action = 629;
		}
	} else if (substAction == t_hp) {
		if (action == 626 && yytext[0] == L';') {
			if (substActionState < 2) {
				++substActionState;
			} else if (substActionState == 2) {
				++substActionState;
				yytext[0] = L'}';
			} else {
				action = 629;
			}
		} else if (action == 626 && yytext[0] == L'}') {
			if (substActionState == 4) {
				action = 629;
			}
			substActionState = 0;
			substAction = 0;
		} else if ((action == 465 || action == 466 || action == 467) && substActionState == 3) {
			std::wstring tokenString = std::wstring(yytext, yyleng);
			if (tokenString == L"per") {
				substActionState = 4;
				action = 629;
				CSkillEffect_t_hp::last->per = true;
			} else if (tokenString == L"diff") {
				substActionState = 4;
				action = 629;
			}
		}
	} else if (substAction == i_call_pc) {
		if (action == 626 && yytext[0] == L';') {
			if (substActionState == 0) {
				++substActionState;
				yytext[0] = L'}';
			} else {
				action = 629;
			}
		} else if (action == 626 && yytext[0] == L'}') {
			if (substActionState == 3) {
				action = 629;
			}
			substActionState = 0;
			substAction = 0;
		} else if (action == 627 && substActionState == 1) {
			// name of item that i_call_pc should take - in Freya it's always [crystal_of_summon]
			// so we will ignore it until we want to go beyond Freya
			++substActionState;
			action = 629;
		} else if (action == 623 && substActionState == 2) {
			// count of items that i_call_pc should take - in Freya it's always 1
			// so we will ignore it until we want to go beyond Freya
			++substActionState;
			action = 629;
		}
	} else if (substAction == op_check_abnormal) {
		if (action == 626 && yytext[0] == L';') {
			if (substActionState < 2) {
				++substActionState;
			} else if (substActionState == 2) {
				++substActionState;
				yytext[0] = L'}';
			} else {
				action = 629;
			}
		} else if (action == 626 && yytext[0] == L'}') {
			if (substActionState == 4) {
				action = 629;
			}
			substActionState = 0;
			substAction = 0;
		} else if (action == 623 && substActionState == 3) {
			if (!_wtoi(yytext)) {
				CSkillOperateCondition_op_check_abnormal::last->invert = true;
			}
			substActionState = 4;
			action = 629;
		}
	}

	yl::yywint_t token = reinterpret_cast<yl::yywint_t(*)(CLexerForSkill*, int)>(0x98FA34)(this, action);

	if (token == CONSTANT && action == 628
		&& substAction != abnormal_visual_effect
		&& substAction != i_p_attack
		&& substAction != i_p_soul_attack
		&& substAction != i_energy_attack
		&& substAction != i_call_pc
		&& substAction != t_hp
		&& substAction != op_check_abnormal) {

		substAction = 0;
		substActionState = 0;
		std::wstring tokenString = std::wstring(yytext, yyleng);
		std::map<std::wstring, Subst>::const_iterator inewTokens(newTokens.find(tokenString));
		if (inewTokens != newTokens.end()) {
			substAction = inewTokens->second.action;
			token = inewTokens->second.token;
			substOwn = inewTokens->second.own;
		}
	} else if (token == i_p_attack && action == 170) {
		substAction = token;
	} else if (token == i_p_soul_attack && action == 171){ 
		substAction = token;
	} else if (token == i_energy_attack && action == 202) {
		substAction = token;
	} else if (token == t_hp && action == 296) {
		substAction = token;
	} else if (token == i_call_pc && action == 259) {
		substAction = token;
	} else if (token == abnormal_visual_effect && action == 63) {
		substAction = token;
	} else if (token == op_check_abnormal && action == 84) {
		substAction = token;
	}

	return token;
}

