#pragma once
#include "DLLEvent.h"

/// @brief Zombie 行为动作的更新。
/// @note 时机上先于原版的更新。
/// @param 更新的 Zombie
class ZombieUpdateActionEvent : public DLLEventTemplate<0x52B112, 6, REG_EAX>
{
public:
	ZombieUpdateActionEvent() : DLLEventTemplate() { Init("onZombieUpdateAction"); };
	ZombieUpdateActionEvent(const char* str) : DLLEventTemplate() { Init(str); };
	ZombieUpdateActionEvent(int address) : DLLEventTemplate() { Init(address); };
};

namespace PVZEvent
{
	/// @brief Zombie 行为动作的更新。
	/// @note 时机上先于原版的更新。
	/// @note 该事件与 ZombieUpdateActionEvent 不同，只影响僵尸自身的技能。
	/// @param 更新的 Zombie
	/// @return 是否更新原版行为动作
	/// @retval false 完全跳过原版的任何行为动作，这会导致原生技能失效。
		class ZombieUpdateAbilityEvent : public DLLEventTemplate<0x52B174, 6, REG_ESI>
		{
		public:
			ZombieUpdateAbilityEvent() : DLLEventTemplate() { Init("onZombieUpdateAbility"); };
			ZombieUpdateAbilityEvent(const char* str) : DLLEventTemplate() { Init(str); };
			ZombieUpdateAbilityEvent(int address) : DLLEventTemplate() { Init(address); };
		protected:
			void InitExtra(AsmBuilder& builder)
			{
				static constexpr byte after[] =
				{
					0x84, 0xC0,
					0x75, 7,

					0x61,
					0x68, (byte)(0x52B278 & 0xFF), (byte)((0x52B278 & 0xFF00) >> 8), (byte)((0x52B278 & 0xFF0000) >> 16), (byte)((0x52B278 & 0xFF000000) >> 24),
					0xC3,

					0x61,
					0x83, 0x78 + (REG_ESI), 0x24, 3,
					0x75, 6,

					0x68, (byte)(0x52B17A & 0xFF), (byte)((0x52B17A & 0xFF00) >> 8), (byte)((0x52B17A & 0xFF0000) >> 16), (byte)((0x52B17A & 0xFF000000) >> 24),
					0xC3,
					0x68, (byte)(0x52B180 & 0xFF), (byte)((0x52B180 & 0xFF00) >> 8), (byte)((0x52B180 & 0xFF0000) >> 16), (byte)((0x52B180 & 0xFF000000) >> 24),
					0xC3,
				};
				builder.add_bytes(STRING(after));
			}
		};
}