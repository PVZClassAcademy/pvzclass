#include "../PVZ.h"

namespace PVZ
{
	class WidgetManager : public WidgetContainer
	{
	public:
		WidgetManager(uint32_t baseaddress) : WidgetContainer(baseaddress) {};
		T_READONLY_PROPERTY(bool, IsMouseInArea, __get_IsMouseInArea, 0xDC);
		INT_PROPERTY(X, __get_X, __set_X, 0xE0);
		INT_PROPERTY(Y, __get_Y, __set_Y, 0xE4);
		T_READONLY_PROPERTY(MouseClickState::MouseClickState, ClickState, __get_ClickState, 0xE8);
		void GameClick(int x, int y);
	};
    PVZ::WidgetManager GetWidgetManager();
}
