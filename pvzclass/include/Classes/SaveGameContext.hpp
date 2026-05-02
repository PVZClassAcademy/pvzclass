#pragma once
#include "../PVZ.h"

namespace PVZ
{
	class SaveGameContext : public BaseClass
	{
	public:
		SaveGameContext(uint32_t address) : PVZ::BaseClass(address) {};

		T_READONLY_PROPERTY(bool, Failed, __get_Failed, 0x20);
		T_READONLY_PROPERTY(bool, Reading, __get_Reading, 0x21);
	};
}