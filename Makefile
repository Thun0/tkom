CC=g++
CFLAGS=-Wall -g
OUTPUT=lexer.bin
INCLUDES=-Iinclude

lexer.bin: lexer.cpp out/output.o
	$(CC) $(CFLAGS) lexer.cpp out/output.o -o $(OUTPUT) $(INCLUDES)
out/output.o: include/output.h output.cpp include/options.h
	$(CC) $(CFLAGS) -c output.cpp -o out/output.o $(INCLUDES)
clean:
	rm -rf out/*.o
	rm lexer.bin
