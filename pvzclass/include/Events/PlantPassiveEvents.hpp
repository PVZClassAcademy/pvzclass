#pragma once
#include "DLLEvent.h"

namespace PVZEvent
{
	/// @brief 判断植物是否具有保护伞防护效果的事件
	/// @param 触发事件的植物，检查的行数，检查的列数
	/// @return 若为负数，与原版一致；若为 0，则无效果；若为是，则有效果，且返回值应当为该植物的基址。
	class CheckUmbrellaEvent_ts : public ThreeStateEventTemplate<0x41D3F0, 8, 0x41D446, 0x41D437, REG_EBX, REG_EDI, MEM_ESP_ADD(0x2C)>
	{
	public:
		CheckUmbrellaEvent_ts(const char* str) : ThreeStateEventTemplate() { Init(str); };
		CheckUmbrellaEvent_ts(int address) : ThreeStateEventTemplate() { Init(address); };
		CheckUmbrellaEvent_ts() : CheckUmbrellaEvent_ts("IsUmbrellaPlant") {};
	};
}
