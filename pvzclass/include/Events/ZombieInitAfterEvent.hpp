#pragma once
#include "DLLEvent.h"

/// @brief 僵尸初始化完成事件
/// @param 初始化的 Zombie 的基址。
class ZombieInitAfterEvent : public DLLEventTemplate<0x524035, 5, REG_EDI>
{
public:
	ZombieInitAfterEvent(const char* str) : DLLEventTemplate() { Init(str); };
	ZombieInitAfterEvent(int address) : DLLEventTemplate() { Init(address); };
	ZombieInitAfterEvent() : DLLEventTemplate() { Init("onZombieInitAfter"); };
};

namespace PVZEvent
{
	/// @brief 僵尸初始化时，获取动画类型事件
	/// @param 触发事件的僵尸，默认动画类型
	/// @return 重载后的动画类型
	class ZombieGetReanimTypeEvent : public DLLEventTemplate<0x5227C6, 10, REG_EAX, REG_EDI>
	{
	public:
		ZombieGetReanimTypeEvent(const char* str) : DLLEventTemplate() { Init(str); };
		ZombieGetReanimTypeEvent(int address) : DLLEventTemplate() { Init(address); };
		ZombieGetReanimTypeEvent() : DLLEventTemplate() { Init("GetZombieReanimType"); };
		virtual void InitExtra(AsmBuilder& builder)
		{
			builder.mov_mem_esp_add_imm8_reg(0x1C - (REG_EAX << 2), REG_EAX);
		}
	};
}