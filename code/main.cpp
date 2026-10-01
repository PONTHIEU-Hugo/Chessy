#include "Lexer.h"
#include <filesystem>

void Token::Print()
{
    std::cout << line << ":" << column << " => ";
    switch (globalType)
    {
    case GlobalTokenType::_LITTERAL:
        std::cout << "_LITTERAL";
        break;
    case GlobalTokenType::_IDENTIFIER:
        std::cout << "_IDENTIFIER";
        break;
    case GlobalTokenType::_OPERAND:
        std::cout << "_OPERAND";
        break;
    case GlobalTokenType::_KEYWORD:
        std::cout << "_KEYWORD";
        break;
    case GlobalTokenType::_DELIMITOR:
        std::cout << "_DELIMITOR";
        break;
    }  
    std::cout << ": " << view << std::endl;
}

int main()
{
    Lexer lex;
    if(lex.ReadFile("../../../code/main.chessy") == false) std::cout << "alert";
    lex.Tokenize();
    vector<Token> tokens = lex.GetTokens();
    for(Token& token : tokens) token.Print();

    std::cout << "End of " << tokens.size() << " token" << std::endl;

    return 0;
}