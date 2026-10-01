#pragma once
#include "DLLEvent.h"

namespace PVZEvent
{
	/// @brief 僵尸是否应当掉落物品事件
	/// @note 该事件的触发优先级比 ZombieDropLootEvent 低
	/// @param 触发事件的僵尸所处的 Board、触发事件的僵尸
	/// @return 由 ThreeState::ThreeState 表示的，是否掉落物品
	class ZombieShouldDropLootPieceEvent_ts : public ThreeStateEventTemplate<0x53020D, 5, 0x530244, 0x5302DD, REG_EBX, REG_ECX>
	{
	public:
		ZombieShouldDropLootPieceEvent_ts(const char* str) : ThreeStateEventTemplate() { Init(str); };
		ZombieShouldDropLootPieceEvent_ts(int address) : ThreeStateEventTemplate() { Init(address); };
		ZombieShouldDropLootPieceEvent_ts() : ThreeStateEventTemplate() { Init("ZombieShouldDropLootPiece"); };
	};

	namespace Dancer
	{
		/// @brief 舞王开始召唤僵尸事件
		/// @param 触发事件的舞王僵尸
		/// @return 是否进行此次召唤
		class SummonStartEvent : public BoolDLLEventTemplate<0x528970, 10, 0x52BA3D, REG_ESI>
		{
		public:
			SummonStartEvent(const char* str) : BoolDLLEventTemplate() { Init(str); };
			SummonStartEvent(int address) : BoolDLLEventTemplate() { Init(address); };
			SummonStartEvent() : SummonStartEvent("onDancerSummonStart") {};
		};
	}

	namespace Zomboni
	{
		/// @brief 冰车僵尸更新冰道事件
		/// @param 触发事件的僵尸
		/// @return 是否更新冰道。
		class UpdateIceEvent : public BoolDLLEventTemplate<0x52A865, 6, 0x52A8D6, REG_ESI>
		{
		public:
			UpdateIceEvent(const char* str) : BoolDLLEventTemplate() { Init(str); };
			UpdateIceEvent(int address) : BoolDLLEventTemplate() { Init(address); };
			UpdateIceEvent() : UpdateIceEvent("onZomboniUpdateIce") {};
		};
	}

	namespace BobsledTeam
	{
		/// @brief 雪橇处于冰道外事件。
		/// @param 触发事件的僵尸
		/// @return 是否进行原版的雪橇损坏结算流程。
		class OutofIceEvent : public BoolDLLEventTemplate<0x528218, 5, 0x52822D, REG_ESI>
		{
		public:
			OutofIceEvent() : BoolDLLEventTemplate() { Init("onBobsledTeamOutofIce"); };
			OutofIceEvent(const char* str) : BoolDLLEventTemplate() { Init(str); };
			OutofIceEvent(int address) : BoolDLLEventTemplate() { Init(address); };
		};
	}

	namespace Digger
	{
		/// @brief 矿工僵尸检查是否出土的事件
		/// @note 该事件与矿工僵尸被吸取镐子的事件无关
		/// @note 使用该事件会导致原始判定失效
		/// @note 该事件也可用于矿工僵尸在地底挖掘时的更新
		/// @param 触发事件的僵尸
		/// @return 是否出土
		class CheckRisingEvent : public DiversionEventTemplate<0x528324, 6, 0x528338, 0x528757, REG_EDI>
		{
		public:
			CheckRisingEvent() : DiversionEventTemplate() { Init("IsDiggerRising"); };
			CheckRisingEvent(const char* str) : DiversionEventTemplate() { Init(str); };
			CheckRisingEvent(int address) : DiversionEventTemplate() { Init(address); };
		};

		/// @brief 矿工僵尸丢失镐子事件
		/// @param 触发事件的矿工僵尸
		class LoseAxeAfterEvent : public DLLEventTemplate<0x5282FE, 5, REG_ESI>
		{
		public:
			LoseAxeAfterEvent(const char* str) : DLLEventTemplate() { Init(str); };
			LoseAxeAfterEvent(int address) : DLLEventTemplate() { Init(address); };
			LoseAxeAfterEvent() : LoseAxeAfterEvent("onDiggerLoseAxeAfter") {};
		};
	}
	namespace Ladder
	{
		/// @brief 扶梯僵尸搭梯后事件
		/// @param 触发事件的僵尸
		/// @return 是否失去防具
		class PlaceLadderAfterEvent : public BoolDLLEventTemplate<0x52AA1A, 5, 0x52AA1F, REG_EBX>
		{
		public:
			PlaceLadderAfterEvent(const char* str) : BoolDLLEventTemplate() { Init(str); };
			PlaceLadderAfterEvent(int address) : BoolDLLEventTemplate() { Init(address); };
			PlaceLadderAfterEvent() : PlaceLadderAfterEvent("onLadderPlacedAfter") {};
		};

		/// @brief 扶梯僵尸搭梯后事件
		/// @param 触发事件的僵尸、僵尸生成的梯子
		class PlaceLadderEvent : public DLLEventTemplate<0x52A9FD, 5, REG_EAX, REG_EBX>
		{
		public:
			PlaceLadderEvent(const char* str) : DLLEventTemplate() { Init(str); };
			PlaceLadderEvent(int address) : DLLEventTemplate() { Init(address); };
			PlaceLadderEvent() : PlaceLadderEvent("onLadderPlaced") {};
		};
	}
	namespace Catapult
	{
		class DeathEvent : public BoolDLLEventTemplate<0x52EC00, 6, 0x52ED9E, 0x24, REG_EAX>
		{
		public:
			DeathEvent(const char* str) : BoolDLLEventTemplate() { Init(str); };
			DeathEvent(int address) : BoolDLLEventTemplate() { Init(address); };
			DeathEvent() : DeathEvent("onZombieCatapultDie") {};
		};
	}

	namespace Gargantuar
	{
		/// @brief 修复魅惑巨人小鬼落点
		class JudgeXFixEvent : public DLLEvent
		{
		public:
			JudgeXFixEvent()
			{
				hookAddress = 0x526EEA;
				rawlen = 6;
				BYTE code[] =
				{
					CMP_BYTE_PTR_EUX_ADD__V(REG_EBX, 0x0B8, 0),
					JE(8),
					FCHS,
					FADD_PTR_ADDR(0x67A114), // 800
					CMP_EUX(REG_EAX, 0x45)
				};
				start(STRING(code));
			}
		};
	}

	namespace PeaZombie
	{
		/// @brief 豌豆僵尸判定是否发射子弹事件。
		/// @note 不会影响射击动作，只影响子弹生成。
		/// @param 触发事件的僵尸
		/// @retval true 是否发射子弹
		class JudgeShootEvent : public DiversionEventTemplate<0x527459, 6, 0x52745F, 0x5275B6, REG_EDI>
		{
		public:
			JudgeShootEvent(const char* str) : DiversionEventTemplate() { Init(str); };
			JudgeShootEvent(int address) : DiversionEventTemplate() { Init(address); };
			JudgeShootEvent() : DiversionEventTemplate() { Init("onPeaZombieJudgeShoot"); };
		};
	}

	namespace JalapenoZombie
	{
		/// @brief 辣椒僵尸爆炸事件
		/// @param 触发事件的僵尸
		/// @return 是否执行烧毁植物的部分。
		class BurnStartEvent : public BoolDLLEventTemplate<0x5276BB, 7, 0x52773E, REG_EDI>
		{
		public:
			BurnStartEvent(const char* str) : BoolDLLEventTemplate() { Init(str); };
			BurnStartEvent(int address) : BoolDLLEventTemplate() { Init(address); };
			BurnStartEvent() : BurnStartEvent("onJalapenoZombieBurnStart") {};
		};
	}

	namespace GatlingPeaZombie
	{
		/// @brief 机枪僵尸判定是否发射子弹事件。
		/// @note 不会影响射击动作，只影响子弹生成。
		/// @param 触发事件的僵尸
		/// @retval true 是否发射子弹
		class GatlingZombieJudgeShootEvent : public DiversionEventTemplate<0x5277D9, 5, 0x52783D, 0x5277ED, REG_EDI>
		{
		public:
			GatlingZombieJudgeShootEvent(const char* str) : DiversionEventTemplate() { Init(str); };
			GatlingZombieJudgeShootEvent(int address) : DiversionEventTemplate() { Init(address); };
			GatlingZombieJudgeShootEvent() : DiversionEventTemplate() { Init("onGatlingZombieJudgeShoot"); };
		};
	}
}
