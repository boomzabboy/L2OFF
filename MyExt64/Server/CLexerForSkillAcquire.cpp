
#include <Server/CLexerForSkillAcquire.h>
#include <Server/CParserForSkillAcquire.h>
#include <Common/Utils.h>
#include <Common/CLog.h>

yl::yywint_t CLexerForSkillAcquire::substAction = 0;
std::map<std::wstring, CLexerForSkillAcquire::Subst> CLexerForSkillAcquire::newTokens;

void CLexerForSkillAcquire::Init()
{
	WriteMemoryQWORD(0xD2FA70, FnPtr(&CLexerForSkillAcquire::yyaction_));

	AddToken(L"bishop_sharing_begin", bishop_sharing_begin, collect_begin);
	AddToken(L"bishop_sharing_end", bishop_sharing_end, collect_end);
	AddToken(L"elder_sharing_begin", elder_sharing_begin, collect_begin);
	AddToken(L"elder_sharing_end", elder_sharing_end, collect_end);
	AddToken(L"silen_elder_sharing_begin", silen_elder_sharing_begin, collect_begin);
	AddToken(L"silen_elder_sharing_end", silen_elder_sharing_end, collect_end);
}

void CLexerForSkillAcquire::AddToken(const wchar_t *name, const Token action, const Token type)
{
	Subst s;
	s.token = type;
	s.action = action;
	newTokens.insert(std::make_pair(name, s));
}

yl::yywint_t CLexerForSkillAcquire::yyaction_(int action)
{
	yl::yywint_t token = reinterpret_cast<yl::yywint_t(*)(CLexerForSkillAcquire*, int)>(0x9CDEAC)(this, action);

	if (token == CONSTANT && action == 311) {
		substAction = 0;
		std::wstring tokenString = std::wstring(yytext, yyleng);
		std::map<std::wstring, Subst>::const_iterator inewTokens(newTokens.find(tokenString));
		if (inewTokens != newTokens.end()) {
			substAction = inewTokens->second.action;
			token = inewTokens->second.token;
		}
	}

	return token;
}

