#pragma once
#include "Defines.h"
#include "SymbolType.h"

class Scope;

class Symbol
{
public:
    virtual ~Symbol() = default;
    SymbolType type;
    str_view m_name;
    Scope* m_scope = nullptr;
};

class VarSymbol : public Symbol
{
public:
    int m_slot = -1; // ? maybe 
    VarSymbol()
    {
        type = SymbolType::_VAR;
    }
};

class FuncSymbol : public Symbol
{
public:
    FuncSymbol()
    {
        type = SymbolType::_FUNC;
    }
};

class ConstSymbol : public Symbol
{
public:
    ConstSymbol()
    {
        type = SymbolType::_CONST;
    }
};