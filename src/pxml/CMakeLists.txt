add_custom_command(OUTPUT pxml_parser.cpp
  COMMAND flex ${CMAKE_CURRENT_SOURCE_DIR}/pxml.l
  DEPENDS pxml.l
)

add_library(pxml
  pxml_parser.cpp
)

add_executable(pxml-dump
  dump.cpp
)
target_link_libraries(pxml-dump pxml)