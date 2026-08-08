#pragma once

namespace PVZEnum
{
    enum LawnMowerType
    {
        LawnCleaner,
        PoolCleaner,
        RoofCleaner,
        Trickedout,
    };

    extern const char* ToString(LawnMowerType lawnmowert);
}
