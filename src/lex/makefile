CC = g++
OBJS = lex
CFLAGS = -g -I.. -I.

.PHONY: test clean lib all

all: test

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $< 

lib:
	$(CC) $(CFLAGS) -c -o lex.o lex.cpp 
	
test: $(foreach OBJ,$(OBJS),$(OBJ).o)
	$(foreach OBJ,$(OBJS),$(CC) $(CFLAGS) -o $(OBJ)_test $(OBJ)_test.cpp $(OBJ).o)
	
clean:
	rm *.o
