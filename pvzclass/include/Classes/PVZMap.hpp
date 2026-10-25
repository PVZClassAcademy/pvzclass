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
		/// @brief 向 map 插入一个键值对
		/// @param key 键
		/// @param value 值
		/// @return 是否成功插入。若 map 中的键已有对应的值，则插入失败。
		bool Insert(PVZString key, PVZString value);
	};
}