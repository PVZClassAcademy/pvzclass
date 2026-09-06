#pragma once
#include "DLLEvent.h"

namespace PVZEvent
{
	/// @brief PlayerInfo 重置完成事件
	/// @param 触发事件的 PlayerInfo
	/// @note PlayerInfo 在创建时会进行重置，因此也会触发该事件。
	/// @return 是否使用原版的描述文本
	class PlayerInfoResetAfterEvent : public DLLEventTemplate<0x469A55, 5, REG_ESI>
	{
	public:
		PlayerInfoResetAfterEvent(int address) : DLLEventTemplate() { Init(address); };
		PlayerInfoResetAfterEvent(const char* name) : DLLEventTemplate() { Init(name); };
		PlayerInfoResetAfterEvent() : PlayerInfoResetAfterEvent("onPlayerInfoResetAfter") {};
	};
}
