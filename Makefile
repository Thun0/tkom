CC=g++
CFLAGS=-Wall -g
OUTPUT=lexer.bin
INCLUDES=-Iinclude
OUTS=out

lexer.bin: $(OUTS)/automata.o
	$(CC) $(CFLAGS) lexer.cpp $(OUTS)/automata.o -o $(OUTPUT) $(INCLUDES)
$(OUTS)/automata.o: include/automata.h
	$(CC) $(CFLAGS) -c automata.cpp -o $(OUTS)/automata.o $(INCLUDES)
clean:
	rm -rf *.o
