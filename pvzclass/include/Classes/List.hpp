#pragma once
#include "../../PVZ.h"
#include "TodAllocator.hpp"

namespace PVZ
{
	/// @brief int 链表的节点
	/// @see IntList
	class IntListNode : public BaseClass
	{
	public:
		IntListNode(uint32_t address) : BaseClass(address) {};
		uint32_t GetBaseAddress();
		/// @brief 当前节点存储的值
		INT_SIMPLE_PROPERTY(Value, 0);
		/// @brief 当前节点存储的值（视为无符号整数）
		T_SIMPLE_PROPERTY(uint32_t, UValue, 0);
		/// @brief 下一个节点
		T_SIMPLE_PROPERTY(IntListNode, Next, 4);
		/// @brief 上一个节点
		T_SIMPLE_PROPERTY(IntListNode, Prev, 8);
	};

	/// @brief int 链表
	class IntList : public BaseClass
	{
	public:
		IntList(uint32_t address) : BaseClass(address) {};
		uint32_t GetBaseAddress();
		/// @brief 头节点
		T_SIMPLE_PROPERTY(IntListNode, Head, 0);
		/// @brief 尾节点
		T_SIMPLE_PROPERTY(IntListNode, Tail, 4);
		/// @brief 节点数量
		INT_SIMPLE_PROPERTY(Size, 8);
		/// @brief 链表的内存空间分配器
		T_SIMPLE_PROPERTY(TodAllocator, Allocator, 12);
		/// @brief 在链表头添加元素
		/// @param val 元素
		void AddHead(int val);
		/// @brief 在链表尾添加元素
		/// @param val 元素
		void AddTail(int val);
		/// @brief 移除所有元素
		void RemoveAll();
	};
}