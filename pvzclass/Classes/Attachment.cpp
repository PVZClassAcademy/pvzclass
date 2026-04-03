#include "../PVZ.h"

PVZ::Attachment PVZ::Attachment::GetByIndex(uint32_t index)
{
	return PVZ::Attachment(Memory::ReadPointer(0x6A9EC0, 0x820, 0xC, 0) + index * 0x30C);
}

PVZ::AttachEffect PVZ::Attachment::GetEffect(int index)
{
	return AttachEffect(this->GetBaseAddress() + index * 0x30);
}