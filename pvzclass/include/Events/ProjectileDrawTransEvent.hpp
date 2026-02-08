#pragma once
#include "DLLEvent.h"

namespace PVZEvent
{
	/// @brief 子弹绘制贴图变换矩阵后事件
	/// @param Matrix3
	class ProjectileDrawTransEvent : public DLLEventTemplate<0x46E7F6, 5, REG_ESI>
	{
	public:
		ProjectileDrawTransEvent(const char* str) : DLLEventTemplate() { Init(str); };
		ProjectileDrawTransEvent(int address) : DLLEventTemplate() { Init(address); };
		ProjectileDrawTransEvent() : ProjectileDrawTransEvent("onProjectileDrawTrans") {};
	};
}