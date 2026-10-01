#pragma once
#include "DLLEvent.h"

/// @brief 植物射击事件
/// @param 触发事件的植物
class PlantShootEvent : public DLLEventTemplate<0x466E0D, 6, REG_EBP>
{
public:
	PlantShootEvent(const char* str) : DLLEventTemplate() { Init(str); };
	PlantShootEvent(int address) : DLLEventTemplate() { Init(address); };
	PlantShootEvent() : PlantShootEvent("onPlantShoot") {};
};

namespace PVZEvent
{
	/// @brief 植物射击完成时，恢复闲置动作事件。
	/// @param 触发事件的植物
	/// @return 是否处理植物独特外观的动作。
	/// @retval false 只处理身体部分的动作。
	class PlantShootingCompleteEvent : public BoolDLLEventTemplate<0x46495F, 5, 0x464D75, REG_EDI>
	{
	public:
		PlantShootingCompleteEvent() : BoolDLLEventTemplate() { Init("onPlantShootingComplete"); };
		PlantShootingCompleteEvent(const char* str) : BoolDLLEventTemplate() { Init(str); };
		PlantShootingCompleteEvent(int address) : BoolDLLEventTemplate() { Init(address); };
	};
}