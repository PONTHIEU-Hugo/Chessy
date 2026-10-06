#pragma once
#include "Defines.h"
#include "ConstantContainer.h"
#include "ConstantTrait.h"


template <ConstantType LType, ConstantType RType>
ConstantContainer Add(const ConstantContainer& rLeft, const ConstantContainer& rRight);

template <ConstantType LType, ConstantType RType>
ConstantContainer Sub(const ConstantContainer& rLeft, const ConstantContainer& rRight);

template <ConstantType LType, ConstantType RType>
ConstantContainer Mul(const ConstantContainer& rLeft, const ConstantContainer& rRight);

template <ConstantType LType, ConstantType RType>
ConstantContainer Div(const ConstantContainer& rLeft, const ConstantContainer& rRight);

template <ConstantType LType, ConstantType RType>
ConstantContainer Pow(const ConstantContainer& rLeft, const ConstantContainer& rRight);


template <ConstantType LType, ConstantType RType>
ConstantContainer And(const ConstantContainer& rLeft, const ConstantContainer& rRight);

template <ConstantType LType, ConstantType RType>
ConstantContainer Or(const ConstantContainer& rLeft, const ConstantContainer& rRight);

template <ConstantType LType, ConstantType RType>
ConstantContainer Xor(const ConstantContainer& rLeft, const ConstantContainer& rRight);

template <ConstantType LType>
ConstantContainer Not(const ConstantContainer& rLeft);


template <ConstantType LType>
void Print(const ConstantContainer& rLeft);


#include "VM_Operation.inl"