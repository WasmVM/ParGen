CXX = g++

OBJS = codegen genFunc

CFLAGS = -I.. -I. -Wall

.PHONY: all build

all: build

%.o: %.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<

build: $(foreach OBJ,$(OBJS),$(OBJ).o)
	
