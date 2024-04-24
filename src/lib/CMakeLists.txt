add_library(pxml OBJECT
  Pxml.cpp
)

add_library(luison
  $<TARGET_OBJECTS:pxml>
  exception.cpp
)