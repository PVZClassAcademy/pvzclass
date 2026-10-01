#pragma once
#include "DLLEvent.h"

namespace PVZEvent
{
	/// @brief 子弹绘制贴图变换矩阵后事件
	/// @param Matrix3
	class ProjectileDrawTransEvent : public DLLEventTemplate<0x46E7FB, 6, REG_ESI>
	{
	public:
		ProjectileDrawTransEvent(const char* str) : DLLEventTemplate() { Init(str); };
		ProjectileDrawTransEvent(int address) : DLLEventTemplate() { Init(address); };
		ProjectileDrawTransEvent() : ProjectileDrawTransEvent("onProjectileDrawTrans") {};
	};

	/// @brief 子弹绘制颜色事件
	/// @note 旋转角度为 0 且缩放大小为 1 的子弹不会触发这个事件。
	/// @param 触发事件的子弹
	/// @return 颜色的内存地址。若超出有符号 32 位整数的范围，则不改变颜色。
	class ProjectileColorEvent : public DLLEvent
	{
	public:
		ProjectileColorEvent(int address)
		{
			hookAddress = 0x46E805;
			rawlen = 5;
			BYTE code[] =
			{
				PUSH_PTR_EUX_ADD_V(REG_EBP, 8),
				INVOKE(address),
				ADD_ESP(4),

				TEST_EUX_EVX(REG_EAX, REG_EAX),
				JS(20),
				MOV_PTR_ESP_ADD_V_EUX(REG_EAX, 0x1C),
				MOV_PTR_ESP_ADD_V(0x20, 1),
				POPAD,
				PUSH_EAX,
				PUSHDWORD(0x46E80A),
				RET,
			};
			start(STRING(code));
		}
		ProjectileColorEvent(const char* str) : ProjectileColorEvent(PVZ::Memory::GetProcAddress(str)) {};
		ProjectileColorEvent() : ProjectileColorEvent("GetProjectileColor") {};
	};
}