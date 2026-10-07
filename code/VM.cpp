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
        case OpCode::_LOAD: // TODO: Implement LOAD
        {
            break;
        }
        case OpCode::_STORE: // TODO: Implement STORE
        {
            break;
        }
        case OpCode::_PUSH:
        {
            m_Stack.push_back(m_Registers[rInstruction.regA]);
            break;
        }
        case OpCode::_POP:
        {
            m_Registers[rInstruction.regA] = m_Stack[m_Stack.size() - 1];
            m_Stack.pop_back();
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
        case OpCode::_MOD:
        {
            ConstantType typeB = m_Registers[rInstruction.regB].type;
            ConstantType typeC = m_Registers[rInstruction.regC].type;
            m_Registers[rInstruction.regA] = MOD_TABLE[(size)typeB][(size)typeC](m_Registers[rInstruction.regB], m_Registers[rInstruction.regC]);
            break;
        }
        case OpCode::_POW:
        {
            ConstantType typeB = m_Registers[rInstruction.regB].type;
            ConstantType typeC = m_Registers[rInstruction.regC].type;
            m_Registers[rInstruction.regA] = POW_TABLE[(size)typeB][(size)typeC](m_Registers[rInstruction.regB], m_Registers[rInstruction.regC]);
            break;
        }
        case OpCode::_NEG:
        {
            ConstantType typeB = m_Registers[rInstruction.regB].type;
            m_Registers[rInstruction.regA] = NEG_TABLE[(size)typeB](m_Registers[rInstruction.regB]);
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
        case OpCode::_SHL:
        {
            ConstantType typeB = m_Registers[rInstruction.regB].type;
            ConstantType typeC = m_Registers[rInstruction.regC].type;
            m_Registers[rInstruction.regA] = SHL_TABLE[(size)typeB][(size)typeC](m_Registers[rInstruction.regB], m_Registers[rInstruction.regC]);
            break;
        }
        case OpCode::_SHR:
        {
            ConstantType typeB = m_Registers[rInstruction.regB].type;
            ConstantType typeC = m_Registers[rInstruction.regC].type;
            m_Registers[rInstruction.regA] = SHR_TABLE[(size)typeB][(size)typeC](m_Registers[rInstruction.regB], m_Registers[rInstruction.regC]);
            break;
        }
        case OpCode::_CMP_EQ:
        {
            ConstantType typeB = m_Registers[rInstruction.regB].type;
            ConstantType typeC = m_Registers[rInstruction.regC].type;
            m_Registers[rInstruction.regA] = CMPEQ_TABLE[(size)typeB][(size)typeC](m_Registers[rInstruction.regB], m_Registers[rInstruction.regC]);
            break;
        }
        case OpCode::_CMP_NE:
        {
            ConstantType typeB = m_Registers[rInstruction.regB].type;
            ConstantType typeC = m_Registers[rInstruction.regC].type;
            m_Registers[rInstruction.regA] = CMPNE_TABLE[(size)typeB][(size)typeC](m_Registers[rInstruction.regB], m_Registers[rInstruction.regC]);
            break;
        }
        case OpCode::_CMP_LT:
        {
            ConstantType typeB = m_Registers[rInstruction.regB].type;
            ConstantType typeC = m_Registers[rInstruction.regC].type;
            m_Registers[rInstruction.regA] = CMPLT_TABLE[(size)typeB][(size)typeC](m_Registers[rInstruction.regB], m_Registers[rInstruction.regC]);
            break;
        }
        case OpCode::_CMP_LE:
        {
            ConstantType typeB = m_Registers[rInstruction.regB].type;
            ConstantType typeC = m_Registers[rInstruction.regC].type;
            m_Registers[rInstruction.regA] = CMPLE_TABLE[(size)typeB][(size)typeC](m_Registers[rInstruction.regB], m_Registers[rInstruction.regC]);
            break;
        }
        case OpCode::_CMP_GT:
        {
            ConstantType typeB = m_Registers[rInstruction.regB].type;
            ConstantType typeC = m_Registers[rInstruction.regC].type;
            m_Registers[rInstruction.regA] = CMPGT_TABLE[(size)typeB][(size)typeC](m_Registers[rInstruction.regB], m_Registers[rInstruction.regC]);
            break;
        }
        case OpCode::_CMP_GE:
        {
            ConstantType typeB = m_Registers[rInstruction.regB].type;
            ConstantType typeC = m_Registers[rInstruction.regC].type;
            m_Registers[rInstruction.regA] = CMPGE_TABLE[(size)typeB][(size)typeC](m_Registers[rInstruction.regB], m_Registers[rInstruction.regC]);
            break;
        }

        case OpCode::_PRINT:
            PRINT_TABLE[(size)m_Registers[rInstruction.regA].type](m_Registers[rInstruction.regA]);
            break;
        case OpCode::_HALT:
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