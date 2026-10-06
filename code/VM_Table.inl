#include "VM_Table.h"

// Add operand
template<size iSize, size... jSize>
constexpr array<OperationPtr, sizeof...(jSize)> CreateAddLine(std::index_sequence<jSize...>)
{
    return array<OperationPtr, sizeof...(jSize)>{
        &Add<static_cast<ConstantType>(iSize), static_cast<ConstantType>(jSize)>...
    };
}

template<size... iSize, size... jSize>
constexpr array<array<OperationPtr, sizeof...(jSize)>, sizeof...(iSize)> CreateAddTable(std::index_sequence<iSize...>, std::index_sequence<jSize...> js)
{
    return array<array<OperationPtr, sizeof...(jSize)>, sizeof...(iSize)>{
        CreateAddLine<iSize>(js)...
    };
}


// Sub operand
template<size iSize, size... jSize>
constexpr array<OperationPtr, sizeof...(jSize)> CreateSubLine(std::index_sequence<jSize...>)
{
    return array<OperationPtr, sizeof...(jSize)>{
        &Sub<static_cast<ConstantType>(iSize), static_cast<ConstantType>(jSize)>...
    };
}

template<size... iSize, size... jSize>
constexpr array<array<OperationPtr, sizeof...(jSize)>, sizeof...(iSize)> CreateSubTable(std::index_sequence<iSize...>, std::index_sequence<jSize...> js)
{
    return array<array<OperationPtr, sizeof...(jSize)>, sizeof...(iSize)>{
        CreateSubLine<iSize>(js)...
    };
}


// Mul type
template <size iSize, size... jSize>
constexpr array<OperationPtr, sizeof...(jSize)> CreateMulLine(std::index_sequence<jSize...>)
{
    return array<OperationPtr, sizeof...(jSize)>{
        &Mul<static_cast<ConstantType>(iSize), static_cast<ConstantType>(jSize)>...
    };
}

template<size... iSize, size... jSize>
constexpr array<array<OperationPtr, sizeof...(jSize)>, sizeof...(iSize)> CreateMulTable(std::index_sequence<iSize...>, std::index_sequence<jSize...> js)
{
    return array<array<OperationPtr, sizeof...(jSize)>, sizeof...(iSize)>{
        CreateMulLine<iSize>(js)...
    };
}


// Div type
template<size iSize, size... jSize>
constexpr array<OperationPtr, sizeof...(jSize)> CreateDivLine(std::index_sequence<jSize...>)
{
    return array<OperationPtr, sizeof...(jSize)>{
        &Div<static_cast<ConstantType>(iSize), static_cast<ConstantType>(jSize)>...
    };
}

template<size... iSize, size... jSize>
constexpr array<array<OperationPtr, sizeof...(jSize)>, sizeof...(iSize)> CreateDivTable(std::index_sequence<iSize...>, std::index_sequence<jSize...> js)
{
    return array<array<OperationPtr, sizeof...(jSize)>, sizeof...(iSize)>{
        CreateDivLine<iSize>(js)...
    };
}


// Pow type
template<size iSize, size... jSize>
constexpr array<OperationPtr, sizeof...(jSize)> CreatePowLine(std::index_sequence<jSize...>)
{
    return array<OperationPtr, sizeof...(jSize)>{
        &Pow<static_cast<ConstantType>(iSize), static_cast<ConstantType>(jSize)>...
    };
}

template<size... iSize, size... jSize>
constexpr array<array<OperationPtr, sizeof...(jSize)>, sizeof...(iSize)> CreatePowTable(std::index_sequence<iSize...>, std::index_sequence<jSize...> js)
{
    return array<array<OperationPtr, sizeof...(jSize)>, sizeof...(iSize)>{
        CreatePowLine<iSize>(js)...
    };
}


// And type
template<size iSize, size... jSize>
constexpr array<OperationPtr, sizeof...(jSize)> CreateAndLine(std::index_sequence<jSize...>)
{
    return array<OperationPtr, sizeof...(jSize)>{
        &And<static_cast<ConstantType>(iSize), static_cast<ConstantType>(jSize)>...
    };
}

template<size... iSize, size... jSize>
constexpr array<array<OperationPtr, sizeof...(jSize)>, sizeof...(iSize)> CreateAndTable(std::index_sequence<iSize...>, std::index_sequence<jSize...> js)
{
    return array<array<OperationPtr, sizeof...(jSize)>, sizeof...(iSize)>{
        CreateAndLine<iSize>(js)...
    };
}


// Or type
template<size iSize, size... jSize>
constexpr array<OperationPtr, sizeof...(jSize)> CreateOrLine(std::index_sequence<jSize...>)
{
    return array<OperationPtr, sizeof...(jSize)>{
        &Or<static_cast<ConstantType>(iSize), static_cast<ConstantType>(jSize)>...
    };
}

template<size... iSize, size... jSize>
constexpr array<array<OperationPtr, sizeof...(jSize)>, sizeof...(iSize)> CreateOrTable(std::index_sequence<iSize...>, std::index_sequence<jSize...> js)
{
    return array<array<OperationPtr, sizeof...(jSize)>, sizeof...(iSize)>{
        CreateOrLine<iSize>(js)...
    };
}


// Xor type
template<size iSize, size... jSize>
constexpr array<OperationPtr, sizeof...(jSize)> CreateXorLine(std::index_sequence<jSize...>)
{
    return array<OperationPtr, sizeof...(jSize)>{
        &Xor<static_cast<ConstantType>(iSize), static_cast<ConstantType>(jSize)>...
    };
}

template<size... iSize, size... jSize>
constexpr array<array<OperationPtr, sizeof...(jSize)>, sizeof...(iSize)> CreateXorTable(std::index_sequence<iSize...>, std::index_sequence<jSize...> js)
{
    return array<array<OperationPtr, sizeof...(jSize)>, sizeof...(iSize)>{
        CreateXorLine<iSize>(js)...
    };
}


// Not type
template<size... iSize>
constexpr array<OperationPtrSolo, sizeof...(iSize)> CreateNotTable(std::index_sequence<iSize...>)
{
    return array<OperationPtrSolo, sizeof...(iSize)>{
        &Not<static_cast<ConstantType>(iSize)>...
    };
}


// Print type
template<size... iSize>
constexpr array<NoReturnOperationPtrSolo, sizeof...(iSize)> CreatePrintTable(std::index_sequence<iSize...>)
{
    return array<NoReturnOperationPtrSolo, sizeof...(iSize)>{
        &Print<static_cast<ConstantType>(iSize)>...
    };
}