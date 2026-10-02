# CMakeList.txt : projet CMake pour Assembly, incluez la source et définissez
# la logique spécifique au projet ici.
#
add_executable(Chessy_Lexer
      main.cpp
      Lexer.cpp
      Token.cpp
      CompilationTest.cpp
      LexerTest.cpp)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Chessy_Lexer PROPERTY CXX_STANDARD 20)
endif()

# TODO: Ajoutez des tests et installez des cibles si nécessaire.
