#include "helper.h"

char* type_to_string(Type t)
{
    switch(t)
    {
        case DEC:
            return (char*)"DEC";
        case HEX:
            return (char*)"HEX";
        case STRING:
            return (char*)"STRING";
        case PLUS:
            return (char*)"+";
        case MINUS:
            return (char*)"-";
        case LEFT_SQ_BRACKET:
            return (char*)"[";
        case RIGHT_SQ_BRACKET:
            return (char*)"]";
        case COMMA:
            return (char*)",";
        case DOT:
            return (char*)".";
        case COLON:
            return (char*)":";
        case SEMICOLON:
            return (char*)";";
        case LESS_THAN:
            return (char*)"<";
        case MORE_THAN:
            return (char*)">";
        case AT:
            return (char*)"@";
        case HASH:
            return (char*)"#";
        case FLOOR:
            return (char*)"FLOOR";
        case DOUBLE_SLASH:
            return (char*)"//";
        case EXCLAMATION:
            return (char*)"!";
        case WHITESPACE:
            return (char*)"WHITESPACE";
        case BAD_TOKEN:
            return (char*)"BAD_TOKEN";
        case REGISTER:
            return (char*)"REGISTER";
        case INSTRUCTION:
            return (char*)"INSTRUCTION";
        case CONDITION:
            return (char*)"CONDITION";
        case NEWLINE:
            return (char*)"NEWLINE";
        case HEX_OR_INSTRUCTION:
            return (char*)"HEX_OR_INSTRUCTION";
        default:
            return (char*)"INVALID_TYPE";
    }
}

bool is_whitespace(char c)
{
    return (c == ' ' || c == '\t');
}

bool is_digit(char c)
{
    return (c >= '0' && c <= '9');
}

bool is_hex(char c)
{
    return ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f'));
}

bool is_alpha(char c)
{
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}