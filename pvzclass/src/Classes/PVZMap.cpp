#include "Classes/PVZMap.hpp"

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

	return StringStringMap{ address	};
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
