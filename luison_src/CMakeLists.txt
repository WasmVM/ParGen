include_directories(./)
ADD_EXECUTABLE (luison luison.cpp)
install(TARGETS luison
	RUNTIME DESTINATION ~/arc
)
