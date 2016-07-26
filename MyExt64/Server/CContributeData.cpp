
#include <Server/CContributeData.h>
#include <Server/CUser.h>
#include <Server/CSummon.h>
#include <Common/Utils.h>

bool CContributeData::PickableIn5Sec(CCreature *creature)
{
	return reinterpret_cast<bool(*)(CContributeData*, CCreature*)>(0x758504)(this, creature);
}

double CContributeData::GetContributeInfos(std::map<UINT32, double> &infos)
{
	double result = 0.0;
	for (std::map<UINT32, double>::const_iterator i = data.begin() ; i != data.end() ; ++i) {
		result += i->second;
		infos.insert(*i);
	}
	return result;
}

CompileTimeOffsetCheck(CContributeData, data, 0x0060);
CompileTimeOffsetCheck(CContributeData, looterObjectId, 0x0078);

