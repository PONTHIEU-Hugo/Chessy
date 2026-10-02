# Code commun : tout sauf main.cpp
add_library(chessy_core STATIC
    Token.cpp
    Lexer.cpp
    Parser.cpp
)
target_include_directories(chessy_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_definitions(chessy_core PUBLIC
    PROJECT_ROOT="${CMAKE_SOURCE_DIR}")

# Programme principal
add_executable(Chessy_Lexer main.cpp)
target_link_libraries(Chessy_Lexer PRIVATE chessy_core)