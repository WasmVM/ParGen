include_directories(../ ./)

ADD_LIBRARY (codegen STATIC codegen.cpp genFunc.cpp)
set_property(TARGET codegen PROPERTY CXX_STANDARD 11)
