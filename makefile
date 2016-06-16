CC = g++
TARGETS = parser lex codegen-mips
OBJS = parser parserFunc lex genFunc codegen ruleFunc
CFLAGS = -g -I./src/lex -I./src/parser -I./src/codegen-mips -I./src -Wall

.PHONY: clean all parser lex codegen

all:
	@echo "Target: arc luison clean"
	
parser:
	make -C ./src/parser
	mv ./src/parser/*.o .

lex:
	make -C ./src/lex
	mv ./src/lex/*.o .

codegen-mips:
	make -C ./src/codegen-mips
	mv ./src/codegen-mips/*.o .
	
arc: $(TARGETS) $(foreach OBJ,$(OBJS),$(OBJ).o)
	$(CC) $(CFLAGS) -o arc ./src/arc.cpp $(foreach OBJ,$(OBJS),$(OBJ).o)
	make clean
	
luison: 
	make -C ./luison_src
	mv ./luison_src/luison .

clean:
	rm *.o
