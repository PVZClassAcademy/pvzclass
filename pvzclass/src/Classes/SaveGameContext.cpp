#include "Classes/SaveGameContext.hpp"

PVZ::SaveGameContext PVZ::SaveGameContext::Make()
{
	// Buffer是0x20byte，后面还有2byte的bool，保险起见留0x30byte
	int address = PVZ::Memory::AllocMemory(0, 0x30);
	PVZ::Memory::Execute(AsmBuilder()
		.mov_reg_imm(REG_EAX, address)
		.invoke(0x5D60A0)
		.ret()
	);
	return address;
}

void PVZ::SaveGameContext::Free()
{
	PVZ::Memory::Execute(AsmBuilder()
		.mov_reg_imm(REG_ECX, GetBaseAddress())
		.invoke(0x4820C0)
		.ret()
	);
}

int PVZ::SaveGameContext::Read(char* buf, int buflen)
{
	int address = PVZ::Memory::Execute(AsmBuilder()
		.mov_reg_imm(REG_ESI, GetBaseAddress())
		.invoke(0x5D6990)
		.mov_mem_reg(PVZ::Memory::Variable, REG_EAX)
		.ret()
	);
	int buflen = PVZ::Memory::Execute(AsmBuilder()
		.mov_reg_imm(REG_EAX, GetBaseAddress())
		.invoke(0x5D69C0)
		.mov_mem_reg(PVZ::Memory::Variable, REG_EAX)
		.ret()
	);
	if (PVZ::Memory::localExecute) buf = (char*)address;
	else PVZ::Memory::ReadArray<char>(address, buf, buflen);
	return buflen;
}

void PVZ::SaveGameContext::Write(char* buf, int buflen)
{
	int address = 0;
	if (PVZ::Memory::localExecute)
	{
		address = (int)buf;
	}
	else
	{
		address = PVZ::Memory::AllocMemory(0, buflen);
		PVZ::Memory::WriteArrayUnsafe<char>(address, buf, buflen);
	}
	PVZ::Memory::Execute(AsmBuilder()
		.push(buflen)
		.push(address)
		.push(GetBaseAddress())
		.invoke(0x5D6560)
		.ret()
	);
}

void PVZ::SaveGameContext::SyncBoard(Board board, bool read)
{
	this->Failed = false;
	this->Reading = read;
	PVZ::Memory::Execute(AsmBuilder()
		.push(board.GetBaseAddress())
		.mov_reg_imm(REG_EAX, BaseAddress)
		.invoke(0x4819D0)
		.add_reg_imm(REG_ESP, 4)
		.ret()
	);
	if (read)
	{
		PVZ::Memory::Execute(AsmBuilder()
			.mov_reg_imm(REG_EDI, board.GetBaseAddress())
			.invoke(0x481CE0)
			.ret()
		);
		PVZ::GetPVZApp().GameState = PVZGameState::Playing;
	}
}
