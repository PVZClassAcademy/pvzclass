#include "Classes/List.hpp"

uint32_t PVZ::IntListNode::GetBaseAddress()
{
    return this->BaseAddress;
}

uint32_t PVZ::IntList::GetBaseAddress()
{
    return this->BaseAddress;
}

void PVZ::IntList::AddHead(int val)
{
	PVZ::Memory::Execute(AsmBuilder()
		.push_imm32(val)
		.mov_reg_imm(REG_EBX, this->GetBaseAddress())
		.invoke(0x518AD0)
		.ret()
	);
}

void PVZ::IntList::AddTail(int val)
{
	PVZ::Memory::Execute(AsmBuilder()
		.push_imm32(val)
		.mov_reg_imm(REG_EBX, this->GetBaseAddress())
		.invoke(0x445210)
		.ret()
	);
}

void PVZ::IntList::RemoveAll()
{
	PVZ::Memory::Execute(AsmBuilder()
		.mov_reg_imm(REG_ESI, this->GetBaseAddress())
		.invoke(0x518B50)
		.ret()
	);
}
