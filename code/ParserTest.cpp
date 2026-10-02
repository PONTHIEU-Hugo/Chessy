#include "ParserTest.h"
#include "Lexer.h"
#include "Parser.h"
#include "CompilationTest.h"

void ParserTest::TestDeclaration()
{
    Lexer lex;
    CompilationTest::Assert(lex.ReadFile("../../../Test/Declaration.chessy") == true, "Declaration.chessy can't be read");
    lex.Tokenize();
    vector<Token>& tokens = lex.GetTokens();
    Parser parser;
    parser.Parse(tokens);

    CompilationTest::Assert()
}

void ParserTest::TestMathOperation()
{

}

void ParserTest::TestBoolOperation()
{

}

void ParserTest::TestBinaOperation()
{

}

void ParserTest::TestFunction()
{

}

void ParserTest::TestLoop()
{

}