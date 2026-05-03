#include "Global.hpp"

PVZ::Image PVZ::Resource::IMAGE_BLANK{ 0 };

// 在使用 Resource 类的静态成员前，应当先调用此函数。
void PVZ::Resource::InitImages()
{
	PVZ::Resource::IMAGE_BLANK = PVZ::Image(PVZ::Memory::ReadMemory<DWORD>(0x6A77BC));
}