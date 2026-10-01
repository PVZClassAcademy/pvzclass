#pragma once
#include "DLLEvent.h"

/// @brief 僵尸受伤事件
/// @param 触发事件的僵尸，伤害类型，伤害数值
/// @return 更新后的伤害值
class ZombieHitEvent : public DLLEvent
{
public:
	ZombieHitEvent()
	{
		int procAddress = PVZ::Memory::GetProcAddress("onZombieHit");
		hookAddress = 0x5317C0;
		rawlen = 7;
		BYTE code[] = { PUSH_PTR_ESP_ADD_V(36), PUSH_EAX, PUSH_ESI, INVOKE(procAddress), ADD_ESP(12), MOV_PTR_ESP_ADD_V_EUX(0, 36) };
		start(STRING(code));
	}
};

/// @brief 僵尸受伤事件
/// @param 触发事件的僵尸，伤害类型的引用，伤害数值
/// @return 更新后的伤害值
class ZombieTakeDmgEvent : public DLLEvent
{
public:
	ZombieTakeDmgEvent() : ZombieTakeDmgEvent("onZombieTakeDamage") {};
	ZombieTakeDmgEvent(const char* str) : ZombieTakeDmgEvent(PVZ::Memory::GetProcAddress(str)) {};
	ZombieTakeDmgEvent(int address)
	{
		hookAddress = 0x5317C0;
		rawlen = 7;
		BYTE code[] = {
			PUSH_PTR_ESP_ADD_V(36),
			MOV_PTR_ADDR_EAX(PVZ::Memory::Variable + 400),
			PUSHDWORD(PVZ::Memory::Variable + 400),
			PUSH_ESI,
			INVOKE(address),
			ADD_ESP(12),
			MOV_PTR_ESP_ADD_V_EUX(0, 36),
			POPAD,
			MOV_EAX_PTR(PVZ::Memory::Variable + 400),
			0x51, 0x8B, 0x4E, 0x28, 0x83, 0xF9, 0x10,// <-origincode here
			PUSHDWORD(0x5317C7),
			RET
		};
		start(STRING(code));
	}
};

namespace PVZEvent
{
	/// @brief 僵尸本体受伤后事件
	/// @note 时机上后于本体受伤，先于后续所有判别。
	/// @param 触发事件的僵尸，伤害数值，伤害标签
	class ZombieTakeBodyDamageAfterEvent : public DLLEventTemplate<0x53131F, 5, MEM_ESP_ADD(0x44), MEM_ESP_ADD(0x44), REG_EBP>
	{
	public:
		ZombieTakeBodyDamageAfterEvent(const char* str) : DLLEventTemplate() { Init(str); };
		ZombieTakeBodyDamageAfterEvent(int address) : DLLEventTemplate() { Init(address); };
		ZombieTakeBodyDamageAfterEvent() : ZombieTakeBodyDamageAfterEvent("onZombieTakeBodyDamageAfter") {};
	};

	/// @brief 僵尸受到非灰烬爆炸伤害事件
	/// @param 触发事件的僵尸
	/// @return 是否受到此次伤害
	class PotatoDamageZombieEvent : public DLLEventTemplate<0x41D93A, 5, REG_ESI>
	{
	public:
		PotatoDamageZombieEvent(int address) : DLLEventTemplate() { Init(address); };
		PotatoDamageZombieEvent(const char* name) : DLLEventTemplate() { Init(name); };
		PotatoDamageZombieEvent() : PotatoDamageZombieEvent("onPotatoDamageZombie") {};
		virtual void InitExtra(AsmBuilder& builder)
		{
			builder.test_al_al().jnz_rel(10).popad().add_reg_imm(REG_ESP, 4).push_imm32(0x41D93F).ret();
		}
	};

	/// @brief 僵尸掉头后，持续受到伤害事件
	/// @param 触发事件的僵尸
	/// @return 僵尸是否受到伤害
	class ZombieWitherEvent : public DiversionEventTemplate<0x52B536, 5, 0x52B544, 0x52B551, REG_EDI>
	{
	public:
		ZombieWitherEvent(int address) : DiversionEventTemplate() { Init(address); };
		ZombieWitherEvent(const char* name) : DiversionEventTemplate() { Init(name); };
		ZombieWitherEvent() : ZombieWitherEvent("onZombieWither") {};
	};
	/// @brief 僵尸被其他僵尸啃食事件
	/// @param 被啃咬者，伤害，伤害类型，攻击者
	/// @return 僵尸是否受到伤害
	class ZombieEatByZombieEvent : public BoolDLLEventTemplate<0x52FE1A, 5, 0x52FE1F, MEM_ESP_ADD(0x24), CONST_VAL(9), CONST_VAL(4), REG_ESI>
	{
	public:
		ZombieEatByZombieEvent(int address) : BoolDLLEventTemplate() { Init(address); };
		ZombieEatByZombieEvent(const char* name) : BoolDLLEventTemplate() { Init(name); };
		ZombieEatByZombieEvent() : ZombieEatByZombieEvent("onZombieEatByZombie") {};
	};

	/// @brief 僵尸索敌判定事件
	/// @param 触发事件的僵尸
	/// @note 不影响攻击间隔判定
	/// @return 由 ThreeState::ThreeState 表示的，是否可以索敌
	class IsZombieAble2EatEvent : public ThreeStateEventTemplate<0x52F4C8, 5, 0x52F640, 0x52F6BC, REG_EAX>
	{
	public:
		IsZombieAble2EatEvent() : ThreeStateEventTemplate() { Init("IsZombieAble2Eat"); };
		IsZombieAble2EatEvent(const char* str) : ThreeStateEventTemplate() { Init(str); };
		IsZombieAble2EatEvent(int address) : ThreeStateEventTemplate() { Init(address); };
	};

	/// @brief 僵尸是否被缠绕水草缠绕判定事件
	/// @param 触发事件的僵尸
	/// @return 由 ThreeState::ThreeState 表示的，是否被缠绕水草缠绕
	class IsZombieTangleKelpTargetEvent
	{
	private:
		class Part1 : public ThreeStateEventTemplate<0x526199, 7, 0x5261C8, 0x5261CD, REG_EDI>
		{
		public:
			Part1(int address) : ThreeStateEventTemplate() { Init(address); };
		} *part1;
		class Part2 : public ThreeStateEventTemplate<0x5324B0, 5, 0x413A5E, 0x413A5B, REG_EDI>
		{
		public:
			Part2(int address) : ThreeStateEventTemplate() { Init(address); };
		} *part2;
	public:
		IsZombieTangleKelpTargetEvent() : IsZombieTangleKelpTargetEvent("IsZombieTangleKelpTarget") {};
		IsZombieTangleKelpTargetEvent(const char* name) : IsZombieTangleKelpTargetEvent(PVZ::Memory::GetProcAddress(name)) {};
		IsZombieTangleKelpTargetEvent(int address)
		{
			part1 = new Part1(address);
			part2 = new Part2(address);
		}
		void end()
		{
			part1->end();
			part2->end();
		}
	};
}
