#pragma once
#include "../PVZ.h"

namespace PVZ
{
	class CutScene : public BaseClass
	{
	public:
		CutScene(int address);
		INT_SIMPLE_PROPERTY(mCutsceneTime, 0x08);
		INT_SIMPLE_PROPERTY(mSodTime, 0x0C);
		INT_SIMPLE_PROPERTY(mGraveStoneTime, 0x10);
		INT_SIMPLE_PROPERTY(mReadySetPlantTime, 0x14);
		INT_SIMPLE_PROPERTY(mFogTime, 0x18);
		INT_SIMPLE_PROPERTY(mBossTime, 0x1C);
		INT_SIMPLE_PROPERTY(mCrazyDaveTime, 0x20);
		INT_SIMPLE_PROPERTY(mLawnMowerTime, 0x24);
		INT_SIMPLE_PROPERTY(mCrazyDaveDialogStart, 0x28);

		T_SIMPLE_PROPERTY(bool, mSeedChoosing, 0x2C);
		T_SIMPLE_PROPERTY(bool, mPreloaded, 0x34);
		/// @brief 是否已经放置街上的僵尸
		T_SIMPLE_PROPERTY(bool, mPlacedZombies, 0x35);
		T_SIMPLE_PROPERTY(bool, mPlacedLawnItems, 0x36);

		/// @brief 放置街上的僵尸
		/// @note x 和 y 是街上的坐标，不是场地中的格子坐标
		/// @note x 和 y 的取值应该是 0,1,2,3,4
		/// @note 在植物僵尸 2 关卡中，创建鸭子救生圈僵尸会转化为创建豌豆射手僵尸。
		void PlaceStreetZombie(ZombieType::ZombieType type, int x, int y);
		/// @brief 寻找空位放置街上的僵尸
		/// @param type 僵尸类型
		/// @param grid 该格子是否已被占用
		/// @note grid 数组会被实时修改更新
		void PlaceStreetZombie(ZombieType::ZombieType type, bool grid[5][5]);
		/// @brief 取消过场动画
		void CancelIntro();
	};
}
