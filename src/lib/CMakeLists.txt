include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_custom_command(OUTPUT pxml_parser.cpp
  COMMAND bison --header=${CMAKE_CURRENT_BINARY_DIR}/pxml_parser.hpp --output=${CMAKE_CURRENT_BINARY_DIR}/pxml_parser.cpp ${PROJECT_SOURCE_DIR}/src/pxml/pxml.y
  DEPENDS ${PROJECT_SOURCE_DIR}/src/pxml/pxml.y
)

add_custom_command(OUTPUT pxml_lexer.cpp
  COMMAND flex ${PROJECT_SOURCE_DIR}/src/pxml/pxml.l
  DEPENDS ${PROJECT_SOURCE_DIR}/src/pxml/pxml.l pxml_parser.cpp
)

add_library(pxml
  Pxml.cpp
  exception.cpp
  pxml_parser.cpp
  pxml_lexer.cpp
)

add_library(pargen
  ParGen.cpp
  elements.cpp
)