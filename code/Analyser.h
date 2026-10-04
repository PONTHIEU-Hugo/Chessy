#pragma once
#include "Defines.h"

struct ProgramExpression;
struct BlockExpression;
struct FunctionDeclarationExpression;
struct VariableDeclarationExpression;
struct VariableAssignmentExpression;
class Scope;

class Analyser
{
public:
    Analyser(ProgramExpression* program);
    void Analyse();

private:
    void GlobalAnalyse();
    void AddBuiltin();

    void BlockAnalyse(BlockExpression* block);
    void FunctionAnalyse(FunctionDeclarationExpression* func);
    void VarDeclarationAnalyse(VariableDeclarationExpression* varDec);
    void VarAssignmentAnalyse(VariableAssignmentExpression* varAssign);
private:
    std::stack<Scope*> m_scopes;
    ProgramExpression* m_program = nullptr;
};