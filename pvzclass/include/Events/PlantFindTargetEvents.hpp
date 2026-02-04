#pragma once
#include "DLLEvent.h"

namespace PVZEvent
{
	/// @brief 植物索敌僵尸事件
	/// @note 该事件只重载行差判定和类型判定
	/// @param 触发事件的植物，植物判定的僵尸，索敌行
	/// @return 若为负数，则按原版处理；若为 0，则为不可选中；若为正数，则为强制可选。
	class PlantFindTargetRTEvent_ts : public ThreeStateEventTemplate<0x467614, 6, 0x4676C8, 0x467884, MEM_ESP_ADD(0x74), REG_ESI, REG_EDI>
	{
	public:
		PlantFindTargetRTEvent_ts(const char* str) : ThreeStateEventTemplate() { Init(str); };
		PlantFindTargetRTEvent_ts(int address) : ThreeStateEventTemplate() { Init(address); };
		PlantFindTargetRTEvent_ts() : PlantFindTargetRTEvent_ts("onPlantFindTargetRT") {};
	};

	/// @brief 窝瓜索敌僵尸事件
	/// @note 该事件只重载行差判定和类型判定
	/// @param 触发事件的植物，植物判定的僵尸
	/// @return 若为负数，则按原版处理；若为 0，则为不可选中；若为正数，则为强制可选。
	class SquashFindTargetRTEvent_ts : public ThreeStateEventTemplate<0x460829, 6, 0x460859, 0x46099F, REG_EBX, REG_EBP>
	{
	public:
		SquashFindTargetRTEvent_ts(const char* str) : ThreeStateEventTemplate() { Init(str); };
		SquashFindTargetRTEvent_ts(int address) : ThreeStateEventTemplate() { Init(address); };
		SquashFindTargetRTEvent_ts() : SquashFindTargetRTEvent_ts("onSquashFindTargetRT") {};
	};

	/// @brief 杨桃索敌僵尸事件
	/// @note 优先级低于 PVZ::DamageRangeFlags 的判别，高于其他判定
	/// @param 触发事件的植物，植物判定的僵尸
	/// @return 若为负数，则按原版处理；若为 0，则为不可选中；若为正数，则为强制可选。
	class StarfruitFindTargetEvent_ts : public ThreeStateEventTemplate<0x45F4F1, 6, 0x45F6D1, 0x45F6AD, REG_EBX, MEM_ESP_ADD(0x70)>
	{
	public:
		StarfruitFindTargetEvent_ts(const char* str) : ThreeStateEventTemplate() { Init(str); };
		StarfruitFindTargetEvent_ts(int address) : ThreeStateEventTemplate() { Init(address); };
		StarfruitFindTargetEvent_ts() : StarfruitFindTargetEvent_ts("onStarFruitFindTarget") {};
	};

	/// @brief 磁力菇索敌僵尸事件
	/// @note 该事件只重载行差判定和类型判定，不影响基础类型判定和范围判定
	/// @param 触发事件的植物，植物判定的僵尸
	/// @return 若为负数，则按原版处理；若为 0，则为不可选中；若为正数，则为强制可选。
	class MagnetShroomFindTargetRTEvent_ts : public ThreeStateEventTemplate<0x46209C, 6, 0x4620F4, 0x46218F, REG_EBX, REG_EDI>
	{
	public:
		MagnetShroomFindTargetRTEvent_ts(const char* str) : ThreeStateEventTemplate() { Init(str); };
		MagnetShroomFindTargetRTEvent_ts(int address) : ThreeStateEventTemplate() { Init(address); };
		MagnetShroomFindTargetRTEvent_ts() : MagnetShroomFindTargetRTEvent_ts("onMagnetShroomFindTargetRT") {};
	};

	/// @brief 磁力菇索敌场地物品事件
	/// @param 触发事件的植物，植物判定的场地物品
	/// @return 若为负数，则按原版处理；若为 0，则为不可选中；若为正数，则为强制可选。
	class MagnetShroomFindGriditemEvent_ts : public ThreeStateEventTemplate<0x4621E8, 8, 0x46224F, 0x462257, MEM_ESP_ADD(0x34), REG_EBX>
	{
	public:
		MagnetShroomFindGriditemEvent_ts(const char* str) : ThreeStateEventTemplate() { Init(str); };
		MagnetShroomFindGriditemEvent_ts(int address) : ThreeStateEventTemplate() { Init(address); };
		MagnetShroomFindGriditemEvent_ts() : MagnetShroomFindGriditemEvent_ts("onMagnetShroomFindGriditem") {};
	};
}
