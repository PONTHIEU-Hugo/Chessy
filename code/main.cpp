#include "Lexer.h"
#include "Parser.h"
#include "Analyser.h"
#include "Compiler.h"

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
    if (analyser.HasErrors())
        return 0;
    Compiler compiler;
    compiler.Compile(parser.GetProgram());
    return 0;
}