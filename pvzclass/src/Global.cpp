#include "Global.hpp"

PVZ::Image PVZ::Resource::IMAGE_BLANK{ 0 };

// 在使用 Resource 类的静态成员前，应当先调用此函数。
void PVZ::Resource::InitImages()
{
	PVZ::Resource::IMAGE_BLANK = PVZ::Image(PVZ::Memory::ReadMemory<DWORD>(0x6A77BC));
}

void PVZ::Resource::LoadStringList(const char* str)
{
	PVZ::Memory::WriteArrayUnsafe<const char>(PVZ::Memory::StringVariable, str, std::strlen(str) + 1);

	PVZ::Memory::WriteMemory<uint32_t>(0x518DEB, PVZ::Memory::StringVariable);
	PVZ::Memory::WriteMemory<uint32_t>(0x518DF9, PVZ::Memory::StringVariable);
	PVZ::Memory::WriteMemory<uint32_t>(0x51939E, PVZ::Memory::StringVariable);

	PVZ::Memory::Execute(AsmBuilder()
		.invoke(0x519390)
		.ret()
	);

	PVZ::Memory::WriteMemory<uint32_t>(0x518DEB, 0x667798);
	PVZ::Memory::WriteMemory<uint32_t>(0x518DF9, 0x667798);
	PVZ::Memory::WriteMemory<uint32_t>(0x51939E, 0x667798);
}
