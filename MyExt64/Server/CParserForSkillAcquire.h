
#pragma once

#include <windows.h>
#include <Common/Yacc/yywcpars.h>

class CParserForSkillAcquire : public yl::yywparser {
public:
	static void Init();

	void yyaction_(int action);

	template<typename T>
	T GetYYAttr(int index)
	{
		return *reinterpret_cast<T*>(reinterpret_cast<long double*>(yyattributestackptr) + yytop + index);
	}
};

