#pragma once
#include "Defines.h"
#include "Chunk.h"
#include "VM_Operation.h"
#include "VM_Table.h"

constexpr size TABLE_COUNT = 14;
inline static constexpr array<array<OperationPtr, TABLE_COUNT>, TABLE_COUNT> ADD_TABLE = CreateAddTable(
    std::make_index_sequence<TABLE_COUNT>{},
    std::make_index_sequence<TABLE_COUNT>{}
);
inline static constexpr array<array<OperationPtr, TABLE_COUNT>, TABLE_COUNT> SUB_TABLE = CreateSubTable(
    std::make_index_sequence<TABLE_COUNT>{},
    std::make_index_sequence<TABLE_COUNT>{}
);
inline static constexpr array<array<OperationPtr, TABLE_COUNT>, TABLE_COUNT> MUL_TABLE = CreateMulTable(
    std::make_index_sequence<TABLE_COUNT>{},
    std::make_index_sequence<TABLE_COUNT>{}
);
inline static constexpr array<array<OperationPtr, TABLE_COUNT>, TABLE_COUNT> DIV_TABLE = CreateDivTable(
    std::make_index_sequence<TABLE_COUNT>{},
    std::make_index_sequence<TABLE_COUNT>{}
);
inline static constexpr array<array<OperationPtr, TABLE_COUNT>, TABLE_COUNT> MOD_TABLE = CreateModTable(
    std::make_index_sequence<TABLE_COUNT>{},
    std::make_index_sequence<TABLE_COUNT>{}
);
inline static constexpr array<array<OperationPtr, TABLE_COUNT>, TABLE_COUNT> POW_TABLE = CreatePowTable(
    std::make_index_sequence<TABLE_COUNT>{},
    std::make_index_sequence<TABLE_COUNT>{}
);
inline static constexpr array<OperationPtrSolo, TABLE_COUNT> NEG_TABLE = CreateNegTable(
    std::make_index_sequence<TABLE_COUNT>{}
);

inline static constexpr array<array<OperationPtr, TABLE_COUNT>, TABLE_COUNT> AND_TABLE = CreateAndTable(
    std::make_index_sequence<TABLE_COUNT>{},
    std::make_index_sequence<TABLE_COUNT>{}
);
inline static constexpr array<array<OperationPtr, TABLE_COUNT>, TABLE_COUNT> OR_TABLE = CreateOrTable(
    std::make_index_sequence<TABLE_COUNT>{},
    std::make_index_sequence<TABLE_COUNT>{}
);
inline static constexpr array<array<OperationPtr, TABLE_COUNT>, TABLE_COUNT> XOR_TABLE = CreateXorTable(
    std::make_index_sequence<TABLE_COUNT>{},
    std::make_index_sequence<TABLE_COUNT>{}
);
inline static constexpr array<OperationPtrSolo, TABLE_COUNT> NOT_TABLE = CreateNotTable(
    std::make_index_sequence<TABLE_COUNT>{}
);
inline static constexpr array<array<OperationPtr, TABLE_COUNT>, TABLE_COUNT> SHL_TABLE = CreateShlTable(
    std::make_index_sequence<TABLE_COUNT>{},
    std::make_index_sequence<TABLE_COUNT>{}
);
inline static constexpr array<array<OperationPtr, TABLE_COUNT>, TABLE_COUNT> SHR_TABLE = CreateShrTable(
    std::make_index_sequence<TABLE_COUNT>{},
    std::make_index_sequence<TABLE_COUNT>{}
);
inline static constexpr array<array<OperationPtr, TABLE_COUNT>, TABLE_COUNT> CMPEQ_TABLE = CreateCmpEqTable(
    std::make_index_sequence<TABLE_COUNT>{},
    std::make_index_sequence<TABLE_COUNT>{}
);
inline static constexpr array<array<OperationPtr, TABLE_COUNT>, TABLE_COUNT> CMPNE_TABLE = CreateCmpNeTable(
    std::make_index_sequence<TABLE_COUNT>{},
    std::make_index_sequence<TABLE_COUNT>{}
);
inline static constexpr array<array<OperationPtr, TABLE_COUNT>, TABLE_COUNT> CMPLT_TABLE = CreateCmpLtTable(
    std::make_index_sequence<TABLE_COUNT>{},
    std::make_index_sequence<TABLE_COUNT>{}
);
inline static constexpr array<array<OperationPtr, TABLE_COUNT>, TABLE_COUNT> CMPLE_TABLE = CreateCmpLeTable(
    std::make_index_sequence<TABLE_COUNT>{},
    std::make_index_sequence<TABLE_COUNT>{}
);
inline static constexpr array<array<OperationPtr, TABLE_COUNT>, TABLE_COUNT> CMPGT_TABLE = CreateCmpGtTable(
    std::make_index_sequence<TABLE_COUNT>{},
    std::make_index_sequence<TABLE_COUNT>{}
);
inline static constexpr array<array<OperationPtr, TABLE_COUNT>, TABLE_COUNT> CMPGE_TABLE = CreateCmpGeTable(
    std::make_index_sequence<TABLE_COUNT>{},
    std::make_index_sequence<TABLE_COUNT>{}
);

inline static constexpr array<NoReturnOperationPtrSolo, TABLE_COUNT> PRINT_TABLE = CreatePrintTable(
    std::make_index_sequence<TABLE_COUNT>{}
);

constexpr int registerAmount = 256;
constexpr size framesAllocationSize = 64;
constexpr size stackAllocationSize = 1024;


class VM
{
private:
    struct StackFrame
    {
        size beginIndex;
        size frameSize;
    };

private:
	array<ConstantContainer, registerAmount> m_Registers;
    vector<ConstantContainer> m_Stack;
    size m_StackIndex;    
    vector<StackFrame> m_Frames;
    size m_FramesIndex;

	size m_InstructionIndex;
    vector<size> m_OldInstructionIndex;

	Chunk* m_pChunk;

public:
    VM();

	void SetChunk(Chunk* pChunk) { m_pChunk = pChunk; }

	void Run();

private:
	Instruction& Read_Instruction();
};
