
#include <Server/BuilderCmd2Handler.h>
#include <Server/CUser.h>
#include <Server/CUserSocket.h>
#include <Common/Utils.h>
#include <Common/CLog.h>
#include <Common/Config.h>
#include <sstream>

void BuilderCmd2Handler::Init()
{
	WriteInstructionCall(0x91ED7C, reinterpret_cast<UINT32>(Handler));
}

bool __cdecl BuilderCmd2Handler::Handler(CUserSocket *socket, const BYTE *packet)
{
	CUser *user = socket->user;
	if (!user) {
		return false;
	}

	std::wstring buffer(reinterpret_cast<const wchar_t*>(packet));
	if (buffer.size() > 900) {
		return false;
	}

	CCreature *target = user->GetTarget();
	if (target) {
		CLog::Add(CLog::Blue, L"[AUDIT] BuilderCmd %s -> %s: %s", user->GetName(), target->GetName(), buffer.c_str());
	} else {
		CLog::Add(CLog::Blue, L"[AUDIT] BuilderCmd %s -> null: %s", user->GetName(), buffer.c_str());
	}

	if (buffer == L"gmliston") {
		return reinterpret_cast<bool(*)(CUserSocket*, CUser*, const wchar_t*)>(0x49E63C)(socket, user, L"//gmreg");
	} else if (buffer == L"gmlistoff") {
		return reinterpret_cast<bool(*)(CUserSocket*, CUser*, const wchar_t*)>(0x49E898)(socket, user, L"//gmunreg");
	} else if (buffer == L"res") {
		return reinterpret_cast<bool(*)(CUserSocket*, CUser*, const wchar_t*)>(0x4AB058)(socket, user, L"//resurrect 100");
	} else if (buffer == L"res 0") {
		return reinterpret_cast<bool(*)(CUserSocket*, CUser*, const wchar_t*)>(0x4AB058)(socket, user, L"//resurrect 0");
	} else if (buffer == L"heal") {
		if (target) {
			return reinterpret_cast<bool(*)(CUserSocket*, CUser*, const wchar_t*)>(0x4D3644)(socket, user, target->GetName());
		} else {
			return reinterpret_cast<bool(*)(CUserSocket*, CUser*, const wchar_t*)>(0x4D3644)(socket, user, user->GetName());
		}
	} else if (buffer.substr(0, 4) == L"say ") {
		std::wstring sentence = user->GetName();
		sentence += L": ";
		sentence += buffer.substr(4);
		if (sentence.size() > 900) {
			sentence = sentence.substr(0, 897) + L"...";
		}
		return reinterpret_cast<bool(*)(CUserSocket*, CUser*, const wchar_t*)>(0x48E244)(socket, user, sentence.c_str());
	} else if (buffer.substr(0, 14) == L"drop_item_each") {
		std::wstringstream s;
		s << buffer;
		std::wstring cmd;
		std::wstring itemType;
		UINT64 count = 0;
		s >> cmd >> itemType >> count;
		if (count > 1000) {
			socket->SendSystemMessage(Config::Instance()->server->name.c_str(), L"That's not a good idea...");
			return false;
		}
	}

	return reinterpret_cast<bool(*)(CUserSocket*, const BYTE*)>(0x4E2BA0)(socket, packet);
}

