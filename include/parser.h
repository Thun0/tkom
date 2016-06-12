#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

class Parser
{
    FILE* input_file;
    Lexer* lexer;
    Parser();
    void open_file(char*);
    void check_next_token(Type, char&, std::string&);
    void parse_comment_symbol(char&, std::string&);
    void parse_x_symbol(Type, char&, std::string&);
    void parse_start_symbol(Type, char&, std::string&);
    void parse_z_symbol(char&, std::string&);
    Type parse_operands_symbol(char&, std::string&);
    Type parse_y_symbol(char&, std::string&);
    Type parse_instruction_symbol(char&, std::string&);
public:
    void parse();
    Parser(char*);
    ~Parser();
};

#endif