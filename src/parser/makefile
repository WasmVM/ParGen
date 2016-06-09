CC = g++
OBJS = parser parserFunc
EXTERN = ../lex/lex.o
CFLAGS = -g -I../lex -I.. -I.

.PHONY: test clean all

all: test

../lex/lex.o:
	make -C ../lex -f makefile lib

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $< 
	
test: $(foreach OBJ,$(OBJS),$(OBJ).o) $(EXTERN)
	$(CC) $(CFLAGS) -o parser_test parser_test.cpp $(foreach OBJ,$(OBJS),$(OBJ).o) $(EXTERN)
	
clean:
	rm *.o
