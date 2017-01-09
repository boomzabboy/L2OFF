
#pragma once

#include <Common/Utils.h>
#include <string>

class Variable {
public:
	std::wstring name;
	INT32 offset;
	unsigned char padding0x002C[4];
	class Type *type;
};

