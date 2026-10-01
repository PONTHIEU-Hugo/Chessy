#include "Lexer.h"

Lexer::Lexer()
{
    // Identifiers
    m_Identifier.emplace("bool", TokenType::_BOOL);

    m_Identifier.emplace("i8", TokenType::_I8);
    m_Identifier.emplace("i16", TokenType::_I16);
    m_Identifier.emplace("i32", TokenType::_I32);
    m_Identifier.emplace("i64", TokenType::_I64);

    m_Identifier.emplace("u8", TokenType::_U8);
    m_Identifier.emplace("u16", TokenType::_U16);
    m_Identifier.emplace("u32", TokenType::_U32);
    m_Identifier.emplace("u64", TokenType::_U64);

    m_Identifier.emplace("bitboard", TokenType::_BITBOARD);
    m_Identifier.emplace("piece", TokenType::_PIECE);
    m_Identifier.emplace("position", TokenType::_POSITION);
    m_Identifier.emplace("move", TokenType::_MOVE);

    // Keywords
    m_Keyword.emplace("do", TokenType::_DO);
    m_Keyword.emplace("while", TokenType::_WHILE);
    m_Keyword.emplace("if", TokenType::_IF);
    m_Keyword.emplace("func", TokenType::_FUNC);
    m_Keyword.emplace("return", TokenType::_RETURN);
    m_Keyword.emplace("return", TokenType::_TRUE);
    m_Keyword.emplace("return", TokenType::_FALSE);
}

bool Lexer::ReadFile(str _path)
{
    std::ifstream file(_path, std::ios::binary);
    if(!file)
        return false;
    std::ostringstream string;
    string << file.rdbuf();
    m_File = string.str();
    return true;
}

void Lexer::Tokenize()
{
    m_Tokens.clear();
    m_Line = 1;
    m_Column = 1;
    m_Current = 0;
    m_Start = 0;

    while (IsAtEnd() == false)
    {
        m_Start = m_Current;
        ScanToken();
    }
}

void Lexer::ScanToken()
{    
    char& currentChar = NextChar();
    bool isMatch = false;
    switch (currentChar)
    {
    case ' ':
        break;
    case '\r':
        m_Column = 1;
        break;
    case '\t':
        m_Column += 4;
        break;
    case '\n':
        m_Line++;
        break;

    case ';':
        AddToken(GlobalTokenType::_DELIMITOR, TokenType::_SEMI_COLON);
        break;
    case '{':
        AddToken(GlobalTokenType::_DELIMITOR, TokenType::_L_BRACE);
        break;
    case '}':
        AddToken(GlobalTokenType::_DELIMITOR, TokenType::_R_BRACE);
        break;
    case '(':
        AddToken(GlobalTokenType::_DELIMITOR, TokenType::_L_PARENTHESE);
        break;
    case ')':
        AddToken(GlobalTokenType::_DELIMITOR, TokenType::_R_PARENTHESE);
        break;
    case ':':
        AddToken(GlobalTokenType::_DELIMITOR, TokenType::_COLON);
        break;
    case '"':
        String();
        break;
    case ',':
        AddToken(GlobalTokenType::_DELIMITOR, TokenType::_COMMA);
        break;
    case '+':
        AddToken(GlobalTokenType::_OPERAND, TokenType::_ADD);
        break;
    case '-':
        AddToken(GlobalTokenType::_OPERAND, TokenType::_SUB);
        break;
    case '%':
        AddToken(GlobalTokenType::_OPERAND, TokenType::_MOD);
        break;
    case '*':
        AddToken(GlobalTokenType::_OPERAND, (Match('*') == false ? TokenType::_MUL : TokenType::_POW));
        break;
    case '=':
        AddToken(GlobalTokenType::_OPERAND, (Match('=') == false ? TokenType::_EQUAL : TokenType::_EQUAL_OP));
        break;
    case '/':
        if(Match('/') == false)
        {
            while(Peek() != '\n' && !IsAtEnd())
                NextChar();
        }
        else
            AddToken(GlobalTokenType::_OPERAND, TokenType::_DIV);
        break;

    case '^':
        AddToken(GlobalTokenType::_OPERAND, TokenType::_XOR_BINARY);
        break;
    case '|':
        AddToken(GlobalTokenType::_OPERAND, (Match('|') == false ? TokenType::_OR_BINARY : TokenType::_OR_OP));
        break;
    case '&':
        AddToken(GlobalTokenType::_OPERAND, (Match('&') == false ? TokenType::_AND_BINARY : TokenType::_AND_OP));
        break;
    case '!':
        AddToken(GlobalTokenType::_OPERAND, (Match('=') == false ? TokenType::_NOT_OP : TokenType::_NOT_EQUAL_OP));
        break;
    case '<':
        isMatch = Match('=');
        if(isMatch == false)
            AddToken(GlobalTokenType::_OPERAND, (Match('<') == false ? TokenType::_GREATER_THAN : TokenType::_L_SHIFT));
        else
            AddToken(GlobalTokenType::_OPERAND, TokenType::_GREATER_EQ_THAN);
        break;
    case '>':
        isMatch = Match('=');
        if(isMatch == false)
            AddToken(GlobalTokenType::_OPERAND, (Match('>') == false ? TokenType::_LOWER_THAN : TokenType::_R_SHIFT));
        else
            AddToken(GlobalTokenType::_OPERAND, TokenType::_LOWER_EQ_THAN);
        break;

    default:
        //std::cout << currentChar << std::endl;
        if(std::isdigit(currentChar))
            Number();
        else if(std::isalpha(currentChar))
            Symbol();
        else
            throw std::runtime_error("Lexical error");
        break;
    }
}

void Lexer::AddToken(GlobalTokenType globalType, TokenType type)
{
    str_view fileView(m_File);
    m_Tokens.push_back(Token{
        fileView.substr(m_Start, m_Current - m_Start),
        m_Line,
        m_Column - (m_Current - m_Start),
        globalType,
        type
    });
}

bool Lexer::Match(char expected)
{
    if(IsAtEnd() == true) return false;
    else if(m_File[m_Current] != expected) return false;

    m_Current++;
    return true;
}

char &Lexer::NextChar()
{
    m_Column++;
    return m_File[m_Current++];
}

char Lexer::Peek()
{
    if (IsAtEnd()) return '\0';

    return m_File[m_Current];
}

void Lexer::String()
{
    while(Peek() != '"' && IsAtEnd() == false)
    {
        m_Column++;
        if(Peek() == '\n') 
        {
            m_Line++;
            m_Column = 1;
        }
        NextChar();
    }
    if(IsAtEnd())
    {
        std::cout << "String";
        throw std::runtime_error("No end string token");
    }
    
    NextChar();
    AddToken(GlobalTokenType::_DELIMITOR, TokenType::_DOUBLE_QUOTE);
}

void Lexer::Number()
{
    while(std::isdigit(Peek()) && IsAtEnd() == false)
        NextChar();

    AddToken(GlobalTokenType::_IDENTIFIER, TokenType::_VALUE);
}

void Lexer::Symbol()
{
    while((std::isalnum(Peek()) || Peek() == '_') && IsAtEnd() == false)
        NextChar();

    str word = m_File.substr(m_Start, m_Current - m_Start);
    if(m_Keyword.contains(word) == true)
        AddToken(GlobalTokenType::_KEYWORD, m_Keyword[word]);
    else if(m_Identifier.contains(word) == true)
        AddToken(GlobalTokenType::_IDENTIFIER, m_Identifier[word]);
    else
        AddToken(GlobalTokenType::_IDENTIFIER, TokenType::_SYMBOL);    
}