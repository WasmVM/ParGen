cmake_minimum_required(VERSION 3.16)
project(pargen VERSION 0.0.1)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED 11)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED 20)

set(CONSOLE_COLOR ON CACHE BOOL "Turn on color in console result")
if(CONSOLE_COLOR)
  add_compile_definitions(CONSOLE_COLOR)
endif(CONSOLE_COLOR)

include_directories(${CMAKE_CURRENT_LIST_DIR}/src/include)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
add_subdirectory(src)

set(BUILD_EXAMPLES ON CACHE BOOL "Build examples")
if(BUILD_EXAMPLES)
  add_subdirectory(example)
endif(BUILD_EXAMPLES)

set(BUILD_DOCS ON CACHE BOOL "Build documentation")
if(BUILD_DOCS)
  add_subdirectory(docs)
endif(BUILD_DOCS)

include(pack)
cpack_add_component(programs DISPLAY_NAME "Programs"
  DESCRIPTION "ParGen programs"
)
cpack_add_component(libs DISPLAY_NAME "Libraries"
  DESCRIPTION "ParGen libraries"
)