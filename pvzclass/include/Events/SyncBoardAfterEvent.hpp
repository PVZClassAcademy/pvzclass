#pragma once
#include "DLLEvent.h"

namespace PVZEvent
{
	/// @brief Board 存读档完成事件
	/// @param 触发事件的 Board，触发事件的存档上下文
	/// @note 在此期间调用存档上下文的函数会导致存档文件与原版不兼容。
	/// @see PVZ::SaveGameContext
	class SyncBoardAfterEvent : public DLLEventTemplate<0x481C57, 5, REG_ECX, REG_EBP>
	{
	public:
		SyncBoardAfterEvent(int address) : DLLEventTemplate() { Init(address); };
		SyncBoardAfterEvent(const char* name) : DLLEventTemplate() { Init(name); };
		SyncBoardAfterEvent() : SyncBoardAfterEvent("onSyncBoardAfter") {};
	};
}
