add_library(luison
  Pxml.cpp
  exception.cpp
)

add_dependencies(luison
  pxml
)