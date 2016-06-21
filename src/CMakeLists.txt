include_directories(./ ./lex ./parser ./codegen-mips)

ADD_SUBDIRECTORY (lex)
ADD_SUBDIRECTORY (parser)
ADD_SUBDIRECTORY (codegen-mips)
ADD_EXECUTABLE (arc arc.cpp)
set_property(TARGET arc PROPERTY CXX_STANDARD 11)
target_link_libraries(arc codegen)
target_link_libraries(arc lex)
target_link_libraries(arc parser)
install(TARGETS arc
    RUNTIME DESTINATION /usr/local/bin
    )
