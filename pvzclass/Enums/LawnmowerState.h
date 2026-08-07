#pragma once

namespace PVZEnum
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
