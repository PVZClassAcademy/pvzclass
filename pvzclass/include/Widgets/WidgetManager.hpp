#include "../PVZ.h"

namespace PVZ
{
	class WidgetManager : public WidgetContainer
	{
	public:
		WidgetManager(uint32_t baseaddress) : WidgetContainer(baseaddress) {};
		T_READONLY_PROPERTY(PVZ::PVZApp, App, __get_App, 0x5C);
		T_READONLY_PROPERTY(bool, HasFocus, __get_HasFocus, 0x84);
		T_READONLY_PROPERTY(bool, IsMouseInArea, __get_IsMouseInArea, 0xDC);
		INT_PROPERTY(X, __get_X, __set_X, 0xE0);
		INT_PROPERTY(Y, __get_Y, __set_Y, 0xE4);
		T_READONLY_PROPERTY(MouseClickState::MouseClickState, ClickState, __get_ClickState, 0xE8);
		READONLY_PROPERTY_BINDING(PVZ::Array<bool>, __get_IsKeyDown, this->BaseAddress + 0x0F4) IsKeyDown;
		INT_SIMPLE_PROPERTY(LastDownButtonId, 0x1F4);

		void MouseDown(int x, int y);
	};
    PVZ::WidgetManager GetWidgetManager();
}
