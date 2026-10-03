#include "Lexer.h"
#include "Parser.h"

int main()
{
    Lexer lexer;
    lexer.ReadFile("PipelineTest/Math_Operation.chessy");
    lexer.Tokenize();
    Parser parser;
    parser.Parse(lexer.GetTokens());
    return 0;
}