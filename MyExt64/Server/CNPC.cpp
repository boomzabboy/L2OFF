
#include <Server/CNPC.h>
#include <Server/EventDrop.h>
#include <Common/Utils.h>
#include <Common/CSharedCreatureData.h>
#include <Common/CLog.h>

void CNPC::Init()
{
	WriteInstructionCall(0x7B7168 + 0x5C7, reinterpret_cast<UINT32>(DieWrapper));
	WriteInstructionCall(0x880B1C + 0x8B, reinterpret_cast<UINT32>(DieWrapper));
	WriteMemoryQWORD(0xA73848, reinterpret_cast<UINT64>(DieWrapper));
	WriteMemoryQWORD(0xAB9758, reinterpret_cast<UINT64>(DieWrapper));
	WriteMemoryQWORD(0xB1FB08, reinterpret_cast<UINT64>(DieWrapper));
	WriteMemoryQWORD(0xB7D3A8, reinterpret_cast<UINT64>(DieWrapper));
	WriteMemoryQWORD(0xB93FD8, reinterpret_cast<UINT64>(DieWrapper));
	WriteMemoryQWORD(0xC32068, reinterpret_cast<UINT64>(DieWrapper));
	WriteMemoryQWORD(0xC393D8, reinterpret_cast<UINT64>(DieWrapper));
	WriteMemoryQWORD(0xC3BDF8, reinterpret_cast<UINT64>(DieWrapper));
	WriteMemoryQWORD(0xC8C9D8, reinterpret_cast<UINT64>(DieWrapper));
}

bool __cdecl CNPC::DieWrapper(CNPC *self, CCreature *killer)
{
	return self->Die(killer);
}

bool CNPC::Die(CCreature *killer)
{
	GUARDED;

	if (this && killer && !IsUser() && !IsSummon() && (killer->IsUser() || killer->IsSummon())) {
		EventDrop::Data *data = EventDrop::data;
		if (data->maxLevelDifference < 0 || sd->level >= killer->sd->level - data->maxLevelDifference) {
			double r = static_cast<double>(rand()) / (static_cast<double>(RAND_MAX/100.0));
			double s = 0.0;
			for (size_t i = 0 ; i < data->items.size() ; ++i) {
				s += data->items[i].chance;
				if (s > r) {
					AddItemToInventory(data->items[i].itemId, 1);
					break;
				}
			}
		}
	}

	return reinterpret_cast<bool(*)(CNPC*, CCreature*)>(0x72972C)(this, killer);
}

