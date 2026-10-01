#pragma once
#include "DLLEvent.h"

namespace PVZEvent
{
	/// @brief 僵尸失去盾牌事件
	/// @param 触发事件时的僵尸
	/// @bug 与已存在的事件重复。
	class ZombieDetachShieldEvent : public DLLEventTemplate<0x5330E0, 5, REG_EAX>
	{
	public:
		ZombieDetachShieldEvent(int address) : DLLEventTemplate() { Init(address); };
		ZombieDetachShieldEvent(const char* name) : DLLEventTemplate() { Init(name); };
		ZombieDetachShieldEvent() : ZombieDetachShieldEvent("onZombieDetachShield") {};
	};

	/// @brief 僵尸掉头盔事件
	/// @param 触发事件的僵尸
	class ZombieDropHelmEvent : public DLLEventTemplate<0x530E46, 6, REG_EBX>
	{
	public:
		ZombieDropHelmEvent(int address) : DLLEventTemplate() { Init(address); };
		ZombieDropHelmEvent(const char* name) : DLLEventTemplate() { Init(name); };
		ZombieDropHelmEvent() : ZombieDropHelmEvent("onZombieDropHelm") {};
	};
	
	/// @brief 僵尸掉头盔的粒子效果处理事件。
	/// @param 触发事件的僵尸、触发事件的粒子效果。
	/// @note 结算时机先于原版的大小重载，但该事件无法将其跳过。
	class ZombieDropHelmParticleEvent : public DLLEventTemplate<0x530FB3, 6, REG_EAX, REG_EBX>
	{
	public:
		ZombieDropHelmParticleEvent() : DLLEventTemplate() { Init("onZombieDropHelmParticle"); };
		ZombieDropHelmParticleEvent(const char* str) : DLLEventTemplate() { Init(str); };
		ZombieDropHelmParticleEvent(int address) : DLLEventTemplate() { Init(address); };
	};

	/// @brief 僵尸头盔受到伤害后，调整头盔外观事件。
	/// @param 触发事件的僵尸、僵尸的本体动画、僵尸头盔受伤程度的三分数。
	/// @note 只有三分数发生变化时，该事件才会触发。
	/// @return 是否使用原版的图片重载处理。
	class ZombieTakeHelmDamageTextureEvent : public BoolDLLEventTemplate<0x5310F8, 6, 0x53111B, REG_EDI, REG_ECX, REG_EBP>
	{
	public:
		ZombieTakeHelmDamageTextureEvent() : BoolDLLEventTemplate() { Init("onZombieTakeHelmDmgTexture"); };
		ZombieTakeHelmDamageTextureEvent(const char* str) : BoolDLLEventTemplate() { Init(str); };
		ZombieTakeHelmDamageTextureEvent(int address) : BoolDLLEventTemplate() { Init(address); };
	};

	/// @brief 僵尸掉手的粒子效果处理事件。
	/// @param 触发事件的僵尸、触发事件的粒子效果。
	/// @note 结算时机后于原版的大小重载和颜色重载。
	/// @return 是否使用原版的图片重载处理。
	class ZombieDropArmParticleEvent : public BoolDLLEventTemplate<0x52A3B1, 6, 0x52A452, REG_EDI, REG_EBX>
	{
	public:
		ZombieDropArmParticleEvent() : BoolDLLEventTemplate() { Init("onZombieDropArmParticle"); };
		ZombieDropArmParticleEvent(const char* str) : BoolDLLEventTemplate() { Init(str); };
		ZombieDropArmParticleEvent(int address) : BoolDLLEventTemplate() { Init(address); };
	};
}