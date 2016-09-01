
#include <Server/BuilderCmd2Handler.h>
#include <Server/CUser.h>
#include <Server/CUserSocket.h>
#include <Server/CObjectDB.h>
#include <Common/Utils.h>
#include <Common/CLog.h>
#include <Common/Config.h>
#include <sstream>

void BuilderCmd2Handler::Init()
{
	WriteInstructionCall(0x91ED7C, reinterpret_cast<UINT32>(Handler));
}

bool __cdecl BuilderCmd2Handler::Handler(CUserSocket *socket, const BYTE *packet)
{ GUARDED

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
		return Say(socket, user, target, packet, buffer);
	} else if (buffer.substr(0, 14) == L"drop_item_each") {
		return DropItemEach(socket, user, target, packet, buffer);
	} else if (buffer.substr(0, 5) == L"give ") {
		return Give(socket, user, target, packet, buffer);
	} else if (buffer.substr(0, 5) == L"take ") {
		return Take(socket, user, target, packet, buffer);
	} else {
		return reinterpret_cast<bool(*)(CUserSocket*, const BYTE*)>(0x4E2BA0)(socket, packet);
	}
}

bool BuilderCmd2Handler::Say(CUserSocket *socket, CUser *user, CCreature *target, const BYTE *packet, const std::wstring &buffer)
{
	std::wstring sentence = user->GetName();
	sentence += L": ";
	sentence += buffer.substr(4);
	if (sentence.size() > 900) {
		sentence = sentence.substr(0, 897) + L"...";
	}
	return reinterpret_cast<bool(*)(CUserSocket*, CUser*, const wchar_t*)>(0x48E244)(socket, user, sentence.c_str());
}

bool BuilderCmd2Handler::DropItemEach(CUserSocket *socket, CUser *user, CCreature *target, const BYTE *packet, const std::wstring &buffer)
{
	std::wstringstream s;
	s << buffer;
	std::wstring cmd;
	std::wstring itemType;
	UINT64 count = 0;
	s >> cmd >> itemType >> count;
	if (count > 1000) {
		socket->SendSystemMessage(Config::Instance()->server->name.c_str(), L"That's not a good idea...");
		return false;
	} else {
		return reinterpret_cast<bool(*)(CUserSocket*, const BYTE*)>(0x4E2BA0)(socket, packet);
	}
}

bool BuilderCmd2Handler::Give(CUserSocket *socket, CUser *user, CCreature *target, const BYTE *packet, const std::wstring &buffer)
{
	std::wstringstream s;
	s << buffer;
	std::wstring cmd;
	std::wstring itemType;
	UINT64 count = 0;
	s >> cmd >> itemType >> count;
	if (!target || !target->IsUser()) {
		socket->SendSystemMessage(Config::Instance()->server->name.c_str(), L"Invalid target");
		return false;
	}
	if (count <= 0) {
		socket->SendSystemMessage(Config::Instance()->server->name.c_str(), L"Invalid count");
		return false;
	}
	int itemTypeId = CObjectDB::Instance()->GetClassIdFromName(itemType.c_str());
	if (itemTypeId <= 0) {
		itemTypeId = _wtoi(itemType.c_str());
		if (itemTypeId <= 0) {
			socket->SendSystemMessage(Config::Instance()->server->name.c_str(), L"Unknown item");
			return false;
		}
	}
	if (target->AddItemToInventory(itemTypeId, count)) {
		socket->SendSystemMessageFmt(Config::Instance()->server->name.c_str(),
			L"Gave %dx item %s (%d) to %s",
			count, itemType.c_str(), itemTypeId, target->GetName());
	} else {
		socket->SendSystemMessageFmt(Config::Instance()->server->name.c_str(),
			L"Failed to give %dx item %s (%d) to %s",
			count, itemType.c_str(), itemTypeId, target->GetName());
	}
	return false;
}

bool BuilderCmd2Handler::Take(CUserSocket *socket, CUser *user, CCreature *target, const BYTE *packet, const std::wstring &buffer)
{
	std::wstringstream s;
	s << buffer;
	std::wstring cmd;
	std::wstring itemType;
	UINT64 count = 0;
	s >> cmd >> itemType >> count;
	if (!target || !target->IsUser()) {
		socket->SendSystemMessage(Config::Instance()->server->name.c_str(), L"Invalid target");
		return false;
	}
	if (count <= 0) {
		socket->SendSystemMessage(Config::Instance()->server->name.c_str(), L"Invalid count");
		return false;
	}
	int itemTypeId = CObjectDB::Instance()->GetClassIdFromName(itemType.c_str());
	if (itemTypeId <= 0) {
		itemTypeId = _wtoi(itemType.c_str());
		if (itemTypeId <= 0) {
			socket->SendSystemMessage(Config::Instance()->server->name.c_str(), L"Unknown item");
			return false;
		}
	}
	if (reinterpret_cast<CUser*>(target)->TakeItem(itemTypeId, count)) {
		socket->SendSystemMessageFmt(Config::Instance()->server->name.c_str(),
			L"Taken %dx item %s (%d) from %s",
			count, itemType.c_str(), itemTypeId, target->GetName());
	} else {
		socket->SendSystemMessageFmt(Config::Instance()->server->name.c_str(),
			L"Failed to take %dx item %s (%d) from %s",
			count, itemType.c_str(), itemTypeId, target->GetName());
	}
	return false;
}

