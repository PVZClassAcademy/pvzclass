#pragma once
#include "DLLEvent.h"

namespace PVZEvent
{
	/// @brief 植物设置大小事件
	/// @param 植物，X 偏移，Y 偏移，X 缩放，Y 缩放
	class PlantSetSizeEvent : public DLLEvent
	{
	public:
		PlantSetSizeEvent() : PlantSetSizeEvent("GetPlantSize") {};
		PlantSetSizeEvent(const char* str) : PlantSetSizeEvent(PVZ::Memory::GetProcAddress(str)) {};
		PlantSetSizeEvent(int address)
		{
			hookAddress = 0x463BAE;
			rawlen = 6;
			BYTE code[] =
			{
				PUSH_ECX,
				LEA_ECX_ESP_ADD(0x40),

				PUSH_ECX,
				SUB_EUX(REG_ECX, 4),
				PUSH_ECX,
				SUB_EUX(REG_ECX, 4),
				PUSH_ECX,
				SUB_EUX(REG_ECX, 4),
				PUSH_ECX,
				SUB_EUX(REG_ECX, 4),
				PUSH_EBX,

				INVOKE(address),
				ADD_ESP(20),

				POP_EUX(REG_ECX)
			};
			start(STRING(code));
		}
	};

	/// @brief 植物设置大小事件
	/// @param 植物，缩放大小，Y 偏移，X 偏移
	class PlantSetShadowSizeEvent : public DLLEvent
	{
	public:
		PlantSetShadowSizeEvent() : PlantSetShadowSizeEvent("GetPlantShadowSize") {};
		PlantSetShadowSizeEvent(const char* str) : PlantSetShadowSizeEvent(PVZ::Memory::GetProcAddress(str)) {};
		PlantSetShadowSizeEvent(int address)
		{
			hookAddress = 0x465960;
			rawlen = 9;
			BYTE code[] =
			{
				PUSH_ECX,
				LEA_ECX_ESP_ADD(0x3C),

				PUSH_ECX,
				SUB_EUX(REG_ECX, 4),
				PUSH_ECX,
				SUB_EUX(REG_ECX, 4),
				PUSH_ECX,
				SUB_EUX(REG_ECX, 4),
				PUSH_EBX,

				INVOKE(address),
				ADD_ESP(16),

				POP_EUX(REG_ECX),
				POPAD,

				CMP_EUX(REG_ESI, 0x23),
				JE(6),

				PUSHDWORD(0x465A0A),
				RET,

				PUSHDWORD(0x465969),
				RET,
			};
			start(STRING(code));
		}
	};
}