#pragma once
#include "DLLEvent.h"

namespace PVZEvent
{
	/// @brief 判断指定行能否出指定类型僵尸时触发的事件
	/// @param 触发事件的 Board，判定的行，僵尸类型
	/// @return 以 ThreeState::ThreeState 表示的，本行是否能出僵尸
	class IsRowCanHaveZombieTypeEvent_ts : public ThreeStateEventTemplate<0x40DB21, 7, 0x40DC41, 0x40DB4E, 0x2C, 0x2C, REG_ESI>
	{
	public:
		IsRowCanHaveZombieTypeEvent_ts(const char* str) : ThreeStateEventTemplate() { Init(str); };
		IsRowCanHaveZombieTypeEvent_ts(int address) : ThreeStateEventTemplate() { Init(address); };
		IsRowCanHaveZombieTypeEvent_ts(int address) : ThreeStateEventTemplate() { Init("IsRowCanHaveZombieType"); };
	};
}
