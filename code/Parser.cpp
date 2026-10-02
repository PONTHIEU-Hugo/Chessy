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

BlockExpression* Parser::ParseBlock()
{
    Consume(TokenType::_L_BRACE);

    BlockExpression* block = new BlockExpression();

    while (Peek().type != TokenType::_R_BRACE)
    {
        block->content.push_back(ParseStatement());
    }

    Consume(TokenType::_R_BRACE);
    return block;
}

FunctionDeclarationExpression* Parser::ParseFunctionDeclaration()
{
    FunctionDeclarationExpression* func = new FunctionDeclarationExpression();
    Consume(TokenType::_FUNC);

    func->functionName = new IdentifierExpression(Consume(TokenType::_SYMBOL));

    Consume(TokenType::_L_PARENTHESE);

    while (Peek().type != TokenType::_R_PARENTHESE)
    {
        func->parameters.push_back(ParseParameter());
        Consume(TokenType::_COMMA);
    }

    Consume(TokenType::_R_PARENTHESE);

    if (Peek().type == TokenType::_COLON)
    {
        Consume(TokenType::_COLON);
        func->returnType = ParseType();
    }

    func->content = ParseBlock();

    return func;
}

FunctionCallExpression* Parser::ParseFunctionCall()
{
    FunctionCallExpression* call = new FunctionCallExpression();

    call->name = new IdentifierExpression(Consume(TokenType::_SYMBOL));

    Consume(TokenType::_L_PARENTHESE);

    while (Peek().type != TokenType::_R_PARENTHESE)
    {
        call->arguments.push_back(ParseStatement());
        Consume(TokenType::_COMMA);
    }

    Consume(TokenType::_R_PARENTHESE);

    return call;
}

ParameterExpression* Parser::ParseParameter() 
{
    ParameterExpression* param = new ParameterExpression();
    param->paramType = ParseType();
    param->name = new IdentifierExpression(Consume(TokenType::_SYMBOL));
    return param;
}

VariableDeclarationExpression* Parser::ParseVariableDeclaration()
{
    VariableDeclarationExpression* variableDec = new VariableDeclarationExpression();
    variableDec->varType = ParseType();
    variableDec->name = new IdentifierExpression(Consume(TokenType::_SYMBOL));

    if (Peek().type == TokenType::_EQUAL)
    {
        Consume(TokenType::_EQUAL);
        variableDec->value = ParseStatement();
    }

    return variableDec;
}

VariableAssignmentExpression* Parser::ParseVariableAssignement() 
{
    VariableAssignmentExpression* varAssign = new VariableAssignmentExpression();

    varAssign->name = new IdentifierExpression(Consume(TokenType::_SYMBOL));
    Consume(TokenType::_EQUAL);
    varAssign->value = ParseStatement();

    return varAssign;
}

TypeExpression* Parser::ParseType()
{
    static un_set<TokenType> typeTokens = {
        TokenType::_BOOL,
        TokenType::_I8, TokenType::_I16, TokenType::_I32, TokenType::_I64,
        TokenType::_U8, TokenType::_U16, TokenType::_U32, TokenType::_U64,
        TokenType::_BITBOARD, TokenType::_PIECE,
        TokenType::_POSITION, TokenType::_MOVE,
    };

    Token& type = Peek();
    if (typeTokens.count(type.type) == 0)
        throw std::runtime_error("unexpected token type");

    TypeExpression* typeExpr = new TypeExpression(type);

    return typeExpr;
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
