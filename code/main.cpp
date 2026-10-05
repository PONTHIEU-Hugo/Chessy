#include "Lexer.h"
#include "Parser.h"
#include "Analyser.h"

int main()
{
    Lexer lexer;
    lexer.ReadFile("code/main.chessy");
    lexer.Tokenize();
    Parser parser;
    parser.Parse(lexer.GetTokens());
    Analyser analyser = Analyser(parser.GetProgram());
    analyser.Analyse();
    analyser.PrintErrors();
    return 0;
}