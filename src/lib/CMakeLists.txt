include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

find_package(BISON)
find_package(FLEX)

BISON_TARGET(pxml_parser ${PROJECT_SOURCE_DIR}/src/pxml/pxml.y ${CMAKE_CURRENT_BINARY_DIR}/pxml_parser.cpp
  DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/pxml_parser.hpp
)

add_custom_command(OUTPUT pxml_lexer.cpp
  COMMAND flex -o ${CMAKE_CURRENT_BINARY_DIR}/pxml_lexer.cpp ${PROJECT_SOURCE_DIR}/src/pxml/pxml.l 
  DEPENDS pxml_parser ${PROJECT_SOURCE_DIR}/src/pxml/pxml.l
)

add_library(pargen
  ParGen.cpp
  elem.cpp
  tokens.cpp
  exception.cpp
  Util.cpp
  ${BISON_pxml_parser_OUTPUTS}
  ${CMAKE_CURRENT_BINARY_DIR}/pxml_lexer.cpp
  lexer/use.cpp
  lexer/lexer.cpp
  lexer/node.cpp
  lexer/autometa.cpp
  parser/parser.cpp
  parser/base.cpp
)