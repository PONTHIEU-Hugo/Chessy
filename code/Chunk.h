#pragma once
#include "Defines.h"
#include "Instruction.h"
#include "ConstantContainer.h"

struct Chunk
{
private:
	vector<Instruction> instructions;
	vector<ConstantContainer> constants;

public:
	u8 push_instruction(const Instruction instructionCode);
	u8 push_constant(const ConstantContainer constantValue);

	Instruction& read_instruction(const size index) { return instructions[index]; }
	ConstantContainer& read_constants(const size index) { return constants[index]; }

	size instruction_size() { return instructions.size(); }
};