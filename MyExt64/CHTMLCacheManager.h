
#pragma once

class CHTMLCacheManager {
public:
	static void Init();

	static bool __cdecl IsValidLinkWrapper(CHTMLCacheManager *self, void *data, const wchar_t *link, class CUser *user);

	bool IsValidLink(void *data, const wchar_t *link, class CUser *user);
};

