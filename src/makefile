CC = g++
OBJS = lex

.PHONY: test clean

%.o: %.cpp %.hpp
	$(CC) -c -o $@ $< 
	
test: $(foreach OBJ,$(OBJS),$(OBJ).o)
	$(foreach OBJ,$(OBJS),$(CC) -o $(OBJ)_test $(OBJ)_test.cpp $(OBJ).o)
	
clean:
	rm *.o
