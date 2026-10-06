#pragma once
#include "Defines.h"

enum class OpCode : u8
{
	_MOV, _LOADC,

	_ADD, _SUB, _MUL, _DIV, _POW,

	_AND, _OR, _XOR, _NOT,
	_CMP,

	_JMP, _PRINT,

	_END
};


struct Instruction
{
	OpCode operation;
	u8 regA;
	u8 regB;
	u8 regC;
};