#pragma once
#include "DLLEvent.h"

namespace PVZEvent
{
	/// @brief 子弹位移结算事件
	/// @param 触发事件的子弹
	/// @return 是否进行位移
	class ProjUpdateMotionEvent : public BoolDLLEventTemplate<0x46DCAD, 5, 0x46DCC0, REG_ESI>
	{
	public:
		ProjUpdateMotionEvent(int address) : BoolDLLEventTemplate() { Init(address); };
		ProjUpdateMotionEvent(const char* name) : BoolDLLEventTemplate() { Init(name); };
		ProjUpdateMotionEvent() : ProjUpdateMotionEvent("onProjectileUpdateMotion") {};
	};

	/// @brief 检查子弹是否应该过期事件
	/// @note 构造后，原版的判定条件会失效
	/// @param 触发事件的子弹
	/// @return 子弹是否过期
	class ProjCheckExpireEvent : public DiversionEventTemplate<0x46CE91, 6, 0x46D047, 0x46CE9D, REG_EBP>
	{
	public:
		ProjCheckExpireEvent(const char* str) : DiversionEventTemplate() { Init(str); };
		ProjCheckExpireEvent(int address) : DiversionEventTemplate() { Init(address); };
		ProjCheckExpireEvent() : ProjCheckExpireEvent("onProjectileCheckExpire") {};
	};
}
