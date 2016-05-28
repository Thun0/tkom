CC=g++
CFLAGS=-Wall -g
OUTPUT=parser.bin
INCLUDES=-Iinclude

lexer.bin: parser.cpp out/output.o
	$(CC) $(CFLAGS) parser.cpp out/output.o -o $(OUTPUT) $(INCLUDES)
out/output.o: include/output.h output.cpp include/options.h
	$(CC) $(CFLAGS) -c output.cpp -o out/output.o $(INCLUDES)
clean:
	rm -rf out/*.o
	rm parser.bin
