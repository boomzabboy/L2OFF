
#include <Server/Beta.h>
#include <Server/CUser.h>
#include <Server/CDB.h>
#include <Common/Config.h>
#include <Common/CSharedCreatureData.h>
#include <sstream>

void Beta::Bypass(CUser *user, const std::wstring &command)
{
	if (command.find(L"set_level?level=") == 0 && Config::Instance()->beta->level) {
		std::wstringstream ws;
		ws << command.substr(10 + 5 + 1);
		int level = -1;
		ws >> level;
		if (level >= 1 && level <= Config::Instance()->server->maxLevelMain) {
			const UINT64 *exp = reinterpret_cast<const UINT64*>(0xA77848);
			user->ExpInc(exp[level] - user->sd->exp, false);
		}
	} else if (command.find(L"set_class?class=") == 0 && Config::Instance()->beta->class_) {
		std::wstringstream ws;
		ws << command.substr(10 + 5 + 1);
		int newClass = -1;
		ws >> newClass;
		user->sdLock->Enter(__FILEW__, __LINE__);
		int oldClass = user->sd->class_;
		bool ok = false;
		switch (newClass) {
		case 1: case 4: case 7: ok = (oldClass == 0); break;
		case 2: case 3: ok = (oldClass == 1 || oldClass == 0); break;
		case 5: case 6: ok = (oldClass == 4 || oldClass == 0); break;
		case 8: case 9: ok = (oldClass == 7 || oldClass == 0); break;
		case 11: case 15: ok = (oldClass == 10); break;
		case 12: case 13: case 14: ok = (oldClass == 11 || oldClass == 10); break;
		case 16: case 17: ok = (oldClass == 15 || oldClass == 10); break;
		case 88: ok = (oldClass == 2 || oldClass == 1 || oldClass == 0); break;
		case 89: ok = (oldClass == 3 || oldClass == 1 || oldClass == 0); break;
		case 90: ok = (oldClass == 5 || oldClass == 4 || oldClass == 0); break;
		case 91: ok = (oldClass == 6 || oldClass == 4 || oldClass == 0); break;
		case 92: ok = (oldClass == 9 || oldClass == 7 || oldClass == 0); break;
		case 93: ok = (oldClass == 8 || oldClass == 7 || oldClass == 0); break;
		case 94: ok = (oldClass == 12 || oldClass == 11 || oldClass == 10); break;
		case 95: ok = (oldClass == 13 || oldClass == 11 || oldClass == 10); break;
		case 96: ok = (oldClass == 14 || oldClass == 11 || oldClass == 10); break;
		case 97: ok = (oldClass == 16 || oldClass == 15 || oldClass == 10); break;
		case 98: ok = (oldClass == 17 || oldClass == 15 || oldClass == 10); break;
		case 19: case 22: ok = (oldClass == 18); break;
		case 20: case 21: ok = (oldClass == 19 || oldClass == 18); break;
		case 23: case 24: ok = (oldClass == 22 || oldClass == 18); break;
		case 26: case 29: ok = (oldClass == 25); break;
		case 27: case 28: ok = (oldClass == 26 || oldClass == 25); break;
		case 30: ok = (oldClass == 29 || oldClass == 25); break;
		case 99: ok = (oldClass == 20 || oldClass == 19 || oldClass == 18); break;
		case 100: ok = (oldClass == 21 || oldClass == 19 || oldClass == 18); break;
		case 101: ok = (oldClass == 23 || oldClass == 22 || oldClass == 18); break;
		case 102: ok = (oldClass == 24 || oldClass == 22 || oldClass == 18); break;
		case 103: ok = (oldClass == 27 || oldClass == 26 || oldClass == 25); break;
		case 104: ok = (oldClass == 28 || oldClass == 26 || oldClass == 25); break;
		case 105: ok = (oldClass == 30 || oldClass == 29 || oldClass == 25); break;
		case 32: case 35: ok = (oldClass == 31); break;
		case 33: case 34: ok = (oldClass == 32 || oldClass == 31); break;
		case 36: case 37: ok = (oldClass == 35 || oldClass == 31); break;
		case 39: case 42: ok = (oldClass == 38); break;
		case 40: case 41: ok = (oldClass == 39 || oldClass == 38); break;
		case 43: ok = (oldClass == 42 || oldClass == 38); break;
		case 106: ok = (oldClass == 33 || oldClass == 32 || oldClass == 31); break;
		case 107: ok = (oldClass == 34 || oldClass == 32 || oldClass == 31); break;
		case 108: ok = (oldClass == 36 || oldClass == 35 || oldClass == 31); break;
		case 109: ok = (oldClass == 37 || oldClass == 35 || oldClass == 31); break;
		case 110: ok = (oldClass == 40 || oldClass == 39 || oldClass == 38); break;
		case 111: ok = (oldClass == 41 || oldClass == 39 || oldClass == 38); break;
		case 112: ok = (oldClass == 43 || oldClass == 42 || oldClass == 38); break;
		case 45: case 47: ok = (oldClass == 44); break;
		case 46: ok = (oldClass == 45 || oldClass == 44); break;
		case 48: ok = (oldClass == 47 || oldClass == 44); break;
		case 50: ok = (oldClass == 49); break;
		case 51: case 52: ok = (oldClass == 50 || oldClass == 49); break;
		case 113: ok = (oldClass == 46 || oldClass == 45 || oldClass == 44); break;
		case 114: ok = (oldClass == 48 || oldClass == 47 || oldClass == 44); break;
		case 115: ok = (oldClass == 51 || oldClass == 50 || oldClass == 49); break;
		case 116: ok = (oldClass == 52 || oldClass == 50 || oldClass == 49); break;
		case 54: case 56: ok = (oldClass == 53); break;
		case 55: ok = (oldClass == 54 || oldClass == 53); break;
		case 57: ok = (oldClass == 56 || oldClass == 53); break;
		case 117: ok = (oldClass == 55 || oldClass == 54 || oldClass == 53); break;
		case 118: ok = (oldClass == 57 || oldClass == 56 || oldClass == 53); break;
		case 125: ok = (oldClass == 123); break;
		case 126: ok = (oldClass == 124); break;
		case 127: ok = (oldClass == 125 || oldClass == 123); break;
		case 128: ok = (oldClass == 125 || oldClass == 123); break;
		case 129: ok = (oldClass == 126 || oldClass == 124); break;
		case 130: ok = (oldClass == 126 || oldClass == 124); break;
		case 131: ok = (oldClass == 127 || oldClass == 125 || oldClass == 123); break;
		case 132: ok = (oldClass == 128 || oldClass == 125 || oldClass == 123); break;
		case 133: ok = (oldClass == 129 || oldClass == 126 || oldClass == 124); break;
		case 134: ok = (oldClass == 130 || oldClass == 126 || oldClass == 124); break;
		}
		if (ok) {
			reinterpret_cast<bool(*)(CUser*, int)>(0x8A0C2C)(user, newClass);
		}
		user->sdLock->Leave(__FILEW__, __LINE__);
	} else if (command.find(L"give_adena") == 0 && Config::Instance()->beta->adena) {
		user->AddItemToInventory(57, 100000000);
	} else if (command.find(L"make_noblesse") == 0 && Config::Instance()->beta->noblesse) {
		reinterpret_cast<void(*)(CDB*, CUser*, UINT32)>(0x5990A8)(CDB::Instance(), user, 1);
		user->sdLock->Enter(__FILEW__, __LINE__);
		reinterpret_cast<void(*)(unsigned char*, int, BYTE)>(0x443730)(
			reinterpret_cast<unsigned char*>(user->sd) + 0x5D4, 235, 1);
		reinterpret_cast<void(*)(CDB*, CUser*)>(0x598680)(CDB::Instance(), user);
		user->sdLock->Leave(__FILEW__, __LINE__);
	} else if (command.find(L"give_sp") == 0 && Config::Instance()->beta->sp) {
		user->sdLock->Enter(__FILEW__, __LINE__);
		user->sd->sp = 2147483647;
		user->sdLock->Leave(__FILEW__, __LINE__);
		user->SendUserInfo();
	} else if (command.find(L"give_fame") == 0 && Config::Instance()->beta->fame) {
		user->SavePoint(5, 50000);
	}
}

