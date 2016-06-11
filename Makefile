CC=g++
CFLAGS=-Wall -g
OUTPUT=parser.bin
INCLUDES=-Iinclude

parser.bin: main.cpp out/parser.o out/output.o out/lexer.o out/helper.o
	$(CC) $(CFLAGS) main.cpp out/output.o out/parser.o out/lexer.o out/helper.o -o $(OUTPUT) $(INCLUDES)
out/parser.o: parser.cpp include/parser.h
	$(CC) $(CFLAGS) -c parser.cpp -o out/parser.o $(INCLUDES)
out/lexer.o: lexer.cpp include/lexer.h out/output.o
	$(CC) $(CFLAGS) -c lexer.cpp -o out/lexer.o $(INCLUDES)
out/output.o: output.cpp include/output.h include/options.h
	$(CC) $(CFLAGS) -c output.cpp -o out/output.o $(INCLUDES)
out/helper.o: helper.cpp include/helper.h
	$(CC) $(CFLAGS) -c helper.cpp -o out/helper.o $(INCLUDES)
clean:
	rm -rf out/*.o
	rm parser.bin
