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
inline static constexpr array<array<OperationPtr, TABLE_COUNT>, TABLE_COUNT> POW_TABLE = CreatePowTable(
    std::make_index_sequence<TABLE_COUNT>{},
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
inline static constexpr array<NoReturnOperationPtrSolo, TABLE_COUNT> PRINT_TABLE = CreatePrintTable(
    std::make_index_sequence<TABLE_COUNT>{}
);

constexpr int registerAmount = 256;


class VM
{
private:
	array<ConstantContainer, registerAmount> m_Registers;

	size m_InstructionIndex;

	Chunk* m_pChunk;

public:
	void SetChunk(Chunk* pChunk) { m_pChunk = pChunk; }

	void Run();

private:
	Instruction& Read_Instruction();

	void Add(const Instruction& rInstruction);
};
