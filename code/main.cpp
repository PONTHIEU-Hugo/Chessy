#include "Lexer.h"



int main()
{
    str _TestFiles[6]{
    "../../../Test/Declaration.chessy",
    "../../../Test/Math_Operation.chessy",
    "../../../Test/Bool_Operation.chessy",
    "../../../Test/Bina_Operation.chessy",
    "../../../Test/Function.chessy",
    "../../../Test/Loop.chessy"
    };

    Lexer lex;
    for(str& rTestPath : _TestFiles)
    {
        if(lex.ReadFile(rTestPath) == false)
            std::runtime_error("Error reading test: " + rTestPath);

        lex.Tokenize();
        vector<Token>& rTokens = lex.GetTokens();

        std::cout << std::endl;
        for(Token& rToken : rTokens) rToken.Print();
        std::cout << std::endl << "End of a total of " << rTokens.size() << " token for the file: " << rTestPath
            << std::endl << "=====================================" << std::endl;
    }

    return 0;
}