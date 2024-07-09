include_directories(${CMAKE_CURRENT_BINARY_DIR})
add_custom_command(OUTPUT PxmlLexer.cpp PxmlToken.cpp PxmlParser.cpp
  COMMAND ${PROJECT_BINARY_DIR}/src/exec/pargen ${CMAKE_CURRENT_LIST_DIR}/pxml.pxml
  DEPENDS pargen-exec ${CMAKE_CURRENT_LIST_DIR}/pxml.pxml
)
add_executable(pxml-dump
  dump.cpp
  PxmlLexer.cpp
  PxmlParser.cpp
  PxmlToken.cpp
)