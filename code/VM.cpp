#include "VM.h"


void VM::Run()
{
    size instructionSize = m_pChunk->instruction_size();
    m_InstructionIndex = 0;
    while(m_InstructionIndex < instructionSize)
    {
        Instruction& rInstruction = Read_Instruction();
        switch (rInstruction.operation)
        {
        case OpCode::_MOV:
        {
            m_Registers[rInstruction.regA] = m_Registers[rInstruction.regB];
            break;
        }
        case OpCode::_LOADC:
        {
            m_Registers[rInstruction.regA] = m_pChunk->read_constants(rInstruction.regB);
            break;
        }

        case OpCode::_ADD:
        {
            ConstantType typeB = m_Registers[rInstruction.regB].type;
            ConstantType typeC = m_Registers[rInstruction.regC].type;
            m_Registers[rInstruction.regA] = ADD_TABLE[(size)typeB][(size)typeC](m_Registers[rInstruction.regB], m_Registers[rInstruction.regC]);
            break;
        }
        case OpCode::_SUB:
        {
            ConstantType typeB = m_Registers[rInstruction.regB].type;
            ConstantType typeC = m_Registers[rInstruction.regC].type;
            m_Registers[rInstruction.regA] = SUB_TABLE[(size)typeB][(size)typeC](m_Registers[rInstruction.regB], m_Registers[rInstruction.regC]);
            break;
        }
        case OpCode::_MUL:
        {
            ConstantType typeB = m_Registers[rInstruction.regB].type;
            ConstantType typeC = m_Registers[rInstruction.regC].type;
            m_Registers[rInstruction.regA] = MUL_TABLE[(size)typeB][(size)typeC](m_Registers[rInstruction.regB], m_Registers[rInstruction.regC]);
            break;
        }
        case OpCode::_DIV:
        {
            ConstantType typeB = m_Registers[rInstruction.regB].type;
            ConstantType typeC = m_Registers[rInstruction.regC].type;
            m_Registers[rInstruction.regA] = DIV_TABLE[(size)typeB][(size)typeC](m_Registers[rInstruction.regB], m_Registers[rInstruction.regC]);
            break;
        }
        case OpCode::_POW:
        {
            ConstantType typeB = m_Registers[rInstruction.regB].type;
            ConstantType typeC = m_Registers[rInstruction.regC].type;
            m_Registers[rInstruction.regA] = POW_TABLE[(size)typeB][(size)typeC](m_Registers[rInstruction.regB], m_Registers[rInstruction.regC]);
            break;
        }

        case OpCode::_AND:
        {
            ConstantType typeB = m_Registers[rInstruction.regB].type;
            ConstantType typeC = m_Registers[rInstruction.regC].type;
            m_Registers[rInstruction.regA] = AND_TABLE[(size)typeB][(size)typeC](m_Registers[rInstruction.regB], m_Registers[rInstruction.regC]);
            break;
        }
        case OpCode::_OR:
        {
            ConstantType typeB = m_Registers[rInstruction.regB].type;
            ConstantType typeC = m_Registers[rInstruction.regC].type;
            m_Registers[rInstruction.regA] = OR_TABLE[(size)typeB][(size)typeC](m_Registers[rInstruction.regB], m_Registers[rInstruction.regC]);
            break;
        }
        case OpCode::_XOR:
        {
            ConstantType typeB = m_Registers[rInstruction.regB].type;
            ConstantType typeC = m_Registers[rInstruction.regC].type;
            m_Registers[rInstruction.regA] = XOR_TABLE[(size)typeB][(size)typeC](m_Registers[rInstruction.regB], m_Registers[rInstruction.regC]);
            break;
        }
        case OpCode::_NOT:
        {
            ConstantType typeB = m_Registers[rInstruction.regB].type;
            m_Registers[rInstruction.regA] = NOT_TABLE[(size)typeB](m_Registers[rInstruction.regB]);
            break;
        }
        case OpCode::_CMP:
        {
            // TODO: Implement CMP operand
            break;
        }

        // case OpCode::_JMP:
        //     m_InstructionIndex = m_Registers[rInstruction.regA];
        //     break;
        case OpCode::_PRINT:
            PRINT_TABLE[(size)m_Registers[rInstruction.regA].type](m_Registers[rInstruction.regA]);
            // std::cout << m_Registers[rInstruction.regA];
            break;
            
        case OpCode::_END:
            return;
        
        default:
            break;
        }
    }
}

Instruction &VM::Read_Instruction()
{
    size_t current = m_InstructionIndex;
    m_InstructionIndex++;
    return m_pChunk->read_instruction(current);
}