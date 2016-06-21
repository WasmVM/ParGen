include_directories(../ ./)

ADD_LIBRARY (lex STATIC lex.cpp)
set_property(TARGET lex PROPERTY CXX_STANDARD 11)
