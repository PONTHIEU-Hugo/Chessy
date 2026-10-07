#pragma once 
#include "Defines.h"
#include "OpCode.h"

struct Instruction
{
	OpCode operation;
	u8 regA;
	u8 regB;
	u8 regC;
};