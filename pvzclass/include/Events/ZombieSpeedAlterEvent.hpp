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
	/// @brief 判断僵尸是否不走动的事件
	/// @param 触发事件的僵尸
	/// @return 以 ThreeState::ThreeState 表示的，僵尸是否不走动
	class ZombieNotWalkingEvent_ts : public ThreeStateEventTemplate<0x52A611, 6, 0x52A7A4, 0x52A79A, REG_EAX>
	{
	public:
		ZombieNotWalkingEvent_ts(const char* str) : ThreeStateEventTemplate() { Init(str); };
		ZombieNotWalkingEvent_ts(int address) : ThreeStateEventTemplate() { Init(address); };
		ZombieNotWalkingEvent_ts() : ThreeStateEventTemplate() { Init("IsZombieNotWalking"); };
	};
}
