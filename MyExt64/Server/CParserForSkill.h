
#pragma once

#include <Common/Yacc/yywcpars.h>

class CParserForSkill : public yl::yywparser {
public:
	static void Init();

	void yyaction_(int action);

	/* ?????? */ unsigned char padding[0x00F8 - sizeof(yl::yywparser)];
	/* 0x00F8 */ class CSkillInfo *skillInfo;
};

