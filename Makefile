CC=g++
CFLAGS=-Wall -g
OUTPUT=lexer.bin
INCLUDES=-Iinclude

lexer.bin: out/automata.o lexer.cpp
	$(CC) $(CFLAGS) lexer.cpp out/automata.o -o $(OUTPUT) $(INCLUDES)
out/automata.o: include/automata.h automata.cpp
	$(CC) $(CFLAGS) -c automata.cpp -o out/automata.o $(INCLUDES)
clean:
	rm -rf out/*.o
	rm lexer.bin
