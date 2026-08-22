#pragma once
#include "DLLEvent.h"

namespace PVZEvent
{
	/// @brief 使用普通僵尸模型的僵尸生成贴图缓存后的事件	
	/// @param 触发事件的动画部件，僵尸类型，Graphics
	/// @note 事件结算完毕后，动画部件将立刻绘制
	class NormalZombieReanimMakeCacheEvent : public DLLEvent
	{
	public:
		NormalZombieReanimMakeCacheEvent() : NormalZombieReanimMakeCacheEvent("onNormalZombieReanimMakeCache") {};
		NormalZombieReanimMakeCacheEvent(const char* name) : NormalZombieReanimMakeCacheEvent(PVZ::Memory::GetProcAddress(name)) {};
		NormalZombieReanimMakeCacheEvent(uint32_t address)
		{
			hookAddress = 0x46FAD3;
			rawlen = 9;
			BYTE code[] = {
				PUSH_ESP,
				CALC_PTR_ESP(CALC_ADD, 0x174),
				PUSH_EDI,
				PUSH_ESP,
				CALC_PTR_ESP(CALC_ADD, 0x3C),
				INVOKE(address),
				ADD_ESP(12),
			};
			start(STRING(code));
		};
	};
}
