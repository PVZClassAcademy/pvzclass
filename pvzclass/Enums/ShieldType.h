#pragma once
namespace ShieldType
{

	enum ShieldType
	{
		None,
		/// @deprecated 请改用 None
		ZombieAccessoriesType2None = 0,
		ScreenDoor,
		Newspaper,
		Ladder,
	};

	extern const char* ToString(ShieldType zombieat2);

}

#define ZombieAccessoriesType2 ShieldType