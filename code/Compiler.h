#pragma once
#include "Expression.h"
#include "Chunk.h"

class Compiler
{
public:
Compiler();
void Compile(ProgramExpression* program); 
Chunk& GetChuck();

private:
    void CompileProgram();
    void CompileDeclaration(Expression* expr);

    void CompileExpression(Expression* expr);

    void CompileBlock(BlockExpression* block);
    void CompileReturn(ReturnExpression* ret);
    void CompileDoWhile(DoWhileExpression* doWhile);
    void CompileIf(IfExpression* ifStmt);

    void CompileFunctionDeclaration(FunctionDeclarationExpression* functionDeclaration);
    void CompileFunctionCall(FunctionCallExpression* functionCall);
    void CompileParameter(ParameterExpression* parameter);

    void CompileVariableDeclaration(VariableDeclarationExpression* variableDeclaration);
    void CompileVariableAssignment(VariableAssignmentExpression* variableAssignment);

    void CompileIdentifier(IdentifierExpression* identifier);
    void CompileType(TypeExpression* type);
    void CompileLiteral(LiteralExpression* literal);

    void CompileBinary(BinaryExpression* binary);
    void CompileUnary(UnaryExpression* unary);
private:
    ProgramExpression* m_program = nullptr;
    un_map<str, int> m_consts;
    Chunk m_chunk;
};