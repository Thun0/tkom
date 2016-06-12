#include <cstring>

#include "lexer.h"
#include "output.h"

void Lexer::initialize_set(char* filename, std::set <uint64_t>* s)
{
    FILE* file = fopen(filename, "r+");
    if(!file)
    {
        print_fatal("Couldn't open set file!\n");
    }
    print_log("Set file opened\n");

    char* line = NULL;
    size_t line_len = 0;
    while(getline(&line, &line_len, file) != -1)
    {
        line_len = strlen(line);
        if(line[line_len-1] == '\n')
            line[--line_len] = '\0';
        unsigned it = 0;
        uint64_t hash = 0;
        while(it < line_len)
        {
            hash <<= 8;
            hash += line[it++];
        }
        if(s->find(hash) != s->end())
        {
            print_fatal("TWO STRINGS WITH SAME HASH!\n");
        }
        s->insert(hash);
        line = NULL;
        line_len = 0;
    }
    print_log("Filled set\n");
    fclose(file);
}

Type Lexer::get_hex(char &c, std::string &str)
{
    while(is_hex(c))
    {
        str += c;
        c = fgetc(input_file);
    }
    return HEX;
}

Type Lexer::get_whitespace(char &c, std::string &str)
{
    while(is_whitespace(c))
    {
        str += c;
        c = fgetc(input_file);
    }
    return WHITESPACE;
}

Type Lexer::get_type_by_hash(uint64_t hash)
{
    if(instruction_set.find(hash) != instruction_set.end())
        return INSTRUCTION;
    if(condition_set.find(hash) != condition_set.end())
        return CONDITION;
    if(register_set.find(hash) != register_set.end())
        return REGISTER;
    return STRING;
}

Type Lexer::get_token(char &c, std::string &str)
{
    str = "";
    if(is_whitespace(c))
    {
        return get_whitespace(c, str);
    }
    if(c == '0')
    {
        str += c;
        c = fgetc(input_file);
        if(c == 'x')
        {
            str += c;
            c = fgetc(input_file);
            return get_hex(c, str);
        }
        while(is_digit(c))
        {
            str += c;
            c = fgetc(input_file);
        }
        if(is_hex(c))
        {
            return get_hex(c, str);
        }
        else
        {
            return DEC;
        }
    }
    if(is_digit(c))
    {
        while(is_digit(c))
        {
            str += c;
            c = fgetc(input_file);
        }
        if(is_hex(c))
        {
            return get_hex(c, str);
        }
        else
        {
            return DEC;
        }
    } 
    if(is_alpha(c) || c == '.' || c == '_')
    {
        uint64_t hash = 0;
        if(is_hex(c))
        {
            while(is_hex(c))
            {
                hash <<= 8;
                hash += c;
                str += c;
                c = fgetc(input_file);
            }
            if(is_alpha(c) || is_digit(c) || c == '.' || c =='_')
            {
                while(is_alpha(c) || is_digit(c) || c == '.' || c =='_')
                {
                    hash <<= 8;
                    hash += c;
                    str += c;
                    c = fgetc(input_file);
                }
                return get_type_by_hash(hash);
            }
            else if(instruction_set.find(hash) != instruction_set.end())
                    return HEX_OR_INSTRUCTION;
            else
                return HEX;
        }
        else
        {
            while(is_alpha(c) || is_digit(c) || c == '.' || c =='_')
            {
                hash <<= 8;
                hash += c;
                str += c;
                c = fgetc(input_file);
            }
            return get_type_by_hash(hash);
        }
    }
    str += c;
    if(c == '/')
    {
        c = fgetc(input_file);
        str += c;
        if(c == '/')
        {
            c = fgetc(input_file);
            return DOUBLE_SLASH;
        }
        else 
            return BAD_TOKEN;
    }
    char s = c;
    c = fgetc(input_file);
    switch(s)
    {
        case '!':
            return EXCLAMATION;
        case '\n':
            return NEWLINE;
        case '#':
            return HASH;
        case ':':
            return COLON;
        case ';':
            return SEMICOLON;
        case '[':
            return LEFT_SQ_BRACKET;
        case ']':
            return RIGHT_SQ_BRACKET;
        case ',':
            return COMMA;
        case '@':
            return AT;
        case '+':
            return PLUS;
        case '-':
            return MINUS;
        case '<':
            return LESS_THAN;
        case '>':
            return MORE_THAN;
        default:
            return BAD_TOKEN;
    }
}

Lexer::Lexer(FILE* file)
{
    input_file = file;
    initialize_set((char*)"res/arm-instruction-set", &instruction_set);
    initialize_set((char*)"res/conditions", &condition_set);
    initialize_set((char*)"res/registers", &register_set);
}

Lexer::~Lexer()
{

}