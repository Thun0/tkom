CC=g++
CFLAGS=-Wall -g
OUTPUT=lexer.bin

all: automata.h
	$(CC) $(CFLAGS) lexer.cpp automata.cpp -o $(OUTPUT)

