include_directories(../ ./)

ADD_LIBRARY (parser STATIC parser.cpp parserFunc.cpp ruleFunc.cpp)
set_property(TARGET parser PROPERTY CXX_STANDARD 11)
