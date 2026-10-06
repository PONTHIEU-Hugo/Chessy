#include "Chunk.h"

u8 Chunk::push_instruction(const Instruction instructionCode)
{
    instructions.push_back(instructionCode);
    return (u8)instructions.size() - 1;
}

u8 Chunk::push_constant(const ConstantContainer constantValue)
{
    constants.push_back(constantValue);
    return (u8)constants.size() - 1;
}