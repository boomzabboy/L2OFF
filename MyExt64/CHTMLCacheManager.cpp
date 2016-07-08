
#include "CHTMLCacheManager.h"
#include "CUser.h"
#include "Utils.h"

void CHTMLCacheManager::Init()
{
	WriteMemoryBYTES(0x948DC6, "\x4C\x8B\xCE", 3);
	WriteInstructionCall(0x948DD5, reinterpret_cast<UINT32>(IsValidLinkWrapper));
	WriteMemoryBYTES(0x94A2BA, "\x4C\x8B\xCE", 3);
	WriteInstructionCall(0x94A2CC, reinterpret_cast<UINT32>(IsValidLinkWrapper));
}

bool CHTMLCacheManager::IsValidLinkWrapper(CHTMLCacheManager *self, void *data, const wchar_t *link, CUser *user)
{
	return self->IsValidLink(data, link, user);
}

bool CHTMLCacheManager::IsValidLink(void *data, const wchar_t *link, CUser *user)
{
	std::wstring link_(link);
	if (link_ == L"_bbsclan" || link_ == L"_bbshome"  || link_ == L"manor_menu_select") {
		return true;
	}

	user->htmlLock.Enter(__FILEW__, __LINE__);

	bool result = reinterpret_cast<bool(*)(CHTMLCacheManager*, void*, const wchar_t*, const UINT32)>(
		0x669D8C)(this, data, link, 0);
	reinterpret_cast<void*(*)(void*)>(0x8D2C88)(data);

	user->htmlLock.Leave(__FILEW__, __LINE__);

	return result;
}

