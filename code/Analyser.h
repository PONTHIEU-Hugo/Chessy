#pragma once
#include "Defines.h"
#include "Expression.h"

class Scope;

class Analyser
{
public:
    Analyser(ProgramExpression* program);
    void Analyse();

private:
    void GlobalAnalyse();
    void CollectGlobals();
    void AnalyseBodies();
    void AddBuiltin();

    void AnalyseExpression(Expression* expr);

    void BlockAnalyse(BlockExpression* block);
    void ReturnAnalyse(ReturnExpression* ret);
    void DoWhileAnalyse(DoWhileExpression* doWhile);
    void IfAnalyse(IfExpression* ifStmt);

    void FunctionAnalyse(FunctionDeclarationExpression* func);
    void ParameterAnalyse(ParameterExpression* param);
    void FunctionCallAnalyse(FunctionCallExpression* call);

    void VarDeclarationAnalyse(VariableDeclarationExpression* varDec);
    void VarAssignmentAnalyse(VariableAssignmentExpression* varAssign);

    void IdentifierAnalyse(IdentifierExpression* id);
    void TypeAnalyse(TypeExpression* type);
    void LiteralAnalyse(LiteralExpression* literal);

    void UnaryAnalyse(UnaryExpression* unary);
    void BinaryAnalyse(BinaryExpression* binary);

    void CommentAnalyse(CommentExpression* comment);

    void AddScope(FunctionDeclarationExpression* func = nullptr);
    void PopScope(bool popFunc = false);
private:
    std::vector<Scope*> m_scopes;
    std::vector<str> m_errors;
    ProgramExpression* m_program = nullptr;
    FunctionDeclarationExpression* m_currentFunc = nullptr;
    int m_nextSlot = 0;
    std::vector<int> m_previousNextSlot;
    std::vector<FunctionDeclarationExpression*> m_previousFunc;
};