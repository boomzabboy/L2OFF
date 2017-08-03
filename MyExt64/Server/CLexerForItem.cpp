
#include <Server/CLexerForItem.h>
#include <Server/CParserForItem.h>
#include <Common/Utils.h>
#include <Common/CLog.h>

yl::yywint_t CLexerForItem::substAction = 0;
bool CLexerForItem::substOwn = false;
int CLexerForItem::substActionState = 0;
std::map<std::wstring, CLexerForItem::Subst> CLexerForItem::newTokens;

void CLexerForItem::Init()
{
	WriteMemoryQWORD(0xCAC240, FnPtr(&CLexerForItem::yyaction_));

	AddToken(L"is_private_store", is_private_store, is_drop, true);
	AddToken(L"is_olympiad_can_use", is_olympiad_can_use, is_drop, true);
}

void CLexerForItem::AddToken(const wchar_t *name, const Token action, const Token type, const bool own)
{
	Subst s;
	s.token = type;
	s.action = action;
	s.own = own;
	newTokens.insert(std::make_pair(name, s));
}

yl::yywint_t CLexerForItem::yyaction_(int action)
{
	yl::yywint_t token = reinterpret_cast<yl::yywint_t(*)(CLexerForItem*, int)>(0x98C0D0)(this, action);

	if (token == CONSTANT && action == 209) {
		substAction = 0;
		substActionState = 0;
		std::wstring tokenString = std::wstring(yytext, yyleng);
		std::map<std::wstring, Subst>::const_iterator inewTokens(newTokens.find(tokenString));
		if (inewTokens != newTokens.end()) {
			substAction = inewTokens->second.action;
			token = inewTokens->second.token;
			substOwn = inewTokens->second.own;
		}
	}

	return token;
}

