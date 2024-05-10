include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

find_package(BISON)
find_package(FLEX)

BISON_TARGET(pxml_parser ${PROJECT_SOURCE_DIR}/src/pxml/pxml.y ${CMAKE_CURRENT_BINARY_DIR}/pxml_parser.cpp
  DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/pxml_parser.hpp
)

add_custom_command(OUTPUT pxml_lexer.cpp
  COMMAND flex -o ${CMAKE_CURRENT_BINARY_DIR}/pxml_lexer.cpp ${PROJECT_SOURCE_DIR}/src/pxml/pxml.l 
  DEPENDS pxml_parser
)

add_library(pxml
  Pxml.cpp
  exception.cpp
  ${BISON_pxml_parser_OUTPUTS}
  ${CMAKE_CURRENT_BINARY_DIR}/pxml_lexer.cpp
  Util.cpp
)

add_library(pargen
  ParGen.cpp
  elements.cpp
  tokens.cpp
  lexer.cpp
)