#pragma once
#include "DLLEvent.h"

/// @brief Coin创建事件
/// @param 触发事件的Coin
class CoinCreateEvent : public DLLEventTemplate<0x40CCCE, 8, REG_EAX>
{
public:
	CoinCreateEvent() : CoinCreateEvent("onCoinCreate") {};
	CoinCreateEvent(const char* str) : DLLEventTemplate() { Init(str); };
	CoinCreateEvent(int address) : DLLEventTemplate() { Init(address); };
};

namespace PVZEvent
{
	/// @brief Coin 初始化完毕事件
	/// @note 触发事件的 Coin
	class CoinInitAfterEvent : public DLLEventTemplate<0x43093C, 7, REG_EBP>
	{
	public:
		CoinInitAfterEvent() : DLLEventTemplate() { Init("onCoinInitAfter"); };
		CoinInitAfterEvent(const char* str) : DLLEventTemplate() { Init(str); };
		CoinInitAfterEvent(int address) : DLLEventTemplate() { Init(address); };
	};
}