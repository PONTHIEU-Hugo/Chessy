#include "Lexer.h"

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