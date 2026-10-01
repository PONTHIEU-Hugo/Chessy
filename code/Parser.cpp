#include "Parser.h"

Parser::Parser()
{
}

Parser::~Parser()
{
}

void Parser::Parse(std::vector<Token> tokens)
{
	m_tokens = tokens;
    m_program = ParseProgram();
}

Token& Parser::Consume(TokenType type)
{
    if (m_tokenIndex >= static_cast<int>(m_tokens.size()))
        throw std::runtime_error("token out of range");
    Token& t = m_tokens[m_tokenIndex];
    if (t.type != type)
        throw std::runtime_error("unexpected token type");
    m_tokenIndex++;
}

Token& Parser::Peek()
{
    if (m_tokenIndex >= static_cast<int>(m_tokens.size()))
        throw std::runtime_error("token out of range");
    Token& t = m_tokens[m_tokenIndex];
}

ProgramExpression* Parser::ParseProgram()
{
    ProgramExpression* programExp = new ProgramExpression();
    while (m_tokenIndex < m_tokens.size())
    {
        Expression* exp = ParseDeclaration();
        programExp->content.push_back(exp);
    }
    return programExp;
}

Expression* Parser::ParseDeclaration()
{
    Token& token = Peek();
    switch (token.type)
    {
    case TokenType::_FUNC: return ParseFunctionDeclaration();
    default:
        return ParseVariableDeclaration(); 
    }
}

BlockExpression* Parser::ParseBlock() //TODO
{
    return nullptr;
}

FunctionDeclarationExpression* Parser::ParseFunctionDeclaration() //TODO
{
    return nullptr;
}

FunctionCallExpression* Parser::ParseFunctionCall() //TODO
{
    return nullptr;
}

ParameterExpression* Parser::ParseParameters() //TODO
{
    return nullptr;
}

VariableDeclarationExpression* Parser::ParseVariableDeclaration() //TODO
{
    return nullptr;
}

VariableAssignmentExpression* Parser::ParseVariableAssignement() //TODO
{
    return nullptr;
}

ReturnStatementExpression* Parser::ParseReturnStatement() //TODO
{
    return nullptr;
}

StatementExpression* Parser::ParseStatement() //TODO
{
    return nullptr;
}

Expression* Parser::ParseExpression(int minLeftBindingPower)
{
    /*
    Expression* left = ParsePrefix();
    while (m_tokenIndex < static_cast<int>(m_tokens.size()))
    {
        Token token = m_tokens[m_tokenIndex];
        BindingPower bindingPower = GetBindingPower(token);
        if (bindingPower.left < minLeftBindingPower || bindingPower.left == 0)
            break;
        m_tokenIndex++;
        Expression* right = MakeExpression(bindingPower.right);
        left = MakeBinaryExpression(token, left, right);
    }
    return left;
    */
    return nullptr;
}

BindingPower Parser::GetBindingPower(Token& token)
{
    switch (token.globalType)
    {
    case GlobalTokenType::_OPERAND:
        switch (token.type)
        {
        case TokenType::_EQUAL:        return { 16, 16 };
        case TokenType::_OR_OP:        return { 15, 15 };
        case TokenType::_AND_OP:       return { 14, 14 };
        case TokenType::_OR_BINARY:    return { 13, 13 };
        case TokenType::_XOR_BINARY:   return { 12, 12 };
        case TokenType::_AND_BINARY:   return { 11, 11 };
        case TokenType::_EQUAL_OP:
        case TokenType::_NOT_EQUAL_OP:    return { 10, 10 };
        case TokenType::_GREATER_THAN:
        case TokenType::_GREATER_EQ_THAN:
        case TokenType::_LOWER_THAN:
        case TokenType::_LOWER_EQ_THAN:   return { 9, 9 };
        case TokenType::_L_SHIFT:
        case TokenType::_R_SHIFT:      return { 7, 7 };
        case TokenType::_ADD:
        case TokenType::_SUB:          return { 6, 6 };
        case TokenType::_MUL:
        case TokenType::_DIV:
        case TokenType::_MOD:          return { 5, 5 };
        case TokenType::_POW:          return { 3, 3 };
        default:                       return { 0, 0 };
        }

    case GlobalTokenType::_DELIMITOR:
        switch (token.type)
        {
        case TokenType::_L_PARENTHESE: return { 17, 0 };
        }

    default:
        return { 0, 0 };
    }
}
