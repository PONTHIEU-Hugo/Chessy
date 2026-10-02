#include "CompilationTest.h"


void CompilationTest::RunTest()
{
    TestLexer();
    TestParser();
    TestSEMA();
}

void CompilationTest::TestLexer()
{
    LexerTest::TestDeclaration();
    LexerTest::TestMathOperation();
    LexerTest::TestBoolOperation();
    LexerTest::TestBinaOperation();
    LexerTest::TestFunction();
    LexerTest::TestLoop();
}

void CompilationTest::TestParser()
{
    // TODO: Fill parser's Test
}

void CompilationTest::TestSEMA()
{
    // TODO: Fill SEMA's Test
}

void CompilationTest::Assert(const bool condition, const str msg, const i32 errorCode, const std::source_location loc)
{
    if(condition == true) return;

    if(msg == "")
        std::cout << "Test fail at line: " << loc.line() << " and column: " << loc.column()
                << " in the function: " << loc.function_name()
                << std::endl;
    else
        std::cout << msg << std::endl;
    exit(errorCode);
}