#pragma once
#include "DLLEvent.h"

/// @brief 植物特性更新事件。
/// @note 时机上先于保龄球特性。
/// @param 触发事件的植物。
/// @return 是否结算大部分原版特性。若为“否”，则只结算射手和一次性植物的特性。
class PlantUpdateAbilityEvent : public DLLEvent
{
public:
	PlantUpdateAbilityEvent() : PlantUpdateAbilityEvent("onPlantUpdateAbility") {};
	PlantUpdateAbilityEvent(const char* str) : PlantUpdateAbilityEvent(PVZ::Memory::GetProcAddress(str)) {};
	PlantUpdateAbilityEvent(int address)
	{
		hookAddress = 0x463254;
		rawlen = 5;
		BYTE code[] =
		{
			PUSH_EDI,
			INVOKE(address),
			ADD_ESP(4),
			TEST_AL_AL,
			JNZ(8),

			POPAD,
			MOV_ECX(0x4633EE),
			JMP_REG32(REG_ECX),

			POPAD,
			INVOKE(0x453840),
			MOV_ECX(0x463259),
			JMP_REG32(REG_ECX),
		};
		start(STRING(code));
	}
};

namespace PVZEvent
{
	/// @brief 判断植物是否应该发动技能的事件
	/// @note 时机上后于压扁判断和消失判断，但先于蹦极是否抱住的判断。
	/// @param 触发事件的植物
	/// @return 是否继续判定是否应该发动技能。若为否，则不发动技能。
	class JudgetPlantUpdateAbilityEvent : public BoolDLLEventTemplate<0x463217, 7, 0x463410, REG_EDI>
	{
	public:
		JudgetPlantUpdateAbilityEvent(int address) : BoolDLLEventTemplate() { Init(address); };
		JudgetPlantUpdateAbilityEvent(const char* name) : BoolDLLEventTemplate() { Init(name); };
		JudgetPlantUpdateAbilityEvent() : JudgetPlantUpdateAbilityEvent("ShouldPlantUpdateAbility") {};
	};

	/// @brief 植物更新特殊外观事件
	/// @param 触发事件的植物
	/// @return 是否结算原版对部分植物的特殊外观设定。
	class PlantSpecialAnimateEvent : public BoolDLLEventTemplate<0x464E4E, 6, 0x464E7C, REG_EDI>
	{
	public:
		PlantSpecialAnimateEvent(const char* str) : BoolDLLEventTemplate() { Init(str); };
		PlantSpecialAnimateEvent(int address) : BoolDLLEventTemplate() { Init(address); };
		PlantSpecialAnimateEvent() : PlantSpecialAnimateEvent("onPlantSpecialAnimate") {};
	};

	namespace Chomper
	{
		/// @brief 大嘴花吞噬僵尸事件.
		///	@note 取消该事件将不会结算啃咬伤害。若希望不吞噬，但结算伤害，请使用 InstantJudgeEvent。
		/// @param 依次为：触发事件的植物、该植物啃食的僵尸。
		/// @return 是否吞噬此僵尸。
		class DevourEvent : public BoolDLLEventTemplate<0x4614F9, 5, 0x4614E5, REG_ESI, REG_EDI>
		{
		public:
			DevourEvent(const char* str) : BoolDLLEventTemplate() { Init(str); };
			DevourEvent(int address) : BoolDLLEventTemplate() { Init(address); };
			DevourEvent() : DevourEvent("onChomperDevour") {};
		};

		/// @brief 大嘴花判断是否秒杀僵尸事件。
		/// @note 该事件下不秒杀会改为造成伤害。
		/// @param 依次为：触发事件的植物、该植物啃食的僵尸。
		/// @return 由 ThreeState::ThreeState 表示的，是否秒杀。
		class InstantJudgeEvent : public ThreeStateEventTemplate<0x461444, 6, 0x461458, 0x461456, REG_ESI, REG_EDI>
		{
		public:
			InstantJudgeEvent(const char* str) : ThreeStateEventTemplate() { Init(str); };
			InstantJudgeEvent(int address) : ThreeStateEventTemplate() { Init(address); };
			InstantJudgeEvent() : InstantJudgeEvent("IsChomperInstant") {};
		};

		/// @brief 大嘴花开始咀嚼事件。\n
		///		时机上落后于原版的设置。
		/// @param 触发事件的植物
		class ChewStartEvent : public DLLEventTemplate<0x461555, 5, REG_EDI>
		{
		public:
			ChewStartEvent(const char* str) : DLLEventTemplate() { Init(str); };
			ChewStartEvent(int address) : DLLEventTemplate() { Init(address); };
			ChewStartEvent() : ChewStartEvent("onChomperChewStart") {};
		};

		/// @brief 大嘴花完成咀嚼事件。
		///	@note 时机上落后于原版的设置（状态设置除外）。
		/// @note 大嘴花吞噬失败也会触发这个事件。
		/// @param 触发事件的植物
		class ChewFinishEvent : public DLLEventTemplate<0x4615BF, 7, REG_EDI>
		{
		public:
			ChewFinishEvent(const char* str) : DLLEventTemplate() { Init(str); };
			ChewFinishEvent(int address) : DLLEventTemplate() { Init(address); };
			ChewFinishEvent() : ChewFinishEvent("onChomperChewFinish") {};
		};
	}

	namespace MagnetShroom
	{
		/// @brief 磁力菇吸取铁器，转换为不活跃外观的事件
		/// @param 触发事件的植物
		/// @return 是否结算原版的动作调整。
		class InactiveEvent : public BoolDLLEventTemplate<0x461F6A, 6, 0x461FE3, REG_EBX>
		{
		public:
			InactiveEvent() : BoolDLLEventTemplate() { Init("onMagnetShroomInactive"); };
			InactiveEvent(const char* str) : BoolDLLEventTemplate() { Init(str); };
			InactiveEvent(int address) : BoolDLLEventTemplate() { Init(address); };
		};
	}

	namespace KernelPult
	{
		/// @brief 玉米投手判定是否投掷黄油事件
		/// @note 若启用该事件，原版的判定条件将被废弃
		/// @param 触发事件的植物
		/// @return 是否投掷黄油
		class JudgeButterEvent : public DiversionEventTemplate<0x45F1E5, 5, 0x45F1EE, 0x45F22D, REG_ESI>
		{
		public:
			JudgeButterEvent(const char* str) : DiversionEventTemplate() { Init(str); };
			JudgeButterEvent(int address) : DiversionEventTemplate() { Init(address); };
			JudgeButterEvent() : JudgeButterEvent("onKernelPultJudgeButter") {};
		};
	}

	namespace GoldManget
	{
		/// @brief 吸金磁吸取物品事件
		/// @param 触发事件的植物，被吸取的物品，被吸取的物品将存入的 MagnetItem
		class AttractEvent : public DLLEventTemplate<0x462567, 7, REG_ESI, REG_EBP, REG_EDI>
		{
		public:
			AttractEvent(const char* str) : DLLEventTemplate() { Init(str); };
			AttractEvent(int address) : DLLEventTemplate() { Init(address); };
			AttractEvent() : DLLEventTemplate() { Init("onGoldMagnetAttract"); };
		};
	}
}