#include "LawnmowerType.h"

const char* PVZEnum::ToString(PVZEnum::LawnMowerType lawnmowert)
{
	switch (lawnmowert)
	{
	case LawnMowerType::LawnCleaner:
		return "LawnCleaner";
	case LawnMowerType::PoolCleaner:
		return "PoolCleaner";
	case LawnMowerType::RoofCleaner:
		return "RoofCleaner";
	case LawnMowerType::Trickedout:
		return "Trickedout";
	default:
		return "InValid_Value_Of_LawnmowerType";
	}
}
