
#pragma once

#include <vector>

class AbnormalType {
public:
	AbnormalType(const int id = 0, const wchar_t *name = 0);

	const wchar_t *name;
	int id;

	static void Init();
	static void Copy();
	static void Add(const wchar_t *name);
	static void Setup();

	static AbnormalType abnormalTypes[1024];
	static size_t abnormalTypesSize;
};

