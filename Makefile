CC=g++
CFLAGS=-Wall

all: automata.h
	$(CC) $(CFLAGS) lexer.cpp automata.cpp -o lexer

