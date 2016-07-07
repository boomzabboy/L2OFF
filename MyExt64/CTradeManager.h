
#pragma once

#include "SmartPtr.h"
#include "CTrade.h"

class CTradeManager {
protected:
	CTradeManager();

public:
	static CTradeManager* Instance();

	SmartPtr<CTrade> GetTrade(UINT32 tradeId);
};