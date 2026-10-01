#pragma once
#include "DLLEvent.h"

namespace PVZEvent
{
	/// @brief 绘制场地物品事件
	/// @param 依次为：场地物品，Graphics
	/// @note 时机上先于原版绘制
	class DrawGriditemEvent : public DLLEventTemplate<0x44D14B, 5, REG_ECX, REG_EDX>
	{
	public:
		DrawGriditemEvent(const char* str) : DLLEventTemplate() { Init(str); };
		DrawGriditemEvent(int address) : DLLEventTemplate() { Init(address); };
		DrawGriditemEvent() : DLLEventTemplate() { Init("onDrawGriditem"); };
	};

	/// @brief 重载僵尸绘制位置事件
	/// @note 此时已经完成了除 BodyY 和 ClipRect 的所有量的设定
	/// @param 触发事件的僵尸，僵尸的 ZombieDrawPos
	/// @return 是否执行原版对 BodyY 和 ClipRect 的设定
	class ZombieOverrideDrawPosEvent : BoolDLLEventTemplate<0x52DBAC, 6, 0x52DF89, REG_ESI, REG_ECX>
	{
	public:
		ZombieOverrideDrawPosEvent() : BoolDLLEventTemplate() { Init("OverrideZombieDrawPos"); };
		ZombieOverrideDrawPosEvent(const char* str) : BoolDLLEventTemplate() { Init(str); };
		ZombieOverrideDrawPosEvent(int address) : BoolDLLEventTemplate() { Init(address); };
	};
}