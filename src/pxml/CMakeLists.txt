include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_custom_command(OUTPUT pxml_parser.cpp
  COMMAND bison --header=${CMAKE_CURRENT_BINARY_DIR}/pxml_parser.hpp --output=${CMAKE_CURRENT_BINARY_DIR}/pxml_parser.cpp ${CMAKE_CURRENT_SOURCE_DIR}/pxml.y
  DEPENDS pxml.y
)

add_custom_command(OUTPUT pxml_lexer.cpp
  COMMAND flex ${CMAKE_CURRENT_SOURCE_DIR}/pxml.l
  DEPENDS pxml.l pxml_parser.cpp
)

add_library(pxml
  pxml_parser.cpp
  pxml_lexer.cpp
)

add_executable(pxml-dump
  ../lib/Parser.cpp
  dump.cpp
)
target_link_libraries(pxml-dump pxml)