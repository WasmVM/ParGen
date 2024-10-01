include_directories(${CMAKE_CURRENT_BINARY_DIR})
add_custom_command(OUTPUT PxmlLexer.cpp PxmlToken.cpp PxmlParser.cpp
  COMMAND $<TARGET_FILE:pargen-exec> ${CMAKE_CURRENT_LIST_DIR}/pxml.pxml
  DEPENDS pargen-exec ${CMAKE_CURRENT_LIST_DIR}/pxml.pxml
)
add_executable(pxml-dump
  dump.cpp
  PxmlLexer.cpp
  PxmlParser.cpp
  PxmlToken.cpp
)
if(BUILD_TESTS)
  add_test(NAME example_pxml
    COMMAND ${CMAKE_COMMAND} 
      -DPXML_DUMP=$<TARGET_FILE:pxml-dump>
      -DPXML_PXML=${CMAKE_CURRENT_LIST_DIR}/pxml.pxml
      -P ${CMAKE_CURRENT_LIST_DIR}/test.cmake
  )
endif(BUILD_TESTS)