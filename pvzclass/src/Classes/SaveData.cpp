#include "Classes/SaveData.hpp"

PVZ::PlayerInfo PVZ::GetPlayerInfo()
{
	return PlayerInfo(Memory::ReadPointer(0x6A9EC0, 0x82C));
}

PVZ::PlayerInfo PVZ::GetSaveData()
{
	return PVZ::GetPlayerInfo();
}

void PVZ::PlayerInfo::GetPVZUserName(char str[])
{
	Memory::ReadArray<char>(BaseAddress + 4, str, 12);
}
int PVZ::PlayerInfo::GetChallengeRecord(PVZLevel::PVZLevel mode)
{
	return Memory::ReadMemory<int>(BaseAddress + 0x30 + (mode - 1) * 4);
}

void PVZ::PlayerInfo::SetChallengeRecord(PVZLevel::PVZLevel mode, int val)
{
	Memory::WriteMemoryUnsafe<int>(BaseAddress + 0x30 + (mode - 1) * 4, val);
}

int PVZ::PlayerInfo::GetPurchase(StoreItem::StoreItem item)
{
	return Memory::ReadMemory<int>(BaseAddress + 0x1C0 + item * 4);
}

void PVZ::PlayerInfo::SetPurchase(StoreItem::StoreItem item, int val)
{
	Memory::WriteMemoryUnsafe<int>(BaseAddress + 0x1C0 + item * 4, val);
}

BOOLEAN PVZ::PlayerInfo::HavePurpleCard(SeedType::SeedType purplecard)
{
	if (purplecard >= SeedType::GatlingPea && purplecard <= SeedType::CobCannon)
		return Memory::ReadMemory<int>(BaseAddress + 0x1C0 + (purplecard - 40) * 4);
	return false;
}

PVZ::GardenPlant PVZ::PlayerInfo::GetGardenPlant(int index)
{
	if (index >= 0 && index < GardenPlantCount)
		return GardenPlant(BaseAddress + 0x350 + index * 0x58);
	else
		return NULL;
}
