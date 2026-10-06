#pragma once
#include "Defines.h"
#include "Bitboard.h"
#include "Piece.h"
#include "Position.h"
#include "Move.h"

enum class ConstantType : u8
{
    _BOOL,
    _I8, _I16, _I32, _I64,
    _U8, _U16, _U32, _U64,
    _STRING,
    _BITBOARD, _PIECE,
    _POSITION, _MOVE,

    _COUNT
};

struct ConstantContainer
{
public:
    ConstantType type;
    union
    {
        bool as_bool;

        i8 as_i8;
        i16 as_i16;
        i32 as_i32;
        i64 as_i64;

        u8 as_u8;
        u16 as_u16;
        u32 as_u32;
        u64 as_u64;

        str* as_str;

        Bitboard as_bitboard;
        Piece as_piece;
        Position as_position;
        Move as_move;
    } data;
};