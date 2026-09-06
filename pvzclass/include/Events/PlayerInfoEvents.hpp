#pragma once
#include "DLLEvent.h"

namespace PVZEvent
{
	/// @brief PlayerInfo 重置完成事件
	/// @param 触发事件的 PlayerInfo
	/// @note PlayerInfo 在创建时会进行重置，因此也会触发该事件。
	class PlayerInfoResetAfterEvent : public DLLEvent 
	{
	public:
		PlayerInfoResetAfterEvent() : PlayerInfoResetAfterEvent("onPlayerInfoResetAfter") {};
		PlayerInfoResetAfterEvent(const char* str) : PlayerInfoResetAfterEvent(PVZ::Memory::GetProcAddress(str)) {};
		PlayerInfoResetAfterEvent(int address)
		{
			hookAddress = 0x4699F8;
			rawlen = 6;
			BYTE code[] =
			{
				MOV_PTR_EUX_ADD__EVX(REG_ESI, REG_EBX, 0x350),
				PUSH_ESI,
				INVOKE(address),
				ADD_ESP(4),

				POPAD,
				MOV_ECX(0x4699FE),
				JMP_REG32(REG_ECX)
			};
			start(STRING(code));
		}
	};
}
