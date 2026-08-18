#include "Classes/GameObject.hpp"

DWORD PVZ::Coin::MemSize = 0x0D8;

PVZ::Coin PVZ::Coin::GetByIndex(uint32_t index)
{
    return PVZ::Coin(Memory::ReadMemory<uint32_t>(PVZBASEADDRESS + 0x0E4) + index * MemSize);
}

void PVZ::Coin::GetCollision(PVZ::Rect* collbox)
{
	collbox->X = NULL;
	collbox->Y = NULL;
	collbox->Width = Memory::ReadMemory<int>(BaseAddress + 0x10);
	collbox->Height = Memory::ReadMemory<int>(BaseAddress + 0x14);
}

void PVZ::Coin::SetCollision(PVZ::Rect* collbox)
{
	Memory::WriteMemoryUnsafe<int>(BaseAddress + 0x10, collbox->Width);
	Memory::WriteMemoryUnsafe<int>(BaseAddress + 0x14, collbox->Height);
}

PVZ::Attachment PVZ::Coin::GetAttachment()
{
	int ID = Memory::ReadMemory<int>(BaseAddress + 0x60);
	return (((ID & 0xFFFF0000) == 0) ? INVALID_BASEADDRESS : Attachment::GetByIndex(ID & 0x00FFFF));
}

PVZ::GardenPlant PVZ::Coin::GetGardenPlant()
{
	return PVZ::GardenPlant(this->BaseAddress + 0x68);
}

void PVZ::Coin::Collect()
{
	SETARG(__asm__Collect, 1) = BaseAddress;
	Memory::Execute(STRING(__asm__Collect));
}

byte __asm__Coin_die[] =
{
	MOV_ESI(0),
	INVOKE(0x432DD0),
	RET
};

void PVZ::Coin::Die()
{
	SETARG(__asm__Coin_die, 1) = BaseAddress;
	Memory::Execute(STRING(__asm__Coin_die));
}

bool PVZ::Coin::CoinGetsBouncyArrow()
{
	return PVZ::Memory::Execute(AsmBuilder()
		.mov_reg_imm(REG_ECX, this->BaseAddress)
		.invoke(0x432FE0)
		.mov_mem_reg(PVZ::Memory::Variable, REG_EAX)
		.ret()
	) & 0x0FF;
}

void PVZ::Coin::FanOutCoins(CoinType::CoinType type, int count)
{
	PVZ::Memory::Execute(AsmBuilder()
		.push_imm32(count)
		.push_imm32(type)
		.mov_reg_imm(REG_EDI, this->BaseAddress)
		.invoke(0x431F30)
		.ret()
	);
}

PVZ::Color PVZ::Coin::GetColor()
{
	PVZ::Memory::Execute(AsmBuilder()
		.mov_reg_imm(REG_ESI, PVZ::Memory::Variable)
		.mov_reg_imm(REG_ECX, this->GetBaseAddress())
		.invoke(0x4316F0)
		.ret()
	);

	return Color{ PVZ::Memory::ReadMemory<int>(PVZ::Memory::Variable), PVZ::Memory::ReadMemory<int>(PVZ::Memory::Variable + 4),
		PVZ::Memory::ReadMemory<int>(PVZ::Memory::Variable + 8), PVZ::Memory::ReadMemory<int>(PVZ::Memory::Variable + 12) };
}

bool PVZ::Coin::GetDisappearTime()
{
	return PVZ::Memory::Execute(AsmBuilder()
		.mov_reg_imm(REG_ECX, this->BaseAddress)
		.invoke(0x433050)
		.mov_mem_reg(PVZ::Memory::Variable, REG_EAX)
		.ret()
	) & 0x0FF;
}

SeedType::SeedType PVZ::Coin::GetFinalSeedPacketType()
{
	return SeedType::SeedType(PVZ::Memory::Execute(AsmBuilder()
		.mov_reg_imm(REG_ECX, this->BaseAddress)
		.invoke(0x4317D0)
		.mov_mem_reg(PVZ::Memory::Variable, REG_EAX)
		.ret()
	));
}

bool PVZ::Coin::MouseHitTest(int X, int Y)
{
	return PVZ::Memory::Execute(AsmBuilder()
		.push_imm32(PVZ::Memory::Variable)
		.push_imm32(Y)
		.push_imm32(X)
		.mov_reg_imm(REG_EDX, this->BaseAddress)
		.invoke(0x432E20)
		.mov_mem_reg(PVZ::Memory::Variable, REG_EAX)
		.ret()
	) & 0x0FF;
}

bool PVZ::Coin::IsLevelAward()
{
	return PVZ::Memory::Execute(AsmBuilder()
		.mov_reg_imm(REG_EAX, this->BaseAddress)
		.invoke(0x432F80)
		.mov_mem_reg(PVZ::Memory::Variable, REG_EAX)
		.ret()
	) & 0x0FF;
}

void PVZ::Coin::ScoreCoin()
{
	PVZ::Memory::Execute(AsmBuilder()
		.mov_reg_imm(REG_EAX, this->BaseAddress)
		.invoke(0x4309D0)
		.ret()
	);
}

void PVZ::Coin::TryAutoCollect()
{
	PVZ::Memory::Execute(AsmBuilder()
		.mov_reg_imm(REG_ESI, this->BaseAddress)
		.invoke(0x432000)
		.ret()
	);
}
