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
}