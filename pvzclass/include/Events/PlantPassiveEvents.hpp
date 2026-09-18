#pragma once
#include "DLLEvent.h"

namespace PVZEvent
{
	/// @brief 判断植物是否具有保护伞防护效果的事件
	/// @param 触发事件的植物，检查的行数，检查的列数
	/// @return 若为负数，与原版一致；若为 0，则无效果；若为是，则有效果，且返回值应当为该植物的基址。
	class CheckUmbrellaEvent_ts : public ThreeStateEventTemplate<0x41D3F0, 8, 0x41D446, 0x41D437, REG_EBX, REG_EDI, MEM_ESP_ADD(0x2C)>
	{
	public:
		CheckUmbrellaEvent_ts(const char* str) : ThreeStateEventTemplate() { Init(str); };
		CheckUmbrellaEvent_ts(int address) : ThreeStateEventTemplate() { Init(address); };
		CheckUmbrellaEvent_ts() : CheckUmbrellaEvent_ts("IsUmbrellaPlant") {};
	};

	/// @brief 植物在 IZ 中判断是否掉落阳光事件
	/// @param 触发事件的 Challenge，触发事件的植物
	/// @note 原版的非 IZ 模式不触发该事件，但手动调用 Challenge::IZPlantDropRemainingSun() 可以触发此事件。
	/// @return 由 ThreeSteate::ThreeState 表示的，植物是否掉落阳光
	class PlantDropRemainingSunEvent_ts : public DLLEventTemplate<0x42B9D0, 5, REG_ESI, MEM_ESP_ADD(0x28)>
	{
	protected:
		static constexpr std::array<uint8_t, 23> compiled_special_bytes =
		{
			TEST_EUX_EVX(REG_EAX, REG_EAX),
			JS(19),
			POPAD,
			JE(0x0D),

			PUSH_EBX,
			PUSH_EBP,
			MOV_REG32_PTR_ESP_ADD_V(REG_EBP, 0x0C),
			PUSH_EDI,
			PUSHDWORD(0x42B9DD),
			RET,

			RETN(4)
		};
		virtual void InitExtra(AsmBuilder& builder)
		{
			builder.add_bytes(compiled_special_bytes.data(), 23);
		}
	public:
		PlantDropRemainingSunEvent_ts(const char* str) : DLLEventTemplate() { Init(str); };
		PlantDropRemainingSunEvent_ts(int address) : DLLEventTemplate() { Init(address); };
		PlantDropRemainingSunEvent_ts() : PlantDropRemainingSunEvent_ts("onPlantDropRemainingSun") {};
	};

	/// @brief 植物在 IZ 中因被碾或被偷取而掉落阳光时，修改掉落物创建参数事件
	/// @param 触发事件的植物，由 PVZ::Array\<int\> 表示的掉落物创建参数，依次为：X 坐标，Y 坐标，硬币类型和硬币位移方式。
	class PlantDropRemainingSunParamEvent : DLLEvent
	{
	public:
		PlantDropRemainingSunParamEvent() : PlantDropRemainingSunParamEvent("SetPlantDropRemainingSunParam") {};
		PlantDropRemainingSunParamEvent(const char* str) : PlantDropRemainingSunParamEvent(PVZ::Memory::GetProcAddress(str)) {};
		PlantDropRemainingSunParamEvent(int address)
		{
			hookAddress = 0x42BA11;
			rawlen = 5;
			BYTE code[] =
			{
				PUSH_ESP,
				CALC_PTR_ESP_V(CALC_ADD, 0x20),
				PUSH_ESI,
				INVOKE(address),
				ADD_ESP(8),
			};
			start(STRING(code));
		}
	};
}
