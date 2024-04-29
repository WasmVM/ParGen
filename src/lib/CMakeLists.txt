include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

find_package(BISON)
find_package(FLEX)

BISON_TARGET(pxml_parser ${PROJECT_SOURCE_DIR}/src/pxml/pxml.y ${CMAKE_CURRENT_BINARY_DIR}/pxml_parser.cpp
  DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/pxml_parser.hpp
)

FLEX_TARGET(pxml_lexer ${PROJECT_SOURCE_DIR}/src/pxml/pxml.l ${CMAKE_CURRENT_BINARY_DIR}/pxml_lexer.cpp)
ADD_FLEX_BISON_DEPENDENCY(pxml_lexer pxml_parser)

add_library(pxml
  Pxml.cpp
  exception.cpp
  ${BISON_pxml_parser_OUTPUTS}
  ${FLEX_pxml_lexer_OUTPUTS}
)

add_library(pargen
  ParGen.cpp
  elements.cpp
)