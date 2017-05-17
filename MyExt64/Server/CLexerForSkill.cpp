
#include <Server/CLexerForSkill.h>
#include <Common/Utils.h>
#include <Common/CLog.h>

yl::yywint_t CLexerForSkill::substAction = 0;
std::map<std::wstring, CLexerForSkill::Token> CLexerForSkill::newTokens;

void CLexerForSkill::Init()
{
	WriteMemoryQWORD(0xCBFA20, FnPtr(&CLexerForSkill::yyaction_));

#define AddToken(name) AddToken(L#name, name);

	AddToken(olympiad_use);

#undef AddToken
}

void CLexerForSkill::AddToken(const wchar_t *name, Token token)
{
	newTokens.insert(std::make_pair(name, token));
}

#include <set>
static std::set<std::wstring> knownConstants;

yl::yywint_t CLexerForSkill::yyaction_(int action)
{
	bool &returned(reinterpret_cast<bool&>(reinterpret_cast<char*>(this)[0x5A]));
	yl::yywint_t token = reinterpret_cast<yl::yywint_t(*)(CLexerForSkill*, int)>(0x98FA34)(this, action);
	if (token == CONSTANT && action == 628) {
		std::wstring tokenString = std::wstring(yytext, yyleng);
		std::map<std::wstring, Token>::const_iterator inewTokens(newTokens.find(tokenString));
		if (inewTokens != newTokens.end()) {
			substAction = olympiad_use;
			token = is_magic;
		} else {
			if (knownConstants.insert(tokenString).second) {
				CLog::Add(CLog::Blue, L"Constant or unknown token? >%s<", tokenString.c_str());
			}
		}
	}

	return token;
}

