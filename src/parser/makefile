CXX = g++

OBJS = parser parserFunc ruleFunc

CFLAGS = -I.. -I. -I../lex -Wall

.PHONY: all build

all: build

%.o: %.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<

build: $(foreach OBJ,$(OBJS),$(OBJ).o)
