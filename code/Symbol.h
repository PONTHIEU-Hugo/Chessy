#pragma once
#include "Defines.h"
#include "SymbolType.h"
#include "Token.h"

class Scope;

struct Symbol
{
public:
    virtual ~Symbol() = default;
    SymbolType type;
    str_view m_name;
    Scope* m_scope = nullptr;
};

struct VarSymbol : public Symbol
{
public:
    int m_slot = -1; // ? maybe 
    TokenType varType;
    VarSymbol(TokenType vType) : varType(vType)
    {
        type = SymbolType::_VAR;
    }
};

struct FuncSymbol : public Symbol
{
public:
    int slot_count;
    vector<TokenType> paramsType;
    TokenType returnType;
    FuncSymbol()
    {
        type = SymbolType::_FUNC;
    }
};

struct ConstSymbol : public Symbol
{
public:
    ConstSymbol()
    {
        type = SymbolType::_CONST;
    }
};