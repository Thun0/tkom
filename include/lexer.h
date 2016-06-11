#ifndef LEXER_H
#define LEXER_H

#include <cstdio>
#include <set>
#include <string>
#include <stdint.h>

#include "helper.h"

class Lexer
{
    FILE* input_file;
    std::set <uint64_t> instruction_set;
    std::set <uint64_t> condition_set;
    std::set <uint64_t> register_set;
    Lexer();
public:
    Type get_token(char &c, std::string &str);
    void initialize_set(char*, std::set <uint64_t>*);
    Lexer(FILE*);
    ~Lexer();
};

#endif