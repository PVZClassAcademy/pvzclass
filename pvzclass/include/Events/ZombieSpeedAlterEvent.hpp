#pragma once
#include "DLLEvent.h"

namespace PVZEvent
{
	/// @brief 僵尸动画速度随 buff 改变事件
	/// @param 触发事件的僵尸，僵尸的基础动画速度
	/// @return 调整后的僵尸动画速度
	class ZombieSpeedAlterEvent : public DLLEvent
	{
	public:
		ZombieSpeedAlterEvent(int address)
		{
			hookAddress = 0x52F219;
			rawlen = 5;
			BYTE code[] =
			{
				PUSH_PTR_ESP_ADD_V(0x20),
				PUSH_ESI,
				INVOKE(address),
				ADD_ESP(8),
				FSTP_PTR_ESP_ADD_V(0x20),
			};
			start(STRING(code));
		}
		ZombieSpeedAlterEvent(const char* str) : ZombieSpeedAlterEvent(PVZ::Memory::GetProcAddress(str)) {};
		ZombieSpeedAlterEvent() : ZombieSpeedAlterEvent("CalcZombieSpeedAlter") {};
	};

	/// @brief 僵尸位移距离事件
	/// @param 触发事件的僵尸，僵尸的基础位移
	/// @return 调整后的僵尸移动距离
	class ZombieWalkDistEvent : public FloatDLLEventTemplate<0x52AB18, 5, 0x28, false, 0x28, REG_ESI>
	{
	public:
		ZombieWalkDistEvent(const char* str) : FloatDLLEventTemplate() { Init(str); };
		ZombieWalkDistEvent(int address) : FloatDLLEventTemplate() { Init(address); };
		ZombieWalkDistEvent() : FloatDLLEventTemplate() { Init("GetZombieWalkDist"); };
	};
}
