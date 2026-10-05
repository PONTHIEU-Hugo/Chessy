#include "Analyser.h"
#include "ExpressionTrait.h"
#include "Scope.h"
#include "SymbolTrait.h"

Analyser::Analyser(ProgramExpression *program) : m_program(program)
{
}

void Analyser::Analyse()
{
    GlobalAnalyse();
}

void Analyser::GlobalAnalyse()
{
    m_scopes.push_back(new Scope(nullptr));
    AddBuiltin();
    CollectGlobals();
    AnalyseBodies();
    PopScope();
}

void Analyser::CollectGlobals()
{
    if (m_program == nullptr)
        return;

    for (size_t i = 0; i < m_program->content.size(); i++)
    {
        Expression* expr = m_program->content[i];

        switch (expr->type)
        {
        case ExpressionType::_FUNCTION_DECLARATION:
        {
            FunctionDeclarationExpression* funcExpr = ExpressionCast<ExpressionType::_FUNCTION_DECLARATION>(expr);
            FuncSymbol* funcSymbol = new FuncSymbol(); 
            if (m_scopes.back()->Declare(funcExpr->functionName->token.view, funcSymbol) == nullptr)
            {
                delete funcSymbol;
                m_errors.push_back(std::string(funcExpr->functionName->token.view) + " may have already been declared");
            }
            break;
        }
        case ExpressionType::_VARIABLE_DECLARATION:
        {
            VariableDeclarationExpression* varExpr = ExpressionCast<ExpressionType::_VARIABLE_DECLARATION>(expr);
            VarSymbol* varSymbol = new VarSymbol();
            varSymbol->m_slot = m_nextSlot++;
            if (m_scopes.back()->Declare(varExpr->name->token.view, varSymbol) == nullptr)
            {
                delete varSymbol;
                m_errors.push_back(std::string(varExpr->name->token.view) + " may have already been declared");
            }
            break;
        }
        default: break;
        }
    }
    
}

void Analyser::AnalyseBodies()
{
    if (m_program == nullptr)
        return;

    for (size_t i = 0; i < m_program->content.size(); i++)
    {
        Expression* expr = m_program->content[i];

        switch (expr->type)
        {
        case ExpressionType::_FUNCTION_DECLARATION:
            FunctionAnalyse(ExpressionCast<ExpressionType::_FUNCTION_DECLARATION>(expr)); break;
        case ExpressionType::_VARIABLE_DECLARATION:
            VarDeclarationAnalyse(ExpressionCast<ExpressionType::_VARIABLE_DECLARATION>(expr)); break;
        default: break;
        }
    }
}

void Analyser::AddBuiltin()
{
    //TODO
}

void Analyser::AnalyseExpression(Expression *expr)
{
    if (expr == nullptr)
        return;

    switch (expr->type)
    {
        case ExpressionType::_BLOCK:                return BlockAnalyse(ExpressionCast<ExpressionType::_BLOCK>(expr));
        case ExpressionType::_RETURN:               return ReturnAnalyse(ExpressionCast<ExpressionType::_RETURN>(expr));
        case ExpressionType::_DO_WHILE:             return DoWhileAnalyse(ExpressionCast<ExpressionType::_DO_WHILE>(expr));
        case ExpressionType::_IF:                   return IfAnalyse(ExpressionCast<ExpressionType::_IF>(expr));
        case ExpressionType::_FUNCTION_DECLARATION: return FunctionAnalyse(ExpressionCast<ExpressionType::_FUNCTION_DECLARATION>(expr));
        case ExpressionType::_PARAMETER:            return ParameterAnalyse(ExpressionCast<ExpressionType::_PARAMETER>(expr));
        case ExpressionType::_FUNCTION_CALL:        return FunctionCallAnalyse(ExpressionCast<ExpressionType::_FUNCTION_CALL>(expr));
        case ExpressionType::_VARIABLE_DECLARATION: return VarDeclarationAnalyse(ExpressionCast<ExpressionType::_VARIABLE_DECLARATION>(expr));
        case ExpressionType::_VARIABLE_ASSIGNMENT:  return VarAssignmentAnalyse(ExpressionCast<ExpressionType::_VARIABLE_ASSIGNMENT>(expr));
        case ExpressionType::_IDENTIFIER:           return IdentifierAnalyse(ExpressionCast<ExpressionType::_IDENTIFIER>(expr));
        case ExpressionType::_TYPE:                 return TypeAnalyse(ExpressionCast<ExpressionType::_TYPE>(expr));
        case ExpressionType::_LITERAL:              return LiteralAnalyse(ExpressionCast<ExpressionType::_LITERAL>(expr));
        case ExpressionType::_UNARY:                return UnaryAnalyse(ExpressionCast<ExpressionType::_UNARY>(expr));
        case ExpressionType::_BINARY:               return BinaryAnalyse(ExpressionCast<ExpressionType::_BINARY>(expr));
        case ExpressionType::_COMMENT:              return CommentAnalyse(ExpressionCast<ExpressionType::_COMMENT>(expr));

        default:
            return;
    }      
}

void Analyser::BlockAnalyse(BlockExpression *block)
{
    AddScope();

    for (size_t i = 0; i < block->content.size(); i++)
    {
        Expression* expr = block->content[i];
        AnalyseExpression(expr);
    }

    PopScope();
}

void Analyser::ReturnAnalyse(ReturnExpression *ret)
{
    if (m_currentFunc == nullptr)
    {
        m_errors.push_back("return out of function");
        return;
    }

    // TODO
    // ret->value // Exprssion how to get type
    // compare with m_currentFunc->returnType // TypeExpression
    
    if (ret->value == nullptr && m_currentFunc->returnType == nullptr)
        return;
}

void Analyser::DoWhileAnalyse(DoWhileExpression *doWhile)
{
    BlockAnalyse(ExpressionCast<ExpressionType::_BLOCK>(doWhile->block));
    AnalyseExpression(doWhile->condition);
}

void Analyser::IfAnalyse(IfExpression *ifStmt)
{
    AnalyseExpression(ifStmt->condition);
    BlockAnalyse(ExpressionCast<ExpressionType::_BLOCK>(ifStmt->block));
}

void Analyser::FunctionAnalyse(FunctionDeclarationExpression *func)
{
    FuncSymbol* fnSmb;
    if (m_scopes.size() == 1)
    {
        fnSmb = SymbolCast<SymbolType::_FUNC>(m_scopes.back()->GetSymbol(func->functionName->token.view));
        if (fnSmb == nullptr)
        {
            m_errors.push_back(std::string(func->functionName->token.view) + " is not a function");
            return;
        }
    }
    else
    {
        fnSmb = new FuncSymbol(); 

        if (m_scopes.back()->Declare(func->functionName->token.view, fnSmb) == nullptr)
        {
            delete fnSmb;
            m_errors.push_back(std::string(func->functionName->token.view) + " may have already been declared");
            return;
        }
    }

    AddScope(func);
    m_nextSlot++; 
    
    for (size_t i = 0; i < func->parameters.size(); i++)
    {
        ParameterExpression* param = func->parameters[i];
        ParameterAnalyse(param);
    }

    for (size_t i = 0; i < func->content->content.size(); i++)
    {
        Expression* expr = func->content->content[i];
        AnalyseExpression(expr);
    }
    
    fnSmb->slot_count = m_nextSlot;

    PopScope(true);
}

void Analyser::ParameterAnalyse(ParameterExpression *param)
{
    VarSymbol* sym = new VarSymbol();
    sym->m_slot = m_nextSlot++;
    if(m_scopes.back()->Declare(param->name->token.view, sym) == nullptr)
    {
        delete sym;
        m_errors.push_back(std::string(param->name->token.view) + " may have already been declared");
        return;
    }
}

void Analyser::FunctionCallAnalyse(FunctionCallExpression *call)
{
    Symbol* sym = m_scopes.back()->GetSymbol(call->name->token.view);
    if (sym == nullptr)
    {
        m_errors.push_back("function " + std::string(call->name->token.view) + " could not be found");
        return;
    }

    FuncSymbol* fn = SymbolCast<SymbolType::_FUNC>(sym);
    if (fn == nullptr) {
        m_errors.push_back(std::string(call->name->token.view) + " is not a function");
        return;
    }

    for (size_t i = 0; i < call->arguments.size(); i++)
    {
        Expression* expr = call->arguments[i];
        AnalyseExpression(expr);
    }

    if (call->arguments.size() != fn->ParamNumber)
    {
        m_errors.push_back("function " + std::string(call->name->token.view) + " expect" + std::to_string(fn->ParamNumber) + ", " + std::to_string(call->arguments.size()) + " were given");
        return;
    }

    // TODO :: check types
}

void Analyser::VarDeclarationAnalyse(VariableDeclarationExpression *varDec)
{
    VarSymbol* varSmb;
    if (m_scopes.size() == 1)
    {
        Symbol* smb = m_scopes.back()->GetSymbol(varDec->name->token.view);
        varSmb = SymbolCast<SymbolType::_VAR>(smb);
        if (varSmb == nullptr)
        {
            m_errors.push_back(std::string(varDec->name->token.view) + " is not a variable");
            return;
        }
    }
    else
    {
        varSmb = new VarSymbol();
        varSmb->m_slot = m_nextSlot++;
        if (m_scopes.back()->Declare(varDec->name->token.view,varSmb) == nullptr)
        {
            delete varSmb;
            m_errors.push_back(std::string(varDec->name->token.view) + " may have already been declared");
            return;
        }
    }

    // TODO :: check type
    if (varDec->value != nullptr)
    {
        AnalyseExpression(varDec->value);
    }
}

void Analyser::VarAssignmentAnalyse(VariableAssignmentExpression *varAssign)
{
    Symbol* smb = m_scopes.back()->GetSymbol(varAssign->name->token.view);
    if (smb == nullptr)
    {
        m_errors.push_back("variable " + std::string(varAssign->name->token.view) + " has not been declared");
        return;
    }

    VarSymbol* varSmb = SymbolCast<SymbolType::_VAR>(smb);
    if (varSmb == nullptr)
    {
        m_errors.push_back(std::string(varAssign->name->token.view) + " is not a viariable");
        return;
    }
    // check assignment type :: TODO

    AnalyseExpression(varAssign->value);
}

void Analyser::IdentifierAnalyse(IdentifierExpression *id)
{
    Symbol* sym = m_scopes.back()->GetSymbol(id->token.view);
    if (sym == nullptr)
    {
        m_errors.push_back("undefined Identifier " + std::string(id->token.view));
        return;
    }

    // id->m_symbol = sym; //should add this on ast ?
}

void Analyser::TypeAnalyse(TypeExpression *type)
{
}

void Analyser::LiteralAnalyse(LiteralExpression *literal)
{
}

void Analyser::UnaryAnalyse(UnaryExpression *unary)
{
    AnalyseExpression(unary->left);
}

void Analyser::BinaryAnalyse(BinaryExpression *binary)
{
    AnalyseExpression(binary->left);
    AnalyseExpression(binary->right);
}

void Analyser::CommentAnalyse(CommentExpression *comment)
{
}

void Analyser::AddScope(FunctionDeclarationExpression* func = nullptr)
{
    Scope* newScope = new Scope(m_scopes.back());
    m_scopes.push_back(newScope);



    if (func != nullptr)
    {
        m_previousNextSlot.push_back(m_nextSlot);
        m_nextSlot = 0;

        m_previousFunc.push_back(m_currentFunc);
        m_currentFunc = func;
    }
}

void Analyser::PopScope(bool popFunc)
{
    m_scopes.pop_back();


    if (popFunc)
    {
        m_nextSlot = m_previousNextSlot.back();
        m_previousNextSlot.pop_back();

        m_currentFunc = m_previousFunc.back();
        m_previousFunc.pop_back();
    }
}
