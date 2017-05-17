
#pragma once

#include <Common/Yacc/yywcpars.h>

class CParserForSkill : public yl::yywparser {
public:
	static void Init();

	void yyaction_(int action);
};

