
#include <Server/CParserForSkill.h>
#include <Server/CLexerForSkill.h>
#include <Common/Utils.h>
#include <Common/CLog.h>

void CParserForSkill::Init()
{
	WriteMemoryQWORD(0xD068E0, FnPtr(&CParserForSkill::yyaction_));
}

void CParserForSkill::yyaction_(int action)
{
	if (CLexerForSkill::substAction) {
		action = CLexerForSkill::substAction;
		CLog::Add(CLog::Blue, L"CParserForSkill::yyaction %d -> %s", action, this->yylexerptr->yytext);
		switch (action) {
		case CLexerForSkill::olympiad_use:
			//CLog::Add(CLog::Blue, L"olympiad_use -> %s", this->yylexerptr->yytext);
			break;
		}
	} else {
		//CLog::Add(CLog::Blue, L"CParserForSkill::yyaction %d -> %s", action, this->yylexerptr->yytext);
		reinterpret_cast<void(*)(CParserForSkill*, int)>(0x9B39D0)(this, action);
	}

	CLexerForSkill::substAction = 0;
}

