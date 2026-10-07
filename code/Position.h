#pragma once
#include "Defines.h"

struct Position
{
    u8 x, y;
};

inline bool operator==(const Position& a, const Position& b)
{
    return a.x == b.x && a.y == b.y;
}

inline bool operator!=(const Position& a, const Position& b)
{
    return !(a == b);
}
