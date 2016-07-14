
#pragma once

#include <Server/CTrade.h>
#include <Common/SmartPtr.h>

class CTradeManager {
protected:
	CTradeManager();

public:
	static CTradeManager* Instance();

	SmartPtr<CTrade> GetTrade(UINT32 tradeId);
};