include_directories(./)
set(CMAKE_CXX_COMPILER clang++)
ADD_EXECUTABLE (luison luison.cpp)
install(TARGETS luison
	RUNTIME DESTINATION ~/arc
)
