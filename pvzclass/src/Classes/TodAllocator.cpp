#include "Classes/TodAllocator.hpp"

PVZ::TodAllocator PVZ::TodAllocator::FindGlobalAllocator(int size)
{
    return TodAllocator(PVZ::Memory::Execute(AsmBuilder()
		.mov_reg_imm(REG_EDI, size)
		.invoke(0x513570)
		.mov_mem_reg(PVZ::Memory::Variable, REG_EAX)
		.ret()
	));
}
