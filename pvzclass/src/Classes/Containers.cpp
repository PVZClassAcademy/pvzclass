#include "Classes/Containers.hpp"

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

constexpr int nil_vector[3]{ 0, 0, 0 };
PVZ::IntVector PVZ::IntVector::Make()
{
	uint32_t address = PVZ::Memory::AllocMemoryUnsafe(0, 16);
	PVZ::Memory::WriteArrayUnsafe(address + 4, nil_vector, 12);
	return IntVector{ address };
}

void PVZ::IntVector::Free()
{
	PVZ::Memory::Execute(AsmBuilder()
		.mov_reg_imm(REG_ESI, this->GetBaseAddress())
		.invoke(0x541590)
		.ret()
	);
	PVZ::Memory::FreeMemory(this->GetBaseAddress());
}

bool PVZ::IntVector::is_empty()
{
	return this->size() == 0;
}

size_t PVZ::IntVector::size()
{
	return this->First == 0 ? 0 : (this->Last - this->First) >> 2;
}

void PVZ::IntVector::push_back(int val)
{
	PVZ::Memory::WriteMemoryUnsafe<int>(PVZ::Memory::Variable, val);
	PVZ::Memory::Execute(AsmBuilder()
		.mov_reg_imm(REG_EBX, PVZ::Memory::Variable)
		.mov_reg_imm(REG_ESI, this->GetBaseAddress())
		.invoke(0x5415C0)
		.ret()
	);
}

void PVZ::IntVector::pop_back()
{
	if (this->First)
		if (this->Last)
			PVZ::Memory::WriteMemoryUnsafe<int>(this->GetBaseAddress() + 8, this->Last - 4);
}

int PVZ::IntVector::get(int index)
{
	return PVZ::Memory::ReadMemory<int>(this->First + (index << 2));
}

int PVZ::IntVector::operator[](int index)
{
	return PVZ::Memory::Execute(AsmBuilder()
		.mov_reg_imm(REG_EBX, PVZ::Memory::Variable)
		.mov_reg_imm(REG_ESI, this->GetBaseAddress())
		.invoke(0x541960)
		.mov_mem_reg(PVZ::Memory::Variable, REG_EAX)
		.ret()
	);
}

void PVZ::IntVector::resize(int count)
{
	PVZ::Memory::Execute(AsmBuilder()
		.push_imm32(count)
		.mov_reg_imm(REG_EAX, this->GetBaseAddress())
		.invoke(0x59C2C0)
		.ret()
	);
}
