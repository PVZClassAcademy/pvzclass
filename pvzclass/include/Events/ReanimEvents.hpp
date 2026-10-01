#pragma once
#include "DLLEvent.h"

namespace PVZEvent
{
	/// @brief 动画制图时，初始化动画事件
	/// @param 触发事件的动画
	class ReanimCacheDrawFrameEvent : public DLLEventTemplate<0x46F1C1, 5, REG_EBX>
	{
	public:
		ReanimCacheDrawFrameEvent() : DLLEventTemplate() { Init("onReanimCacheDrawFrame"); };
		ReanimCacheDrawFrameEvent(const char* str) : DLLEventTemplate() { Init(str); };
		ReanimCacheDrawFrameEvent(int address) : DLLEventTemplate() { Init(address); };
	};
}