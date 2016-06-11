#ifndef HELPER_H
#define HELPER_H

enum Type
{
    DEC,
    HEX,
    STRING,
    PLUS,
    MINUS,
    LEFT_SQ_BRACKET,
    RIGHT_SQ_BRACKET,
    COMMA,
    DOT,
    COLON,
    SEMICOLON,
    LESS_THAN,
    MORE_THAN,
    AT,
    HASH,
    FLOOR,
    DOUBLE_SLASH,
    EXCLAMATION,
    WHITESPACE,
    BAD_TOKEN,
    REGISTER,
    INSTRUCTION,
    CONDITION,
    NEWLINE,
    HEX_OR_INSTRUCTION
};

bool is_whitespace(char);
bool is_digit(char);
bool is_hex(char);
bool is_alpha(char);
char* type_to_string(Type);

#endif