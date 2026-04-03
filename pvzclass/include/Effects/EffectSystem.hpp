#pragma once
#include "../../PVZ.h"

namespace PVZ
{
	class EffectSystem
	{
		/// @brief 扩展拖尾、动画、附件的上限数目。
		/// @note 不影响粒子系统
		/// @param num 调整后的上限数。
		static void Extend(uint32_t num);
	};
}