#pragma once
#include "../PVZ.h"

namespace PVZ
{
	/// @warning 请勿在程序资源文件涉及非 ASCII 字符时改变此变量的值。
	inline auto IsLocaleChanged = PVZ::Array<int>(0x6A66F4)[0];

	class Resource
	{
	public:
		static Image IMAGE_BLANK;
		static void InitImages();
	};
}