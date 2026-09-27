#pragma once
#include "../PVZ.h"

namespace PVZ
{
	template<typename T>
	using UnsafeItem = typename Array<T>::Item;

	template<typename T>
	class SafeItem : public BaseClass
	{
	public:
		explicit SafeItem(uint32_t address) : BaseClass(address) {};

		const SafeItem& operator=(const T val)
		{
			PVZ::Memory::WriteMemory<T>(this->BaseAddress, val);
			return *this;
		}
		/// @brief 获取该元素的值
		T get() const { return PVZ::Memory::ReadMemory<T>(this->BaseAddress); }
	};

	/// @warning 请勿在程序资源文件涉及非 ASCII 字符时改变此变量的值。
	inline auto IsLocaleChanged = UnsafeItem<bool>(0x6A66F4);
	/// @brief 是否展示过更多阳光的教程。
	inline auto ShownMoreSunTutorial = UnsafeItem<bool>(0x6A9EA9);
	/// @brief 是否开启合作伙伴模式。该模式下，游戏程序将会为空存档生成多个进度的存档（含金葵存档）。
	inline auto IsPartnerBuild = UnsafeItem<bool>(0x6A9EA9);
	/// @brief 是否开启快速模式
	inline auto FastMo = UnsafeItem<bool>(0x6A9EAB);
	/// @brief 开启加速模式时的加速倍率
	inline auto FastUpdateCount = SafeItem<int>(0x4526D3);

	class Resource
	{
	public:
		static Image IMAGE_BLANK;
		static void InitImages();
		/// @brief 加载指定文件中的字符串（同 LawnString）
		/// @param str 文件名
		static void LoadStringList(const char* str);
	};
}