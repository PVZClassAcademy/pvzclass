#pragma once
#include "../../PVZ.h"

namespace PVZ
{
	class TodAllocator : public BaseClass
	{
	public:
		TodAllocator(uint32_t address) : BaseClass(address) {};
		/// @brief 在全局分配器数组中查找一个分配指定大小的空间的分配器。若不存在，则创建一个。
		/// @param size 分配器的单块空间大小
		/// @return 分配器
		static TodAllocator FindGlobalAllocator(int size);
	};
}
