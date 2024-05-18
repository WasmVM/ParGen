add_executable(pargen-exec
  pargen.cpp
  CommandParser.cpp
)
target_link_libraries(pargen-exec
  pargen
)
set_target_properties(pargen-exec PROPERTIES OUTPUT_NAME "pargen")
target_compile_definitions(pargen PUBLIC
  PARGEN_VERSION="${CMAKE_PROJECT_VERSION}"
)
