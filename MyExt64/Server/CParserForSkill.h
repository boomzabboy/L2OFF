
#pragma once

#include <windows.h>
#include <Common/Yacc/yywcpars.h>

class CParserForSkill : public yl::yywparser {
public:
	static void Init();
	static UINT32 AbnormalVisualEffectHelper(const wchar_t *effect, class CSkillInfo *skillInfo);

	void yyaction_(int action);

	template<typename T>
	T GetYYAttr(int index)
	{
		return *reinterpret_cast<T*>(reinterpret_cast<long double*>(yyattributestackptr) + yytop + index);
	}

	/* ?????? */ unsigned char padding[0x00F8 - sizeof(yl::yywparser)];
	/* 0x00F8 */ class CSkillInfo *skillInfo;
	/* 0x0100 */ unsigned char padding0x0100[0x0104 - 0x0100];
	/* 0x0104 */ UINT32 operateConditionTarget;
};

