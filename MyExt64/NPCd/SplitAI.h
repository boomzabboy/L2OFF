
#pragma once

#include <windows.h>
#include <string>
#include <map>

class SplitAI {
public:
	class IdMapping {
	public:
		IdMapping();

		std::string ProcessLine(const std::string &line);
		void Prepare();
		long GetLabel(const std::string &oldId);
		long GetString(const std::string &oldId);

		bool header;
		long lastLabelId;
		std::map<std::string, long> labels;
		long lastStringId;
		std::map<std::string, long> strings;
	};

	static void Init();

	static void* ReadSplitAI(const wchar_t *filename, UINT32 *filesize);

	static unsigned char *buffer;
};

