
#include <Server/CLexerForSkill.h>
#include <Server/CParserForSkill.h>
#include <Server/CSkillInfo.h>
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
}

void CLexerForSkill::AddToken(const wchar_t *name, const Token action, const Token type, const bool own)
{
	Subst s;
	s.token = type;
	s.action = action;
	s.own = own;
	newTokens.insert(std::make_pair(name, s));
}

/*
#include <set>
static std::set<std::wstring> knownConstants;
*/

yl::yywint_t CLexerForSkill::yyaction_(int action)
{

	CSkillInfo *skillInfo = reinterpret_cast<CParserForSkill*>(yyparserptr)->skillInfo;
	if (skillInfo && skillInfo->skillId == 498 && skillInfo->level == 201) {
		CLog::Add(CLog::Blue, L"CLexerForSkill::yyaction %d %s", action, yytext);
	}

	//bool &returned(reinterpret_cast<bool&>(reinterpret_cast<char*>(this)[0x5A]));
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
				//CLog::Add(CLog::Blue, L"substAction == i_p_attack && action == 626 && yytext[0] == L';' && substActionState < 3 -> ++substActionState");
				++substActionState;
			} else if (substActionState == 3) {
				//CLog::Add(CLog::Blue, L"substAction == i_p_attack && action == 626 && yytext[0] == L';' && substActionState == 3 -> ++substActionState ; yytext[0] = L'}'");
				++substActionState;
				yytext[0] = L'}';
			} else {
				//CLog::Add(CLog::Blue, L"substAction == i_p_attack && action == 626 && yytext[0] == L';' && substActionState < 3 -> action = 629");
				action = 629;
			}
		} else if (action == 626 && yytext[0] == L'}') {
			if (substActionState == 5) {
				//CLog::Add(CLog::Blue, L"substAction == i_p_attack && action == 626 && yytext[0] == L'}' && substActionState > 3 -> action = 629 ; reset");
				action = 629;
			}/* else {
				CLog::Add(CLog::Blue, L"substAction == i_p_attack && action == 626 && yytext[0] == L'}' && substActionState <= 3 -> reset");
			}*/
			substActionState = 0;
			substAction = 0;
		} else if (action == 623 && substActionState == 4) {
			//CLog::Add(CLog::Blue, L"substAction == i_p_attack && action == 623 && substActionState > 3 -> action = 629");
			substActionState = 5;
			//CLog::Add(CLog::Blue, L"i_p_attack fourth param = %s", yytext); // TODO!
			action = 629;
		}/* else {
			CLog::Add(CLog::Blue, L"substAction == i_p_attack && action == %d && substActionState == %d", action, substActionState);
		}*/
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
			CLog::Add(CLog::Blue, L"i_p_soul_attack fourth param = %s", yytext); // TODO!
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
			//CLog::Add(CLog::Blue, L"i_energy_attack fifth param = %s", yytext); // TODO!
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
			//CLog::Add(CLog::Blue, L"t_hp third param = %s", yytext); // TODO!
			substActionState = 4;
			action = 629;
		}
	} else if (substAction == i_call_pc) {
		CLog::Add(CLog::Blue, L"substAction == i_call_pc && action == %d && substActionState == %d", action, substActionState);
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
			CLog::Add(CLog::Blue, L"i_call_pc second param = %s", yytext); // TODO!
			++substActionState;
			action = 629;
		} else if (action == 623 && substActionState == 2) {
			CLog::Add(CLog::Blue, L"i_call_pc third param = %s", yytext); // TODO!
			++substActionState;
			action = 629;
		}
	}

	yl::yywint_t token = reinterpret_cast<yl::yywint_t(*)(CLexerForSkill*, int)>(0x98FA34)(this, action);
	//CLog::Add(CLog::Blue, L"CLexerForSkill::yyaction %d -> %s (%d)", action, yytext, token);

	if (token == CONSTANT && action == 628
		&& substAction != abnormal_visual_effect
		&& substAction != i_p_attack
		&& substAction != i_p_soul_attack
		&& substAction != i_energy_attack
		&& substAction != i_call_pc
		&& substAction != t_hp) {

		substAction = 0;
		substActionState = 0;
		std::wstring tokenString = std::wstring(yytext, yyleng);
		std::map<std::wstring, Subst>::const_iterator inewTokens(newTokens.find(tokenString));
		if (inewTokens != newTokens.end()) {
			substAction = inewTokens->second.action;
			token = inewTokens->second.token;
			substOwn = inewTokens->second.own;
		} /*else {
			if (knownConstants.insert(tokenString).second) {
				CLog::Add(CLog::Blue, L"Constant or unknown token? >%s<", tokenString.c_str());
			}
		}*/
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
	}

	return token;
}

