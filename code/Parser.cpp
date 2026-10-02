#include "Parser.h"

un_set<TokenType> Parser::s_typeTokens = {
    TokenType::_BOOL,
    TokenType::_I8, TokenType::_I16, TokenType::_I32, TokenType::_I64,
    TokenType::_U8, TokenType::_U16, TokenType::_U32, TokenType::_U64,
    TokenType::_BITBOARD, TokenType::_PIECE,
    TokenType::_POSITION, TokenType::_MOVE,
};

Parser::Parser()
{
}

Parser::~Parser()
{
}

void Parser::Parse(std::vector<Token>& tokens)
{
	m_tokens = tokens;
    m_program = ParseProgram();
}

ProgramExpression* Parser::GetProgram()
{
    return m_program;
}

Token& Parser::Consume(TokenType type)
{
    if (m_tokenIndex >= static_cast<int>(m_tokens.size()))
        throw std::runtime_error("token out of range");
    Token& t = m_tokens[m_tokenIndex];
    if (t.type != type)
        throw std::runtime_error("unexpected token type");
    m_tokenIndex++;
    return t;
}

Token& Parser::Peek(int indexOffset)
{
    if (m_tokenIndex + indexOffset >= static_cast<int>(m_tokens.size()))
        throw std::runtime_error("token out of range");
    Token& t = m_tokens[m_tokenIndex + indexOffset];
    return t;
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
    {
        Expression* expr = ParseVariableDeclaration();
        Consume(TokenType::_SEMI_COLON);
        return expr;
    }
    }
}

BlockExpression* Parser::ParseBlock()
{
    Consume(TokenType::_L_BRACE);

    BlockExpression* block = new BlockExpression();

    while (Peek().type != TokenType::_R_BRACE)
    {
        Expression* stmt = ParseExpression();
        Consume(TokenType::_SEMI_COLON);
        block->content.push_back(stmt);
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

    if (Peek().type != TokenType::_R_PARENTHESE)
    {
        func->parameters.push_back(ParseParameter());
        while (Peek().type == TokenType::_COMMA)
        {
            Consume(TokenType::_COMMA);
            func->parameters.push_back(ParseParameter());
        }
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

    if (Peek().type != TokenType::_R_PARENTHESE)
    {
        call->arguments.push_back(ParseExpression());
        while (Peek().type == TokenType::_COMMA)
        {
            Consume(TokenType::_COMMA);
            call->arguments.push_back(ParseExpression());
        }
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
        variableDec->value = ParseExpression();
    }

    return variableDec;
}

TypeExpression* Parser::ParseType()
{
    Token& type = Peek();
    if (s_typeTokens.count(type.type) == 0)
        throw std::runtime_error("unexpected token type");

    TypeExpression* typeExpr = new TypeExpression(type);
    Consume(type.type);

    return typeExpr;
}

ReturnStatementExpression* Parser::ParseReturnStatement()
{
    ReturnStatementExpression* returnStatement = new ReturnStatementExpression();
    Consume(TokenType::_RETURN);
    if (Peek().type == TokenType::_SEMI_COLON)
        return returnStatement;

    returnStatement->value = ParseExpression();
    return returnStatement;
}

Expression* Parser::ParseExpression(int minLeftBindingPower)
{
    
    Expression* left = ParsePrefix();
    while (m_tokenIndex < static_cast<int>(m_tokens.size()))
    {
        Token token = m_tokens[m_tokenIndex];
        BindingPower bindingPower = GetBindingPower(token);
        if (bindingPower.left < minLeftBindingPower || bindingPower.left == 0)
            break;
        m_tokenIndex++;
        Expression* right = ParseExpression(bindingPower.right);
        left = new BinaryExpression(token, left, right);
    }
    return left;
}

Expression* Parser::ParsePrefix()
{
    Token& token = Peek();

    if (token.globalType == GlobalTokenType::_LITTERAL)
    {
        Consume(token.type);
        return new LiteralExpression(token);
    }

    if (token.type == TokenType::_SYMBOL)
    {
        if (Peek(1).type == TokenType::_L_PARENTHESE)
            return ParseFunctionCall();

        Consume(TokenType::_SYMBOL);
        return new IdentifierExpression(token);
    }

    if (token.type == TokenType::_L_PARENTHESE)
    {
        Consume(TokenType::_L_PARENTHESE);
        Expression* inner = ParseExpression();
        Consume(TokenType::_R_PARENTHESE);
        return inner;
    }

    if (s_typeTokens.count(token.type) && Peek(1).type == TokenType::_SYMBOL)
    {
        return ParseVariableDeclaration();
    }

    if (token.type == TokenType::_RETURN)
    {
        return ParseReturnStatement();
    }

    if (token.globalType == GlobalTokenType::_OPERAND)
    {
        Consume(token.type);
        Expression* operand = ParseExpression(20);
        return new UnaryExpression(token, operand);
    }

    throw std::runtime_error("expected expression");
}

BindingPower Parser::GetBindingPower(Token& token)
{
    switch (token.globalType)
    {
    case GlobalTokenType::_OPERAND:
        switch (token.type)
        {
        case TokenType::_EQUAL:            return { 3, 3 };    
        case TokenType::_OR_OP:            return { 4, 5 };    
        case TokenType::_AND_OP:           return { 5, 6 };    
        case TokenType::_OR_BINARY:        return { 6, 7 };    
        case TokenType::_XOR_BINARY:       return { 7, 8 };    
        case TokenType::_AND_BINARY:       return { 8, 9 };    
        case TokenType::_EQUAL_OP:
        case TokenType::_NOT_EQUAL_OP:     return { 9, 10 };   
        case TokenType::_GREATER_THAN:
        case TokenType::_GREATER_EQ_THAN:
        case TokenType::_LOWER_THAN:
        case TokenType::_LOWER_EQ_THAN:    return { 10, 11 };  
        case TokenType::_L_SHIFT:
        case TokenType::_R_SHIFT:          return { 11, 12 };  
        case TokenType::_ADD:
        case TokenType::_SUB:              return { 12, 13 };  
        case TokenType::_MUL:
        case TokenType::_DIV:
        case TokenType::_MOD:              return { 13, 14 };  
        case TokenType::_POW:              return { 14, 14 };  
        default:                           return { 0, 0 };
        }

    case GlobalTokenType::_DELIMITOR:
        switch (token.type)
        {
        case TokenType::_L_PARENTHESE: return { 18, 0 };
        default:                       return { 0, 0 };
        }

    default:
        return { 0, 0 };
    }
}
