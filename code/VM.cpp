#include "VM.h"

VM::VM()
{
    m_Stack.resize(stackAllocationSize);
    m_Frames.resize(framesAllocationSize);
}

void VM::Run()
{
    size instructionSize = m_pChunk->instruction_size();
    m_InstructionIndex = 0;
    m_StackIndex = 0;
    m_FramesIndex = 0;
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
        case OpCode::_LOAD:
        {
            StackFrame& rFrame = m_Frames[m_FramesIndex - 1];
            if(rInstruction.regB > rFrame.frameSize)
            {
                std::cout << "Index in frame out of range" << std::endl;
                exit(400); // TODO: set proper error code
            }
            size element = rFrame.beginIndex + rInstruction.regB;
            m_Registers[rInstruction.regA] = m_Stack[element];
            break;
        }
        case OpCode::_STORE: // TODO: Implement STORE
        {
            StackFrame& rFrame = m_Frames[m_FramesIndex - 1];
            if(rInstruction.regA > rFrame.frameSize)
            {
                std::cout << "Index in frame out of range" << std::endl;
                exit(400); // TODO: set proper error code
            }
            size element = rFrame.beginIndex + rInstruction.regA;
            m_Stack[element] = m_Registers[rInstruction.regB];
            break;
        }
        case OpCode::_PUSH:
        {
            if(m_Frames.size() < m_FramesIndex + 1)
                m_Frames.resize(m_Frames.size() + framesAllocationSize);
            if(m_Stack.size() < m_StackIndex + 1)
                m_Stack.resize(m_Stack.size() + stackAllocationSize);
                
            m_Frames[m_FramesIndex] = { m_StackIndex, 1 };
            m_FramesIndex++;
            m_Stack[m_StackIndex] = m_Registers[rInstruction.regA];
            m_StackIndex++;
            break;
        }
        case OpCode::_POP:
        {
            m_StackIndex--;
            m_FramesIndex--;
            if(m_Frames[m_FramesIndex].frameSize > 1)
            {
                std::cout << "Access violation" << std::endl;
                exit(400); // TODO: set proper error code
            }
            m_Registers[rInstruction.regA] = m_Stack[m_StackIndex];
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

        case OpCode::_CALL:
        {
            FunctionInfo& func = m_pChunk->read_functions(rInstruction.regA);
            m_OldInstructionIndex.push_back(m_InstructionIndex);
            m_InstructionIndex = func.entry;
            m_FramesIndex++;
            m_Frames[m_FramesIndex] = { m_StackIndex, func.frame_size };
            m_StackIndex += func.frame_size;
            break;
        }
        case OpCode::_RET:
        {
            m_InstructionIndex = m_OldInstructionIndex[m_OldInstructionIndex.size() - 1];
            m_OldInstructionIndex.pop_back();
            m_FramesIndex--;
            StackFrame& rFrame = m_Frames[m_FramesIndex];
            m_Registers[0] = m_Stack[rFrame.beginIndex];
            m_StackIndex = rFrame.beginIndex;
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