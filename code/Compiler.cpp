#include "Compiler.h"
#include "ExpressionTrait.h"

Compiler::Compiler()
{
}

void Compiler::Compile(ProgramExpression *program)
{
    m_program = program;
    m_chunk = Chunk();
    CompileProgram();
}

void Compiler::CompileProgram()
{
    for (size_t i = 0; i < m_program->content.size(); i++)
    {
        Expression* expr;
        CompileDeclaration(expr);
    }
    
}

void Compiler::CompileDeclaration(Expression *expr)
{
    switch (expr->type)
    {
    case ExpressionType::_FUNCTION_DECLARATION: CompileFunctionDeclaration(ExpressionCast<ExpressionType::_FUNCTION_DECLARATION>(expr)); break;
    case ExpressionType::_VARIABLE_DECLARATION: CompileVariableDeclaration(ExpressionCast<ExpressionType::_VARIABLE_DECLARATION>(expr)); break;
    default:
        break;
    }
}

void Compiler::CompileExpression(Expression *expr)
{
        if (expr == nullptr)
        return;

    switch (expr->type)
    {
        case ExpressionType::_BLOCK:                CompileBlock(ExpressionCast<ExpressionType::_BLOCK>(expr)); break;
        case ExpressionType::_RETURN:               CompileReturn(ExpressionCast<ExpressionType::_RETURN>(expr)); break;
        case ExpressionType::_DO_WHILE:             CompileDoWhile(ExpressionCast<ExpressionType::_DO_WHILE>(expr)); break;
        case ExpressionType::_IF:                   CompileIf(ExpressionCast<ExpressionType::_IF>(expr)); break;
        case ExpressionType::_FUNCTION_DECLARATION: CompileFunctionDeclaration(ExpressionCast<ExpressionType::_FUNCTION_DECLARATION>(expr)); break;
        case ExpressionType::_PARAMETER:            CompileParameter(ExpressionCast<ExpressionType::_PARAMETER>(expr)); break;
        case ExpressionType::_FUNCTION_CALL:        CompileFunctionCall(ExpressionCast<ExpressionType::_FUNCTION_CALL>(expr)); break;
        case ExpressionType::_VARIABLE_DECLARATION: CompileVariableDeclaration(ExpressionCast<ExpressionType::_VARIABLE_DECLARATION>(expr)); break;
        case ExpressionType::_VARIABLE_ASSIGNMENT:  CompileVariableAssignment(ExpressionCast<ExpressionType::_VARIABLE_ASSIGNMENT>(expr)); break;
        case ExpressionType::_IDENTIFIER:           CompileIdentifier(ExpressionCast<ExpressionType::_IDENTIFIER>(expr)); break;
        case ExpressionType::_TYPE:                 CompileType(ExpressionCast<ExpressionType::_TYPE>(expr)); break;
        case ExpressionType::_LITERAL:              CompileLiteral(ExpressionCast<ExpressionType::_LITERAL>(expr)); break;
        case ExpressionType::_UNARY:                CompileUnary(ExpressionCast<ExpressionType::_UNARY>(expr)); break;
        case ExpressionType::_BINARY:               CompileBinary(ExpressionCast<ExpressionType::_BINARY>(expr)); break;

        default:
            return;
    }      
    return;
}

void Compiler::CompileBlock(BlockExpression *block)
{
    for (size_t i = 0; i < block->content.size(); i++)
    {
        Expression* expr = block->content[i];
        CompileExpression(expr);
    }
    
}

void Compiler::CompileReturn(ReturnExpression *ret)
{
    Instruction instruction = {OpCode::_LOADC, 1,1,1};
    m_chunk.push_instruction(instruction);
}

void Compiler::CompileDoWhile(DoWhileExpression *doWhile)
{
}

void Compiler::CompileIf(IfExpression *ifStmt)
{
}

void Compiler::CompileFunctionDeclaration(FunctionDeclarationExpression *functionDeclaration)
{
}

void Compiler::CompileFunctionCall(FunctionCallExpression *functionCall)
{
}

void Compiler::CompileParameter(ParameterExpression *parameter)
{
}

void Compiler::CompileVariableDeclaration(VariableDeclarationExpression *variableDeclaration)
{
}

void Compiler::CompileVariableAssignment(VariableAssignmentExpression *variableAssignment)
{
}

void Compiler::CompileIdentifier(IdentifierExpression *identifier)
{
}

void Compiler::CompileType(TypeExpression *type)
{
}

void Compiler::CompileAnalyse(LiteralExpression *literal)
{
}

void Compiler::CompileBinary(BinaryExpression *binary)
{
}

void Compiler::CompileUnary(UnaryExpression *unary)
{
}
