#pragma once
#include "DLLEvent.h"

/// @brief 子弹命中僵尸事件
/// @param 子弹与被命中的僵尸
/// @return 被命中的僵尸地址，0为判定未命中\n
// 如果返回其它僵尸也可以做到一些有意思的事情
class ProjectileHitZombieEvent : public DLLEvent
{
public:
	ProjectileHitZombieEvent() : ProjectileHitZombieEvent("onProjectileHitZombie") {};
	ProjectileHitZombieEvent(const char* name) : ProjectileHitZombieEvent(PVZ::Memory::GetProcAddress(name)) {};
	ProjectileHitZombieEvent(int address)
	{
		hookAddress = 0x46CE74;
		rawlen = 6;
		BYTE code[] = { CMP_EAX_DWORD(0), JE(22), PUSH_EAX, PUSH_EBP,
			INVOKE(address), ADD_ESP(8), MOV_PTR_ESP_ADD_V_EUX(0, 28) };
		start(STRING(code));
	}
};

namespace PVZEvent
{
	/// @brief 子弹是否可以击中僵尸事件
	/// @param 触发事件的子弹，子弹判定的僵尸
	/// @return 以 ThreeState::ThreeState 表示的，子弹是否能打中僵尸
	class ProjectileFindTargetZombieRTEvent_ts : public ThreeStateEventTemplate<0x46CD95, 6, 0x46CDAD, 0x46CE58, REG_ESI, REG_EDI>
	{
	public:
		ProjectileFindTargetZombieRTEvent_ts(const char* str) : ThreeStateEventTemplate() { Init(str); };
		ProjectileFindTargetZombieRTEvent_ts(int address) : ThreeStateEventTemplate() { Init(address); };
		ProjectileFindTargetZombieRTEvent_ts() : ProjectileFindTargetZombieRTEvent_ts("onProjFindTargetZombieRT") {};
	};

	/// @brief 子弹击中僵尸事件
	/// @param 依次为：触发事件的子弹，子弹击中的僵尸
	/// @return 是否结算原版的子弹击中过程。若为 false，则子弹不会消失，但也不会造成伤害
	class ProjectileImpactEvent : public BoolDLLEventTemplate<0x46E000, 5, 0x46EB41, REG_EAX, REG_ECX>
	{
	public:
		ProjectileImpactEvent(const char* str) : BoolDLLEventTemplate() { Init(str); };
		ProjectileImpactEvent(int address) : BoolDLLEventTemplate() { Init(address); };
		ProjectileImpactEvent() : ProjectileImpactEvent("onProjectileImpact") {};
	};

	/// @brief 子弹击中僵尸时，是否造成溅射伤害事件
	/// @param 触发事件的子弹，子弹击中的僵尸
	/// @return 由 ThreeState::ThreeState 表示的，是否造成溅射伤害
	class IsProjectileSplashDmgEvent_ts : public DLLEventTemplate<0x46E013, 6, REG_ESI, REG_EDI>
	{
	public:
		IsProjectileSplashDmgEvent_ts(const char* str) : DLLEventTemplate() { Init(str); };
		IsProjectileSplashDmgEvent_ts(int address) : DLLEventTemplate() { Init(address); };
		IsProjectileSplashDmgEvent_ts() : DLLEventTemplate() { Init("IsProjectileSplashDmg"); };
	protected:
		static constexpr std::array<uint8_t, 22> compiled_special_bytes =
		{
			TEST_AL_AL,
			JS(18),
			POPAD,
			JE(6),

			PUSHDWORD(0x46E05B),
			RET,

			MOV_EUX_PTR_EVX_ADD_V(REG_EBX, REG_EDI, 0x5C),
			PUSHDWORD(0x46E065),
			RET
		};
		virtual void InitExtra(AsmBuilder& builder)
		{
			builder.add_bytes(compiled_special_bytes.data(), 22);
		}
	};

	/// @brief 判断僵尸是否受到子弹的溅射伤害
	/// @param 依次为：溅射伤害的子弹，触发事件的僵尸
	/// @note 该事件只重载类型和行差的判定。
	/// @return 由 ThreeState::ThreeState 表示的，是否受到溅射伤害
	class CheckZombieHitBySplashRTEvent : public ThreeStateEventTemplate<0x46D2E5, 6, 0x46D32D, 0x46D319, REG_EBX, REG_EBP>
	{
	public:
		CheckZombieHitBySplashRTEvent() : ThreeStateEventTemplate() { Init("IsZombieHitBySplashRT"); };
		CheckZombieHitBySplashRTEvent(const char* str) : ThreeStateEventTemplate() { Init(str); };
		CheckZombieHitBySplashRTEvent(int address) : ThreeStateEventTemplate() { Init(address); };
	};
}