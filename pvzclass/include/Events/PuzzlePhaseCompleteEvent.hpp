#pragma once
#include "DLLEvent.h"

/// @brief 解谜关卡完成事件
/// @param 触发事件时的 Challenge
class PuzzlePhaseCompleteEvent : public DLLEventTemplate<0x429980, 6, REG_ECX>
{
public:
	PuzzlePhaseCompleteEvent(const char* str) : DLLEventTemplate() { Init(str); };
	PuzzlePhaseCompleteEvent(int address) : DLLEventTemplate() { Init(address); };
	PuzzlePhaseCompleteEvent() : DLLEventTemplate() { Init("onPuzzlePhaseComplete"); };
};

namespace PVZEvent
{
	/// @brief 解谜关卡完成，判断是否生成过关物品事件
	/// @param 触发事件时的 Challenge，过关物品生成的 X 方向格位，过关物品生成的 Y 方向格位
	/// @return 由 ThreeState::ThreeState 表示的，是否生成过关物品。
	class PuzzlePhaseCompleteBonusEvent_ts : public ThreeStateEventTemplate<0x429998, 8, 0x4299C2, 0x429AAE, MEM_ESP_ADD(0x34), REG_EDI, REG_ECX>
	{
	public:
		PuzzlePhaseCompleteBonusEvent_ts(const char* str) : ThreeStateEventTemplate() { Init(str); };
		PuzzlePhaseCompleteBonusEvent_ts(int address) : ThreeStateEventTemplate() { Init(address); };
		PuzzlePhaseCompleteBonusEvent_ts() : ThreeStateEventTemplate() { Init("onPuzzlePhaseCompleteBonus"); };
	};
}