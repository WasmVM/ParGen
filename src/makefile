CC = g++
OBJS = lex
CFLAGS = -g

.PHONY: test clean

%.o: %.cpp %.hpp
	$(CC) $(CFLAGS) -c -o $@ $< 
	
test: $(foreach OBJ,$(OBJS),$(OBJ).o)
	$(foreach OBJ,$(OBJS),$(CC) $(CFLAGS) -o $(OBJ)_test $(OBJ)_test.cpp $(OBJ).o)
	
clean:
	rm *.o
