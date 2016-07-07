
#include "CTradeManager.h"
#include "CTrade.h"

CTradeManager::CTradeManager()
{
}

CTradeManager* CTradeManager::Instance()
{
	return reinterpret_cast<CTradeManager*>(0x11F3C9C0);
}

SmartPtr<CTrade> CTradeManager::GetTrade(UINT32 tradeId)
{
	SmartPtr<CTrade> result;
	reinterpret_cast<void(*)(CTradeManager*, SmartPtr<CTrade>*, UINT32)>(0x872A48)(this, &result, tradeId);
	return result;
}

