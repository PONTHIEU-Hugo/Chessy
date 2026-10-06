#pragma once
#include "Defines.h"
#include "Position.h"


enum class PieceType : u8
{
};

struct Piece
{
    Position position;
    PieceType type;
    bool owner;
};

inline bool operator==(const Piece& a, const Piece& b)
{
    return a.position == b.position
        && a.type     == b.type
        && a.owner    == b.owner;
}

inline bool operator!=(const Piece& a, const Piece& b)
{
    return !(a == b);
}