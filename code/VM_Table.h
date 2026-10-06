#pragma once
#include "Defines.h"
#include "ConstantContainer.h"
#include "VM_Operation.h"

using OperationPtr = ConstantContainer(*)(const ConstantContainer&, const ConstantContainer&);
using OperationPtrSolo = ConstantContainer(*)(const ConstantContainer&);
using NoReturnOperationPtrSolo = void(*)(const ConstantContainer&);

// Add operand
template<size iSize, size... jSize>
constexpr array<OperationPtr, sizeof...(jSize)> CreateAddLine(std::index_sequence<jSize...>);

template<size... iSize, size... jSize>
constexpr array<array<OperationPtr, sizeof...(jSize)>, sizeof...(iSize)> CreateAddTable(std::index_sequence<iSize...>, std::index_sequence<jSize...> js);

// Sub operand
template<size iSize, size... jSize>
constexpr array<OperationPtr, sizeof...(jSize)> CreateSubLine(std::index_sequence<jSize...>);

template<size... iSize, size... jSize>
constexpr array<array<OperationPtr, sizeof...(jSize)>, sizeof...(iSize)> CreateSubTable(std::index_sequence<iSize...>, std::index_sequence<jSize...> js);

// Mul type
template <size iSize, size... jSize>
constexpr array<OperationPtr, sizeof...(jSize)> CreateMulLine(std::index_sequence<jSize...>);

template<size... iSize, size... jSize>
constexpr array<array<OperationPtr, sizeof...(jSize)>, sizeof...(iSize)> CreateMulTable(std::index_sequence<iSize...>, std::index_sequence<jSize...> js);

// Div type
template<size iSize, size... jSize>
constexpr array<OperationPtr, sizeof...(jSize)> CreateDivLine(std::index_sequence<jSize...>);

template<size... iSize, size... jSize>
constexpr array<array<OperationPtr, sizeof...(jSize)>, sizeof...(iSize)> CreateDivTable(std::index_sequence<iSize...>, std::index_sequence<jSize...> js);

// Pow type
template<size iSize, size... jSize>
constexpr array<OperationPtr, sizeof...(jSize)> CreatePowLine(std::index_sequence<jSize...>);

template<size... iSize, size... jSize>
constexpr array<array<OperationPtr, sizeof...(jSize)>, sizeof...(iSize)> CreatePowTable(std::index_sequence<iSize...>, std::index_sequence<jSize...> js);


// And type
template<size iSize, size... jSize>
constexpr array<OperationPtr, sizeof...(jSize)> CreateAndLine(std::index_sequence<jSize...>);

template<size... iSize, size... jSize>
constexpr array<array<OperationPtr, sizeof...(jSize)>, sizeof...(iSize)> CreateAndTable(std::index_sequence<iSize...>, std::index_sequence<jSize...> js);

// Or type
template<size iSize, size... jSize>
constexpr array<OperationPtr, sizeof...(jSize)> CreateOrLine(std::index_sequence<jSize...>);

template<size... iSize, size... jSize>
constexpr array<array<OperationPtr, sizeof...(jSize)>, sizeof...(iSize)> CreateOrTable(std::index_sequence<iSize...>, std::index_sequence<jSize...> js);

// Xor type
template<size iSize, size... jSize>
constexpr array<OperationPtr, sizeof...(jSize)> CreateXorLine(std::index_sequence<jSize...>);

template<size... iSize, size... jSize>
constexpr array<array<OperationPtr, sizeof...(jSize)>, sizeof...(iSize)> CreateXorTable(std::index_sequence<iSize...>, std::index_sequence<jSize...> js);

// Not type
template<size... iSize>
constexpr array<OperationPtrSolo, sizeof...(iSize)> CreateNotTable(std::index_sequence<iSize...>);


// Print type
template<size... iSize>
constexpr array<NoReturnOperationPtrSolo, sizeof...(iSize)> CreatePrintTable(std::index_sequence<iSize...>);

#include "VM_Table.inl"