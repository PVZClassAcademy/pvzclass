#pragma once
#include "DLLEvent.h"

/// @brief 磁力菇主动更新时, 吸铁器事件
/// @param 触发事件的植物，僵尸
/// @return false则跳过吸取
class MagnetAttactItemAbilityEvent : public BoolDLLEventTemplate<0x4621AE, 5, 0x4621B3, REG_EBX, REG_EAX>
{
public:
	MagnetAttactItemAbilityEvent(const char* str) : BoolDLLEventTemplate() { Init(str); };
	MagnetAttactItemAbilityEvent(int address) : BoolDLLEventTemplate() { Init(address); };
	MagnetAttactItemAbilityEvent() : BoolDLLEventTemplate() { Init("MagnetAttactItemAbilityEvent"); };
};