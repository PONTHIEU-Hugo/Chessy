#include "Lexer.h"
#include "Parser.h"
#include "VM.h"
#include "ConstantContainer.h"

int main()
{
    // Lexer lexer;
    // lexer.ReadFile(data.string() + "/PipelineTest/Math_Operation.chessy");
    // lexer.Tokenize();
    // Parser parser;
    // parser.Parse(lexer.GetTokens());

    Chunk newChunk;

    ConstantContainer first{ ConstantType::_I8 };
    first.data.as_i8 = 1;
    newChunk.push_instruction({OpCode::_LOADC, 0, newChunk.push_constant(first)});

    ConstantContainer second{ ConstantType::_I16 };
    second.data.as_i16 = 2;
    newChunk.push_instruction({OpCode::_LOADC, 1, newChunk.push_constant(second)});
    
    newChunk.push_instruction({OpCode::_ADD, 2, 1, 0});

    newChunk.push_instruction({OpCode::_PRINT, 2});

    newChunk.push_instruction({OpCode::_HALT});

    VM vm;
    vm.SetChunk(&newChunk);
    vm.Run();

    return 0;
}