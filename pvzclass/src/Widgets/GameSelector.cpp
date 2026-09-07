#include "Widgets/GameSelector.hpp"

void PVZ::GameSelector::SetMemSize(uint32_t NewSize)
{
	PVZ::Memory::WriteMemory<uint32_t>(0x44F92A, NewSize);
}

PVZ::GameSelector PVZ::GetGameSelector()
{
	int address = Memory::ReadPointer(0x6A9EC0, 0x770);
	return(address == 0 ? INVALID_BASEADDRESS : PVZ::GameSelector(address));
}
