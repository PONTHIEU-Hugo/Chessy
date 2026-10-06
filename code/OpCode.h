#pragma once
#include "Defines.h"

enum class OpCode : u8
{
    _MOV, _LOADC, _LOAD, _PUSH, _POP,

    _ADD, _SUB, _MUL, _DIV, _POW,

    _AND, _OR, _XOR, _NOT,
    _CMP,

    _JMP, _PRINT,

    _END
};