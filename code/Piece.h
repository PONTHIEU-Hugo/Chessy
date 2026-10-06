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