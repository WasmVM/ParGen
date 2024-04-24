add_executable(luison-lex
  lex.cpp
  CommandParser.cpp
)
target_link_libraries(luison-lex
  luison
)
target_compile_definitions(luison-lex PUBLIC
  LUISON_VERSION="${CMAKE_PROJECT_VERSION}"
)