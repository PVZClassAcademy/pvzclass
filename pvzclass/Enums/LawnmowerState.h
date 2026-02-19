#pragma once

namespace LawnMowerState
{
    enum LawnMowerState
    {
        RollingIn,
        Ready,
        Triggered,
        Squished,
    };

    extern const char* ToString(LawnMowerState lawnmowert);
}

namespace [[deprecated("Use LawnMowerState instead (fix typo: Lawnmover -> LawnMower)")]] LawnmoverState
{
    enum [[deprecated("Use LawnMowerState::LawnMowerState instead (fix typo: Lawnmover -> LawnMower)")]] LawnmoverState 
    {
        RollingIn,
        Ready,
        Triggered,
        Squished,
    };

    extern const char* ToString(LawnMowerState::LawnMowerState lawnmoert);
}
