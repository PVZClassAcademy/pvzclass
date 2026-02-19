#include "LawnmowerState.h"

const char* LawnMowerState::ToString(LawnMowerState lawnmowert)
{
	switch (lawnmowert)
	{
	case LawnMowerState::RollingIn:
		return "RollingIn";
	case LawnMowerState::Ready:
		return "Ready";
	case LawnMowerState::Triggered:
		return "Triggered";
	case LawnMowerState::Squished:
		return "Squished";
	default:
		return "InValid_Value_Of_LawnmowerState";
	}
}
