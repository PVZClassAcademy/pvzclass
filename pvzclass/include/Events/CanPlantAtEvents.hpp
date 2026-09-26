#pragma once
#include "DLLEvent.h"

namespace PVZEvent
{
	/// @brief 重载蹦极僵尸卡种植条件事件
	/// @param 触发事件的行数、列数，本关放置其他僵尸的最左列数
	/// @return 是否可以种植
	class BungeeCanPlantAtEvent : public DiversionEventTemplate<0x4255E6, 5, 0x425683, 0x425669, REG_ECX, REG_EBX, REG_EDI>
	{
	public:
		BungeeCanPlantAtEvent(const char* str) : DiversionEventTemplate() { Init(str); };
		BungeeCanPlantAtEvent(int address) : DiversionEventTemplate() { Init(address); };
		BungeeCanPlantAtEvent() : BungeeCanPlantAtEvent("IsBungeeCanPlantAt") {};
	};

	/// @brief 判断卡牌类型在关卡中是否可以放置的事件
	/// @param 触发事件的 Challenge，检查的行数，检查的列数，卡牌类型
	/// @note 若返回值不为 PLANTING_OK，则会终止后续判定。
	/// @return 若为负数，使用原版规则进行判定；否则为卡牌是否可用，以及不可用的理由。
	class ChallengeCanPlantAtEvent_ts : public ThreeStateEventTemplate<0x425550, 5, 0x425591, 0x425591, MEM_ESP_ADD(0x24), REG_EBX, REG_EDI, REG_ECX>
	{
	public:
		ChallengeCanPlantAtEvent_ts(const char* str) : ThreeStateEventTemplate() { Init(str); };
		ChallengeCanPlantAtEvent_ts(int address) : ThreeStateEventTemplate() { Init(address); };
		ChallengeCanPlantAtEvent_ts() : ChallengeCanPlantAtEvent_ts("IsChallengeCanPlantAt") {};
	};
}
