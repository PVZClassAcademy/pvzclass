#pragma once
#include "DLLEvent.h"

/// @brief 游戏模式特性更新事件。
/// @param 触发事件的 Challenge
/// @return 是否按原版模式更新事件。
class ChallengeUpdateEvent : public BoolDLLEventTemplate<0x4246B0, 6, 0x42470B, REG_EAX>
{
public:
	ChallengeUpdateEvent(const char* str) : BoolDLLEventTemplate() { Init(str); };
	ChallengeUpdateEvent(int address) : BoolDLLEventTemplate() { Init(address); };
	ChallengeUpdateEvent() : BoolDLLEventTemplate() { Init("onChallengeUpdate"); };
};


namespace PVZEvent
{
	/// @brief 游戏模式特殊的鼠标按下结算事件。
	/// @param 触发事件的 Challenge, 点击 X 坐标，点击 Y 坐标，点击次数，鼠标按下的 HitResult
	/// @note 若返回值不为 ThreeState::None，原生的结算流程会失效
	/// @return 使用 ThreeState 表示的，是否结算其余鼠标按下的结算流程
	class ChallengeMouseDownEvent_ts : public ThreeStateEventTemplate<0x421F1C, 6, 0x421F77, 0x4221A5, REG_EAX, MEM_ESP_ADD(0x48), MEM_ESP_ADD(0x48), MEM_ESP_ADD(0x48), REG_EBP>
	{
	public:
		ChallengeMouseDownEvent_ts(const char* str) : ThreeStateEventTemplate() { Init(str); };
		ChallengeMouseDownEvent_ts(int address) : ThreeStateEventTemplate() { Init(address); };
		ChallengeMouseDownEvent_ts() : ThreeStateEventTemplate() { Init("onChallengeMouseDown"); };
	};
}