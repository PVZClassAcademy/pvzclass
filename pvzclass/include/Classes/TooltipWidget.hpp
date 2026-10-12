#pragma once
#include "../../PVZ.h"

namespace PVZ
{
	/// @brief 存储关卡内文字提示的类。
	class TooltipWidget : public PVZ::BaseClass
	{
	public:
		TooltipWidget(uint32_t address) : PVZ::BaseClass(address) {};
		READONLY_PROPERTY_BINDING(PVZString, __get_Title, PVZString(this->BaseAddress)) Title;
		READONLY_PROPERTY_BINDING(PVZString, __get_Label, PVZString(this->BaseAddress + 0x1C)) Label;
		READONLY_PROPERTY_BINDING(PVZString, __get_WarningText, PVZString(this->BaseAddress + 0x38)) WarningText;
		INT_PROPERTY(X, __get_X, __set_X, 0x54);
		INT_PROPERTY(Y, __get_Y, __set_Y, 0x58);
		T_SIMPLE_PROPERTY(bool, Visible, 0x64);
		T_SIMPLE_PROPERTY(bool, Center, 0x65);
		INT_SIMPLE_PROPERTY(WarningFlashCounter, 0x78);

		void CalculateSize();
		void SetLabel(PVZString str);
	};
}