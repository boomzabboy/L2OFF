
#include "DropRate.h"
#include "CCreature.h"
#include "Config.h"
#include "CSharedCreatureData.h"
#include "CLog.h"
#include "Utils.h"
#include <math.h>
#include <fstream>

void DropRate::Init()
{
	WriteMemoryQWORD(0xA733D8, reinterpret_cast<UINT64>(CNPCSetDrop));
	WriteMemoryQWORD(0xAB92E8, reinterpret_cast<UINT64>(CNPCSetDrop));
	WriteMemoryQWORD(0xB1F698, reinterpret_cast<UINT64>(CNPCSetDrop));
	WriteMemoryQWORD(0xB7CF38, reinterpret_cast<UINT64>(CNPCSetDrop));
	WriteMemoryQWORD(0xB93B68, reinterpret_cast<UINT64>(CNPCSetDrop));
	WriteMemoryQWORD(0xBCB518, reinterpret_cast<UINT64>(CNPCSetDrop));
	WriteMemoryQWORD(0xBCCC48, reinterpret_cast<UINT64>(CNPCSetDrop));
	WriteMemoryQWORD(0xC31BF8, reinterpret_cast<UINT64>(CNPCSetDrop));
	WriteMemoryQWORD(0xC38F68, reinterpret_cast<UINT64>(CNPCSetDrop));
	WriteMemoryQWORD(0xC39AE8, reinterpret_cast<UINT64>(CNPCSetDrop));
	WriteMemoryQWORD(0xC3B988, reinterpret_cast<UINT64>(CNPCSetDrop));
	WriteMemoryQWORD(0xC8C568, reinterpret_cast<UINT64>(CNPCSetDrop));
	WriteMemoryQWORD(0xA73A98, reinterpret_cast<UINT64>(CNPCSetDropMulti));
	WriteMemoryQWORD(0xAB99A8, reinterpret_cast<UINT64>(CNPCSetDropMulti));
	WriteMemoryQWORD(0xB1FD58, reinterpret_cast<UINT64>(CNPCSetDropMulti));
	WriteMemoryQWORD(0xB7D5F8, reinterpret_cast<UINT64>(CNPCSetDropMulti));
	WriteMemoryQWORD(0xB94228, reinterpret_cast<UINT64>(CNPCSetDropMulti));
	WriteMemoryQWORD(0xBCBBD8, reinterpret_cast<UINT64>(CNPCSetDropMulti));
	WriteMemoryQWORD(0xBCD308, reinterpret_cast<UINT64>(CNPCSetDropMulti));
	WriteMemoryQWORD(0xC322B8, reinterpret_cast<UINT64>(CNPCSetDropMulti));
	WriteMemoryQWORD(0xC39628, reinterpret_cast<UINT64>(CNPCSetDropMulti));
	WriteMemoryQWORD(0xC3A1A8, reinterpret_cast<UINT64>(CNPCSetDropMulti));
	WriteMemoryQWORD(0xC3C048, reinterpret_cast<UINT64>(CNPCSetDropMulti));
	WriteMemoryQWORD(0xC8CC28, reinterpret_cast<UINT64>(CNPCSetDropMulti));

	if (Config::Instance()->rate->dump) {
		std::ofstream("..\\dump\\dropspoil.txt").close();
	}
}

void DropRate::CNPCSetDrop(CCreature *npc, UINT32 type, std::vector<ItemDrop*> &data)
{
	double dropRate = type == 144 ? Config::Instance()->rate->spoilRate : npc->IsBoss() ? Config::Instance()->rate->bossDropRate : Config::Instance()->rate->dropRate;
	if (Config::Instance()->rate->fixupLowLevel && npc->sd->level < 20) {
		dropRate = max(1, floor(0.5 + pow(npc->sd->level / 20.0, log((double) dropRate) / log((double) 4)) * dropRate));
	}

	for (std::vector<ItemDrop*>::iterator idata(data.begin()) ; idata != data.end() ; ++idata) {
		ItemDrop &item(**idata);
		ItemDrop old(item);
		if (item.itemId == 57) {
			item.countMin = UINT32(max(1, double(item.countMin) * Config::Instance()->rate->adenaRate));
			item.countMax = UINT32(max(1, double(item.countMax) * Config::Instance()->rate->adenaRate));
		} else if (!Config::Instance()->rate->ignoredItems.count(item.itemId)) {
			double score = float(item.countMin + item.countMax) * item.chance;
			item.chance *= dropRate;
			if (item.chance > 100.0) {
				score *= dropRate;

				item.countMin = UINT32(max(1, floor(0.5 + item.countMin * dropRate / 100.0)));
				item.countMax = UINT32(max(1, floor(0.5 + item.countMax * dropRate / 100.0)));

				for (;;) {
					item.chance = score / float(item.countMin + item.countMax);
					if (item.chance <= 100.0) {
						break;
					}
					++item.countMax;
				}
			}
		}

		if (Config::Instance()->rate->dump) {
			std::ofstream("..\\dump\\dropspoil.txt", std::ios::app)
				<< (npc->sd->npcClassId - 1000000) << "\t"
				<< static_cast<int>(type) << "\t"
				<< item.itemId << "\t"
				<< item.countMin << "\t"
				<< item.countMax << "\t"
				<< item.chance << std::endl;
		}
	}

	reinterpret_cast<void(*)(CCreature*, UINT32, std::vector<ItemDrop*>&)>(0x724090)(npc, type, data);
}

void DropRate::CNPCSetDropMulti(CCreature *npc, UINT32 type, std::vector<ItemDropMulti*> &data)
{

	double dropRate;
	if (type == 250) {
		dropRate = Config::Instance()->rate->herbRate;
	} else {
		dropRate = npc->IsBoss() ? Config::Instance()->rate->bossDropRate : Config::Instance()->rate->dropRate;
		if (Config::Instance()->rate->fixupLowLevel && npc->sd->level < 20) {
			dropRate = max(1, floor(0.5 + pow(npc->sd->level / 20.0, log((double) dropRate) / log((double) 4)) * dropRate));
		}
	}

	for (std::vector<ItemDropMulti*>::iterator idata(data.begin()) ; idata != data.end() ; ++idata) {
		bool stopGroup(false);
		double oldGroupChance = (*idata)->chance;
		size_t itemCount = 0;
		std::vector<ItemDrop> oldItems;

		for (std::vector<ItemDrop*>::iterator iidata((*idata)->items->begin()) ;
			 iidata != (*idata)->items->end() ;
			 ++iidata) {

			ItemDrop drop;
			drop.countMin = (*iidata)->countMin;
			drop.countMax = (*iidata)->countMax;
			drop.chance = (*iidata)->chance;
			oldItems.push_back(drop);

			if ((*iidata)->itemId == 57) { // adena
				(*iidata)->countMin = UINT32(max(1, double((*iidata)->countMin) * Config::Instance()->rate->adenaRate));
				(*iidata)->countMax = UINT32(max(1, double((*iidata)->countMax) * Config::Instance()->rate->adenaRate));
                stopGroup = true;
			} else if (Config::Instance()->rate->ignoredItems.count((*iidata)->itemId)) {
				stopGroup = true;
            }
			++itemCount;
        }

        if (!stopGroup) {
			(*idata)->chance *= dropRate;
			if ((*idata)->chance > 100.0) {
				(*idata)->chance = 100.0;
				double adjustedDropRate = dropRate * oldGroupChance * 0.01;
				double threshold = 100.0 / adjustedDropRate / double(itemCount);
				double s1 = 0.0, s2 = 0.0;

				for (std::vector<ItemDrop*>::iterator iidata((*idata)->items->begin()) ;
					 iidata != (*idata)->items->end() ;
					 ++iidata) {

					bool overThreshold = (*iidata)->chance > threshold;
					double exp = 1.0;
					if (overThreshold) {
						double delta1 = (*iidata)->chance - threshold;
						double delta2 = 100.0 - threshold;
						exp = - delta1 / delta2;
					}
					(*iidata)->chance *= pow(adjustedDropRate, exp);
					if (overThreshold) {
						s1 += (*iidata)->chance;
					} else {
						s2 += (*iidata)->chance;
					}
				}

				std::vector<ItemDrop>::iterator ioldItems(oldItems.begin());
				for (std::vector<ItemDrop*>::iterator iidata((*idata)->items->begin()) ;
					 iidata != (*idata)->items->end() ;
					 ++iidata) {

					if (ioldItems->chance > threshold) {
						(*iidata)->chance *= (100.0 - s2) / s1;
					}
					double coef = ioldItems->countMin + ioldItems->countMax;
					coef *= ioldItems->chance * oldGroupChance;
					double denom = (*iidata)->countMin + (*iidata)->countMax;
					denom *= (*iidata)->chance * (*idata)->chance;
					coef /= denom;
					coef *= dropRate;
					(*iidata)->countMin = UINT32(max(1, floor(0.5 + (*iidata)->countMin * max(1.0, coef))));
					(*iidata)->countMax = UINT32(max(1, floor(0.5 + (*iidata)->countMax * max(1.0, coef))));
				}
			}
		}

		if (Config::Instance()->rate->dump) {
			for (std::vector<ItemDrop*>::iterator iidata((*idata)->items->begin()) ;
				 iidata != (*idata)->items->end() ;
				 ++iidata) {

				std::ofstream("..\\dump\\dropspoil.txt", std::ios::app)
					<< (npc->sd->npcClassId - 1000000) << "\t"
					<< static_cast<int>(type) << "\t"
					<< (*iidata)->itemId << "\t"
					<< (*iidata)->countMin << "\t"
					<< (*iidata)->countMax << "\t"
					<< (*iidata)->chance * (*idata)->chance * 0.01 << std::endl;
			}
		}
    }

	reinterpret_cast<void(*)(CCreature*, UINT32, std::vector<ItemDropMulti*>&)>(0x724288)(npc, type, data);
}

