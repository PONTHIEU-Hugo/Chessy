#include "Analyser.h"
#include "Expression.h"
#include "ExpressionTrait.h"
#include "Scope.h"

Analyser::Analyser(ProgramExpression *program) : m_program(program)
{
}

void Analyser::Analyse()
{
    GlobalAnalyse();
}

void Analyser::GlobalAnalyse()
{
    AddBuiltin();

}

void Analyser::AddBuiltin()
{

}

void Analyser::BlockAnalyse(BlockExpression *block)
{
}

void Analyser::FunctionAnalyse(FunctionDeclarationExpression *func)
{
}

void Analyser::VarDeclarationAnalyse(VariableDeclarationExpression *varDec)
{
}

void Analyser::VarAssignmentAnalyse(VariableAssignmentExpression *varAssign)
{
}
