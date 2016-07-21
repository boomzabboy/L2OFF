
#include <Server/CInstantZone.h>
#include <Server/CUser.h>
#include <Server/CDB.h>
#include <Common/CSharedCreatureData.h>
#include <Common/Utils.h>
#include <Common/CLog.h>
#include <time.h>

std::map<CInstantZone*, CInstantZone::InZoneData> CInstantZone::zones;
CriticalSection CInstantZone::zonesLock;

void CInstantZone::Init()
{
	WriteInstructionCall(0x68065D, reinterpret_cast<UINT32>(OnReleaseWrapper));
	WriteInstructionCall(0x682684, reinterpret_cast<UINT32>(EnterZoneWrapper));
	WriteInstructionCall(0x68306B, reinterpret_cast<UINT32>(EnterZoneWrapper));
	WriteInstructionCall(0x6835BC, reinterpret_cast<UINT32>(SetBindingAllUserWrapper));
	WriteInstructionCall(0x67E1AD, reinterpret_cast<UINT32>(SetBindingWrapper));
	WriteInstructionCall(0x683235, reinterpret_cast<UINT32>(SetBindingWrapper));
}

void __cdecl CInstantZone::OnReleaseWrapper(CInstantZone *self)
{
	GUARDED;
	self->OnRelease();
}

bool __cdecl CInstantZone::EnterZoneWrapper(CInstantZone *self, CUser *user, double *position, int enterType)
{
	GUARDED;
	return self->EnterZone(user, position, enterType);
}

void __cdecl CInstantZone::SetBindingAllUserWrapper(CInstantZone *self)
{
	GUARDED;
	self->SetBindingAllUser();
}

void __cdecl CInstantZone::SetBindingWrapper(CInstantZone *self, CUser *user, UINT32 time)
{
	GUARDED;
	self->SetBinding(user, time);
}

void CInstantZone::OnRelease()
{
	reinterpret_cast<void(*)(CInstantZone*)>(0x67DE8C)(this);

	ScopedLock lock(zonesLock);
	std::map<CInstantZone*, InZoneData>::iterator i = zones.find(this);
	if (i != zones.end()) {
		zones.erase(i);
	}
}

bool CInstantZone::EnterZone(CUser *user, double *position, int enterType)
{
	if (!reinterpret_cast<bool(*)(CInstantZone*, CUser*, double*, int)>(0x680A30)(this, user, position, enterType)) {
		return false;
	}

	ScopedLock lock(zonesLock);
	zones[this].userRestrictions[user->GetDbId()].inZoneRestrictionMap1 = user->inZoneRestrictionMap1;
	zones[this].userRestrictions[user->GetDbId()].inZoneRestrictionMap2 = user->inZoneRestrictionMap2;
	return true;
}

void CInstantZone::SetBindingAllUser()
{
	reinterpret_cast<void(*)(CInstantZone*)>(0x683154)(this);

	ScopedLock lock(zonesLock);
	std::map<CInstantZone*, InZoneData>::iterator i = zones.find(this);
	if (i != zones.end()) {
		UINT32 now = _time32(0);
		for (std::map<UINT32, InZoneUser>::iterator j = i->second.userRestrictions.begin() ;
			j != i->second.userRestrictions.end() ; ++j) {

			CDB::Instance()->RequestMarkInZoneRestriction(
				j->first, id, now, j->second.inZoneRestrictionMap1[id].cnt + 1, false, 1);

			Data::Data2 *data2 = data->data2;
			if (data2) {
				CDB::Instance()->RequestMarkInZoneRestriction(
					j->first, data2->id, now, j->second.inZoneRestrictionMap2[data2->id].cnt + 1, true, data2->unknown);
			}
		}
	}
}

void CInstantZone::SetBinding(CUser *user, UINT32 time)
{
	reinterpret_cast<void(*)(CInstantZone*, CUser*, UINT32)>(0x6781B0)(this, user, time);

	ScopedLock lock(zonesLock);
	std::map<CInstantZone*, InZoneData>::iterator i = zones.find(this);
	if (i == zones.end()) {
		return;
	}
	std::map<UINT32, InZoneUser>::iterator j = i->second.userRestrictions.find(user->GetDbId());
	if (j == i->second.userRestrictions.end()) {
		return;
	}
	i->second.userRestrictions.erase(j);
}

