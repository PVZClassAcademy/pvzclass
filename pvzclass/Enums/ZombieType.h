#pragma once
namespace ZombieType
{

	enum ZombieType
	{
		None = -1,
		Zombie,
		FlagZombie,
		ConeheadZombie,
		PoleVaultingZombie,
		BucketheadZombie,
		NewspaperZombie,
		ScreenDoorZombie,
		FootballZombie,
		DancingZombie,
		BackupDancer,
		DuckyTubeZombie,
		SnorkedZombie,
		Zomboni,
		/// @deprecated 请使用 Zomboni
		Zomboin = 12,
		ZombieBobsledTeam,
		DolphinRiderZombie,
		JackintheboxZombie,
		BalloonZombie,
		DiggerZombie,
		PogoZombie,
		ZombieYeti,
		BungeeZombie,
		LadderZombie,
		CatapultZombie,
		Gargantuar,
		Imp,
		DrZomboss,
		PeashooterZombie,
		WallnutZombie,
		JalapenoZombie,
		GatlingPeaZombie,
		SquashZombie,
		TallnutZombie,
		Gigagargantuar,
	};

	const char* ToString(ZombieType zombiet);

}