#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

class Parser
{
    FILE* input_file;
    Lexer* lexer;
    Parser();
    void comment_symbol(char&, std::string&);
    Type instruction_symbol(char&, std::string&);
    void x_symbol(Type, char&, std::string&);
    void start_symbol(Type, char&, std::string&);
    void check_next_token(Type, char&, std::string&);
    Type operands_symbol(char&, std::string&);
    Type y_symbol(char&, std::string&);
    void z_symbol(char&, std::string&);
    void open_file(char*);
public:
    void parse();
    Parser(char*);
    ~Parser();
};

#endif