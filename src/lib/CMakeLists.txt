include_directories(${PROJECT_BINARY_DIR}/src/pxml)
include_directories(${PROJECT_SOURCE_DIR}/src/pxml)

add_library(luison
  Pxml.cpp
  Parser.cpp
  exception.cpp
)

add_dependencies(luison
  pxml
)