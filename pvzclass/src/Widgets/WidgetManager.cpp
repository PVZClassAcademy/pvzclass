#include "Widgets/WidgetManager.hpp"

void PVZ::WidgetManager::GameClick(int x, int y)
{
	SETARG(__asm__GameClick, 1) = this->GetBaseAddress();
	SETARG(__asm__GameClick, 6) = y;
	SETARG(__asm__GameClick, 16) = x;
	Memory::Execute(STRING(__asm__GameClick));
}

PVZ::WidgetManager PVZ::GetWidgetManager()
{
	return PVZ::WidgetManager(PVZ::Memory::ReadPointer(0x6A9EC0, 0x320));
}