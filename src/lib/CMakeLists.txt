include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(PXML_USE_BISON OFF CACHE BOOL "Generate pxml parser with bison")

if(PXML_USE_BISON)
find_package(BISON)
find_package(FLEX)

BISON_TARGET(pxml_parser ${PROJECT_SOURCE_DIR}/src/pxml/pxml.y ${CMAKE_CURRENT_BINARY_DIR}/pxml_parser.cpp
  DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/pxml_parser.hpp
)

add_custom_command(OUTPUT pxml_lexer.cpp
  COMMAND flex -o ${CMAKE_CURRENT_BINARY_DIR}/pxml_lexer.cpp ${PROJECT_SOURCE_DIR}/src/pxml/pxml.l 
  DEPENDS pxml_parser ${PROJECT_SOURCE_DIR}/src/pxml/pxml.l
)
endif(PXML_USE_BISON)

add_library(pargen
  ParGen.cpp
  elem.cpp
  tokens.cpp
  exception.cpp
  Util.cpp
  lexer/use.cpp
  lexer/lexer.cpp
  lexer/node.cpp
  lexer/autometa.cpp
  parser/parser.cpp
  parser/dump.cpp
)

if(PXML_USE_BISON)
target_sources(pargen
  PRIVATE ${BISON_pxml_parser_OUTPUTS}
  PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/pxml_lexer.cpp
)
target_compile_definitions(pargen PUBLIC USE_BISON)
else(PXML_USE_BISON)
target_sources(pargen
  PRIVATE PxmlToken.cpp
  PRIVATE PxmlLexer.cpp
  PRIVATE PxmlParser.cpp
)
endif(PXML_USE_BISON)

install(TARGETS pargen
  LIBRARY DESTINATION lib
  COMPONENT libs
)