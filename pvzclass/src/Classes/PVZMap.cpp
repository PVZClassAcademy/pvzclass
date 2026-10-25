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
