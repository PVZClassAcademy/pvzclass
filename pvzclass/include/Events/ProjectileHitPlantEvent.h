#pragma once
#include "DLLEvent.h"

/// @brief 子弹命中植物事件
/// @param 子弹与被命中的植物
/// @return 被命中的植物地址，0为判定未命中\n
/// 如果返回其它植物也可以做到一些有意思的事情
class ProjectileHitPlantEvent : public DLLEvent
{
public:
	ProjectileHitPlantEvent() : ProjectileHitPlantEvent("onProjectileHitPlant") {};
	ProjectileHitPlantEvent(const char* name) : ProjectileHitPlantEvent(PVZ::Memory::GetProcAddress(name)) {};
	ProjectileHitPlantEvent(int address)
	{
		PVZ::Memory::WriteMemory<BYTE>(0x46CBBF, 0xEB);
		PVZ::Memory::WriteMemory<BYTE>(0x46CBC0, 0x63);
		PVZ::Memory::WriteMemory<BYTE>(0x46CC18, 0xEB);
		PVZ::Memory::WriteMemory<BYTE>(0x46CC19, 0x0A);
		hookAddress = 0x46CC28;
		rawlen = 6;
		BYTE code[] = { CMP_EAX_DWORD(0), JE(22), PUSH_EAX, PUSH_EBP,
				INVOKE(address), ADD_ESP(8), MOV_PTR_ESP_ADD_V_EUX(0, 28)
			};
		start(STRING(code));
	}
};

namespace PVZEvent
{
	/// @brief 子弹被叶子保护伞弹开事件
	/// @param 依次为 触发事件的子弹，弹开子弹的植物
	/// @note 该事件不能让其他植物获得弹开子弹的能力。若需要此调整，请使用 CheckUmbrellaEvent 。
	class ProjectileReflectedEvent : public DLLEventTemplate<0x46D6D6, 7, REG_EDI, REG_EBP>
	{
	public:
		ProjectileReflectedEvent() : DLLEventTemplate() { Init("onProjectileReflected"); };
		ProjectileReflectedEvent(const char* str) : DLLEventTemplate() { Init(str); };
		ProjectileReflectedEvent(int address) : DLLEventTemplate() { Init(address); };
	};
}
