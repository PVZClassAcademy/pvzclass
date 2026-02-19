#pragma once

namespace LawnMowerType
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

namespace [[deprecated("Use LawnMowerType instead (fix typo: Lawnmover -> LawnMower)")]] LawnmoverType
{
    enum [[deprecated("Use LawnMowerType::LawnMowerType instead (fix typo: Lawnmover -> LawnMower)")]] LawnmoverType
    {
        LawnCleaner,
        PoolCleaner,
        RoofCleaner,
        Trickedout,
    };

    extern const char* ToString(LawnMowerType::LawnMowerType lawnmoert);
}
