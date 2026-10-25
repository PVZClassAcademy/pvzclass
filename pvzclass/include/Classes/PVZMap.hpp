#pragma once
#include "../../PVZ.h"

namespace PVZ
{
	/// @brief 键类型与值类型均为字符串的 map。
	/// @see PVZString
	class StringStringMap : public BaseClass
	{
	public:
		StringStringMap() = default;
		explicit StringStringMap(uint32_t address) : BaseClass(address) {};

		/// @brief 在 PVZ 主程序中创建一个字符串到字符串的 map
		/// @note 以此法创建的 map 需要使用 Free() 销毁，否则会造成内存泄露。
		/// @return 创建的 map
		static StringStringMap Make();
		/// @brief 释放该 map 在 PVZ 占用的内存空间
		void Free();
	};
}