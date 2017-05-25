
#include <Server/CParserForItem.h>
#include <Server/CLexerForItem.h>
#include <Server/CItem.h>
#include <Common/Utils.h>
#include <Common/CLog.h>

void CParserForItem::Init()
{
	WriteMemoryQWORD(0xCE64D0, FnPtr(&CParserForItem::yyaction_));
}

void CParserForItem::yyaction_(int action)
{
	CItem::ItemInfo *itemInfo = reinterpret_cast<CItem::ItemInfo*>(yyvalptr);

	if (CLexerForItem::substAction) {
		if (CLexerForItem::substOwn) {
			action = CLexerForItem::substAction;
			switch (action) {
			case CLexerForItem::is_private_store:
				itemInfo->ext.isPrivateStore = _wtoi(yylexerptr->yytext);
				itemInfo->ext.isPrivateStoreSet = true;
				break;
			case CLexerForItem::is_olympiad_can_use:
				itemInfo->ext.isOlympiadCanUse = _wtoi(yylexerptr->yytext);
				break;
			}
		} else {
			reinterpret_cast<void(*)(CParserForItem*, int)>(0x9A3C10)(this, CLexerForItem::substAction);
		}
		CLexerForItem::substAction = 0;
	} else {
		reinterpret_cast<void(*)(CParserForItem*, int)>(0x9A3C10)(this, action);
	}
}

//CompileTimeOffsetCheck(CParserForItem, skillInfo, 0xF8);

