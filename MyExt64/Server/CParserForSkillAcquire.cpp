
#include <Server/CParserForSkillAcquire.h>
#include <Server/CLexerForSkillAcquire.h>
#include <Common/Utils.h>
#include <Common/CLog.h>

class SkillAcquireInfo {
public:
	int skillId;
	int skillLevel;
	int classType;
	int type;
	int unknown;
};

class CSkillAcquireDB {
public:
	static int substType;

	template<UINT32 origAddr>
	void AddSkillAcquireInfo(SkillAcquireInfo *skillAcquireInfo)
	{
		if (substType >= 0) {
			skillAcquireInfo->type = substType;
		}
		reinterpret_cast<void(*)(CSkillAcquireDB*, SkillAcquireInfo*)>(origAddr)(
			this, skillAcquireInfo);
	}

	unsigned char padding[0x12A0];
	unsigned char newEtcSkills[0x20 * 3];
};

static CSkillAcquireDB skillAcquireDB;

int CSkillAcquireDB::substType = -1;

namespace {

bool AcquireHelper(class CUser *self, int skillId, int skillLevel, int etcSkillType)
{
	if (etcSkillType >= 7 && etcSkillType <= 9) {
		return true;
	}
	return reinterpret_cast<bool(*)(class CUser*, int, int)>(
		(*reinterpret_cast<void***>(self))[0x125])(self, skillId, skillLevel);
}

}

void CParserForSkillAcquire::Init()
{
	WriteMemoryQWORD(0xD3A6A0, FnPtr(&CParserForSkillAcquire::yyaction_));
	WriteMemoryDWORD(0x9D0E06, 10);
	WriteMemoryBYTE(0x8243F5, 0xEA);
	WriteAddress(0x4CC24C+0xA6+3, reinterpret_cast<UINT32>(&skillAcquireDB));
	WriteAddress(0x5B8104+0x1B8+3, reinterpret_cast<UINT32>(&skillAcquireDB));
	WriteAddress(0x5E8134+0xE2+3, reinterpret_cast<UINT32>(&skillAcquireDB));
	WriteAddress(0x6B1488+0x616+3, reinterpret_cast<UINT32>(&skillAcquireDB));
	WriteAddress(0x7418E0+0x252+3, reinterpret_cast<UINT32>(&skillAcquireDB));
	WriteAddress(0x7418E0+0x269+3, reinterpret_cast<UINT32>(&skillAcquireDB));
	WriteAddress(0x74A974+0xD5+3, reinterpret_cast<UINT32>(&skillAcquireDB));
	WriteAddress(0x7C41A4+0x67+3, reinterpret_cast<UINT32>(&skillAcquireDB));
	WriteAddress(0x7CDB90+0xD2+3, reinterpret_cast<UINT32>(&skillAcquireDB));
	WriteAddress(0x823E80+0x76+3, reinterpret_cast<UINT32>(&skillAcquireDB));
	WriteAddress(0x823E80+0x9E+3, reinterpret_cast<UINT32>(&skillAcquireDB));
	WriteAddress(0x8CE2EC+0x182+3, reinterpret_cast<UINT32>(&skillAcquireDB));
	WriteAddress(0x8F57A3+3, reinterpret_cast<UINT32>(&skillAcquireDB));
	WriteAddress(0x8F70B8+0x147+3, reinterpret_cast<UINT32>(&skillAcquireDB));
	WriteAddress(0x8F70B8+0x16C+3, reinterpret_cast<UINT32>(&skillAcquireDB));
	WriteAddress(0x8F7E08+0x92+3, reinterpret_cast<UINT32>(&skillAcquireDB));
	WriteAddress(0x90951C+0x14A+3, reinterpret_cast<UINT32>(&skillAcquireDB));
	WriteAddress(0x91F244+0x1BE+3, reinterpret_cast<UINT32>(&skillAcquireDB));
	WriteAddress(0x91F244+0x1DF+3, reinterpret_cast<UINT32>(&skillAcquireDB));
	WriteAddress(0x9D0B6C+0x82+3, reinterpret_cast<UINT32>(&skillAcquireDB));
	WriteAddress(0x9D0B6C+0x18F+3, reinterpret_cast<UINT32>(&skillAcquireDB));
	WriteAddress(0x9D0B6C+0x2C9+3, reinterpret_cast<UINT32>(&skillAcquireDB));
	WriteAddress(0x9D0B6C+0x347+3, reinterpret_cast<UINT32>(&skillAcquireDB));
	WriteAddress(0xA29FE0+0x4+3, reinterpret_cast<UINT32>(&skillAcquireDB));

	WriteMemoryBYTES(0x8CE629, "\x45\x89\xF9", 3); // mov r9d, r15d (etc skill type)
	WriteInstructionCall(0x8CE636, FnPtr(AcquireHelper), 0x8CE63D); // return true if type is 7, 8 or 9

	WriteInstructionCall(0x9D0D02, FnPtr(&CSkillAcquireDB::AddSkillAcquireInfo<0x8241DC>));
}

void CParserForSkillAcquire::yyaction_(int action)
{
	if (CLexerForSkillAcquire::substAction) {
		switch (CLexerForSkillAcquire::substAction) {
		case CLexerForSkillAcquire::bishop_sharing_begin:
			CSkillAcquireDB::substType = 7;
			break;
		case CLexerForSkillAcquire::elder_sharing_begin:
			CSkillAcquireDB::substType = 8;
			break;
		case CLexerForSkillAcquire::silen_elder_sharing_begin:
			CSkillAcquireDB::substType = 9;
			break;
		case CLexerForSkillAcquire::bishop_sharing_end:
		case CLexerForSkillAcquire::elder_sharing_end:
		case CLexerForSkillAcquire::silen_elder_sharing_end:
			CSkillAcquireDB::substType = -1;
			break;
		}
		CLexerForSkillAcquire::substAction = 0;
	}

	reinterpret_cast<void(*)(CParserForSkillAcquire*, int)>(0x9D0B6C)(this, action);
}

