#pragma once
#include "DLLEvent.h"

namespace PVZEvent {
	/// @brief 磁力菇主动更新时, 吸铁器事件
	/// @param 触发事件的植物，僵尸
	/// @return false则跳过吸取
	class MagnetShroomAttractAbilityEvent : public BoolDLLEventTemplate<0x4621AE, 5, 0x4621B3, REG_EBX, REG_EAX>
	{
	public:
		MagnetShroomAttractAbilityEvent(const char* str) : BoolDLLEventTemplate() { Init(str); };
		MagnetShroomAttractAbilityEvent(int address) : BoolDLLEventTemplate() { Init(address); };
		MagnetShroomAttractAbilityEvent() : BoolDLLEventTemplate() { Init("onMagnetShroomAttractAbility"); };
	};
}
