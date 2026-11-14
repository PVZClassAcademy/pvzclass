#pragma once
#include "DLLEvent.h"

/// @brief Coin消失事件
/// @param 消失的Coin
/// @note Coin消失原因很多：被收集后、时间到了等都会使其消失
class CoinRemoveEvent : public DLLEventTemplate<0x432DD0, 7, REG_ESI>
{
public:
	CoinRemoveEvent() : CoinRemoveEvent("onCoinRemove") {};
	CoinRemoveEvent(const char* str) : DLLEventTemplate() { Init(str); };
	CoinRemoveEvent(int address) : DLLEventTemplate() { Init(address); };
};

namespace PVZEvent
{
	/// @brief 获取 Coin 消失前持续时长的事件
	/// @param 触发事件的 Coin
	class GetCoinDisappearTimeEvent : public IntDLLEventTemplate<0x433050, 7, 0, 0, 0, REG_EAX, true, REG_ECX>
	{
	public:
		GetCoinDisappearTimeEvent() : GetCoinDisappearTimeEvent("GetCoinDisappearTime") {};
		GetCoinDisappearTimeEvent(const char* str) : IntDLLEventTemplate() { Init(str); };
		GetCoinDisappearTimeEvent(int address) : IntDLLEventTemplate() { Init(address); };
	};
}
