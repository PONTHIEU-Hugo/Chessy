#pragma once
#include "Defines.h"

struct Move
{
    u8 x, y;
};

inline bool operator==(const Move& a, const Move& b)
{
    return a.x == b.x && a.y == b.y;
}

inline bool operator!=(const Move& a, const Move& b)
{
    return !(a == b);
}
