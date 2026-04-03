#include "Effects/EffectSystem.hpp"

void PVZ::EffectSystem::Extend(uint32_t num)
{
	PVZ::Memory::WriteMemory<uint32_t>(0x445424, num);
	PVZ::Memory::WriteMemory<uint32_t>(0x44541A, num * 236);
	PVZ::Memory::WriteMemory<uint32_t>(0x44543F, num * 160);
	PVZ::Memory::WriteMemory<uint32_t>(0x44545F, num * 780);
}
