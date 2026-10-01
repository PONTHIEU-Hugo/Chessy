#pragma once
#include "Defines.h"
#include "Token.h"

class Lexer
{
private:
    un_map<str, TokenType> m_Identifier;
    un_map<str, TokenType> m_Keyword;

    str m_File;
    vector<Token> m_Tokens;

    int m_Start;
    int m_Current;
    u32 m_Line;
    u32 m_Column;

public:
    Lexer();
    ~Lexer() = default;

    bool ReadFile(str _path);
    void Tokenize();

    vector<Token>& GetTokens() { return m_Tokens; }

private:
    void ScanToken();
    void AddToken(GlobalTokenType globalType, TokenType type);

    bool IsAtEnd() { return m_Current == m_File.size(); }
    bool Match(char expected);
    char& NextChar();
    char Peek();

    void String();
    void Number();
    void Symbol();
};