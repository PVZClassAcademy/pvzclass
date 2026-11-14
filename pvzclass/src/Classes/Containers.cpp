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

const uint8_t _bytes[]{
	MOV_PTR_EUX_ADD_V_EVX(REG_ESI, REG_EAX, 4),
	MOV_BYTE_PTR_EUX_ADD_V_V(REG_EAX, 0x45, 1),
	MOV_PTR_EUX_ADD_V_EVX(REG_EAX, REG_EAX, 0),
	MOV_PTR_EUX_ADD_V_EVX(REG_EAX, REG_EAX, 4),
	MOV_PTR_EUX_ADD_V_EVX(REG_EAX, REG_EAX, 8),
	MOV_PTR_EUX_ADD_V(REG_ESI, 8, 0)
};

PVZ::StringStringMap PVZ::StringStringMap::Make()
{
	uint32_t address = PVZ::Memory::AllocMemoryUnsafe(0, 0x0C);

	PVZ::Memory::Execute(AsmBuilder()
		.mov_reg_imm(REG_ESI, address)

		.invoke(0x444F50)
		.add_bytes(STRING(_bytes))

		.ret()
	);

	return StringStringMap{ address };
}

void PVZ::StringStringMap::Free()
{
	PVZ::Memory::Execute(AsmBuilder()
		.mov_reg_imm(REG_EAX, this->BaseAddress)
		.invoke(0x444B20)
		.ret()
	);
	PVZ::Memory::FreeMemory(this->BaseAddress);
}

bool PVZ::StringStringMap::Insert(PVZString key, PVZString value)
{
	return PVZ::Memory::Execute(AsmBuilder()
		.sub_reg_imm(REG_ESP, 0x0A4)
		.mov_reg_reg(REG_EDI, REG_ESP)

		.push_reg(REG_EDI)
		.invoke(0x4439F0)

		.mov_reg_mem_reg_add_imm32(REG_EAX, REG_EDI, 0x78)
		.push_reg(REG_EAX)
		.mov_mem_reg_add_imm8_imm32(REG_EDI, 0x78, PVZ::Memory::ReadMemory<uint32_t>(this->GetBaseAddress() + 4))

		.push_imm32(value.GetBaseAddress())
		.mov_reg_imm(REG_ECX, key.GetBaseAddress())
		.push_reg(REG_EDI)
		.invoke(0x5A19D0)
		.mov_mem_reg(PVZ::Memory::Variable, REG_EAX)

		.pop(REG_EAX)
		.mov_mem_reg_add_imm8_reg(REG_EDI, 0x78, REG_EAX)
		.push_reg(REG_EDI)
		.invoke(0x443AE0)

		.add_reg_imm(REG_ESP, 0x0A4)
		.ret()
	) & 0xFF;
}

PVZ::PVZString PVZ::Evaluate(PVZString str, StringStringMap def_map)
{
	auto result = PVZ::PVZString::Make("");

	PVZ::Memory::Execute(AsmBuilder()
		.mov_reg_imm(REG_ECX, def_map.GetBaseAddress())
		.push_imm32(str.GetBaseAddress())
		.push_imm32(result.GetBaseAddress())
		.invoke(0x5B0CC0)
		.add_reg_imm(REG_ESP, 8)
		.ret()
	);

	return result;
}
