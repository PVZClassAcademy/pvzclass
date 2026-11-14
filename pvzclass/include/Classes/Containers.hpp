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

	/// @brief 存有 int 的 vector 容器
	class IntVector : public BaseClass
	{
	public:
		IntVector(uint32_t address) : BaseClass(address) {};
		T_READONLY_PROPERTY(uint32_t, First, __get_First, 4);
		T_READONLY_PROPERTY(uint32_t, Last, __get_Last, 8);
		/// @brief 创建一个空的 vector
		static IntVector Make();
		/// @brief 释放该 vector 在 PVZ 占用的内存空间
		/// @attention 只有通过 Make 创建的 IntVector 才应该使用该函数销毁。
		void Free();
		/// @brief 判断该 vector 是否为空
		/// @return 该 vector 是否为空
		bool is_empty();
		/// @brief 获取元素数量
		size_t size();
		/// @brief 在末尾添加一个元素
		/// @param val 添加的元素
		void push_back(int val);
		/// @brief 移除末尾的元素
		void pop_back();
		/// @brief 获取指定下标的值
		/// @param 下标
		/// @note 与重载的 [] 不同，该函数的读取不会检查上下界
		/// @return 对应的值
		int get(int index);
		/// @brief 获取指定下标的值
		/// @param 下标
		/// @return 对应的值
		int operator[](int index);
		/// @brief 调整容量，使其包含指定数量的元素
		/// @param count 元素数
		void resize(int count);
	};
}