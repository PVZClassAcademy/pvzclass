#include "GameObject.hpp"

DWORD PVZ::Projectile::MemSize = 0x94;

PVZ::Projectile PVZ::Projectile::GetByIndex(uint32_t index)
{
	return PVZ::Projectile(Memory::ReadMemory<int>(PVZBASEADDRESS + 0x0C8) + index * MemSize);
}
byte __asm__Projectile_CheckForCollision[]
{
	PUSHDWORD(0),
	INVOKE(0x46CE80),
	RET,
};
void PVZ::Projectile::CheckForCollision()
{
	SETARG(__asm__Projectile_CheckForCollision, 1) = this->GetBaseAddress();
	Memory::Execute(__asm__Projectile_CheckForCollision, 19);
}

void PVZ::Projectile::ConvertToPea(int column)
{
	PVZ::Memory::Execute(AsmBuilder()
		.mov_reg_imm(REG_EBX, column)
		.mov_reg_imm(REG_EAX, this->BaseAddress)
		.invoke(0x46EE00)
		.ret()
	);
}

void PVZ::Projectile::DoImpact(PVZ::Zombie zombie)
{
	PVZ::Memory::Execute(AsmBuilder()
		.mov_reg_imm(REG_EAX, zombie.GetBaseAddress())
		.mov_reg_imm(REG_ECX, this->BaseAddress)
		.invoke(0x46E000)
		.ret()
	);
}

void PVZ::Projectile::DoSplashDamage(PVZ::Zombie zombie)
{
	PVZ::Memory::Execute(AsmBuilder()
		.push_imm32(zombie.GetBaseAddress())
		.mov_reg_imm(REG_EAX, this->BaseAddress)
		.invoke(0x46D390)
		.ret()
	);
}

byte __asm__Projectile_GetProjectileRect[]
{
	MOV_ECX(0),
	MOV_ESI(0),
	INVOKE(0x46EBC0),
	RET,
};

PVZ::Rect PVZ::Projectile::GetProjectileRect()
{
	SETARG(__asm__Projectile_GetProjectileRect, 1) = PVZ::Memory::Variable;
	SETARG(__asm__Projectile_GetProjectileRect, 6) = this->GetBaseAddress();
	Memory::Execute(__asm__Projectile_GetProjectileRect, 24);
	return Rect
	{
		PVZ::Memory::ReadMemory<int>(PVZ::Memory::Variable),
		PVZ::Memory::ReadMemory<int>(PVZ::Memory::Variable + 4),
		PVZ::Memory::ReadMemory<int>(PVZ::Memory::Variable + 8),
		PVZ::Memory::ReadMemory<int>(PVZ::Memory::Variable + 12)
	};
}
byte __asm__OnFire[]
{
	MOV_ECX(0),
	ONFIRE,
	RET,
};

void PVZ::Projectile::OnFire()
{
	SETARG(__asm__OnFire, 1) = BaseAddress;
	Memory::Execute(STRING(__asm__OnFire));
}

byte __asm__Projectile__Remove[]
{
	MOV_EAX(0),
	PROJECTILE_REMOVE,
	RET
};

void PVZ::Projectile::Remove()
{
	SETARG(__asm__Projectile__Remove, 1) = BaseAddress;
	Memory::Execute(STRING(__asm__Projectile__Remove));
	return;
}
