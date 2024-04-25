cmake_minimum_required(VERSION 3.16)
project(luison VERSION 0.0.1)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED 11)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED 20)

set(CONSOLE_COLOR ON CACHE BOOL "Turn on color in console result")
if(CONSOLE_COLOR)
  add_compile_definitions(CONSOLE_COLOR)
endif(CONSOLE_COLOR)

include_directories(${CMAKE_CURRENT_LIST_DIR}/src/include)
add_subdirectory(src)

