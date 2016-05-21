#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <stdint.h>
#include <map>
#include <set>
#include <utility>

#include "options.h"
#include "output.h"

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
    BAD_TOKEN
};

FILE* input_file;
Options options;
std::set <uint64_t> instruction_set;
std::set <uint64_t> condition_set;

void initialize_set(char* filename, std::set <uint64_t>* s)
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
        s->insert(hash);
        line = NULL;
        line_len = 0;
    }
    print_log("Filled set\n");
    fclose(file);
}

void printUsage()
{
    printf("Usage: lexer [FILE]");
    printf("\nRun lexer on provided FILE");
    printf("\n");
}

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
            return (char*)"PLUS";
        case MINUS:
            return (char*)"MINUS";
        case LEFT_SQ_BRACKET:
            return (char*)"LEFT_SQ_BRACKET";
        case RIGHT_SQ_BRACKET:
            return (char*)"RIGHT_SQ_BRACKET";
        case COMMA:
            return (char*)"COMMA";
        case DOT:
            return (char*)"DOT";
        case COLON:
            return (char*)"COLON";
        case SEMICOLON:
            return (char*)"SEMICOLON";
        case LESS_THAN:
            return (char*)"LESS_THAN";
        case MORE_THAN:
            return (char*)"MORE_THAN";
        case AT:
            return (char*)"AT";
        case HASH:
            return (char*)"HASH";
        case FLOOR:
            return (char*)"FLOOR";
        case DOUBLE_SLASH:
            return (char*)"DOUBLE_SLASH";
        case EXCLAMATION:
            return (char*)"EXCLAMATION";
        case WHITESPACE:
            return (char*)"WHITESPACE";
        case BAD_TOKEN:
            return (char*)"BAD_TOKEN";
        default:
            return (char*)"INVALID_TYPE";
    }
}

bool is_whitespace(char c)
{
    return (c == '\n' || c == ' ' || c == '\r' || c == '\t');
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

Type get_token(char &c)
{
    if(is_whitespace(c))
    {
        while(is_whitespace(c))
            c = fgetc(input_file);
        return WHITESPACE;
    }
    if(c == '/')
    {
        c = fgetc(input_file);
        if(c == '/')
        {
            c = fgetc(input_file);
            return DOUBLE_SLASH;
        }
        else 
        {
            c = fgetc(input_file);
            return BAD_TOKEN;
        }
    }
    if(c == '!')
    {
        c = fgetc(input_file);
        return EXCLAMATION;
    }
    if(c == '#')
    {
        c = fgetc(input_file);
        return HASH;
    }
    if(c == '[')
    {
        c = fgetc(input_file);
        return LEFT_SQ_BRACKET;
    }
    if(c == ']')
    {
        c = fgetc(input_file);
        return RIGHT_SQ_BRACKET;
    }
    if(c == ',')
    {
        c = fgetc(input_file);
        return COMMA;
    }
    if(c == '@')
    {
        c = fgetc(input_file);
        return AT;
    }
    if(c == '+')
    {
        c = fgetc(input_file);
        return PLUS;
    }
    if(c == '-')
    {
        c = fgetc(input_file);
        return MINUS;
    }
    if(c == '<')
    {
        c = fgetc(input_file);
        return LESS_THAN;
    }
    if(c == '>')
    {
        c = fgetc(input_file);
        return MORE_THAN;
    }
    if(c == '0')
    {
        c = fgetc(input_file);
        if(c == 'x')
        {
            c = fgetc(input_file);
            while(is_hex(c))
                c = fgetc(input_file);
            return HEX;
        }
        while(is_digit(c))
        {
            c = fgetc(input_file);
        }
        if(is_hex(c))
        {
            while(is_hex(c))
                c = fgetc(input_file);
            return HEX;
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
            c = fgetc(input_file);
        }
        if(is_hex(c))
        {
            while(is_hex(c))
                c = fgetc(input_file);
            return HEX;
        }
        else
        {
            return DEC;
        }
    } 
    if(is_hex(c))
    {
        while(is_hex(c))
                c = fgetc(input_file);
            return HEX;
    }
    c = fgetc(input_file);
    return BAD_TOKEN;
}

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        printUsage();
        return 0;
    }
    options.verbose = true;
    char* filepath = argv[1];    
    input_file = fopen(filepath, "r");
    if(input_file == NULL)
    {
        print_fatal("Error while reading file: %s\n", filepath);
    }
    print_log("File \"%s\" opened\n", filepath);
    initialize_set((char*)"res/arm-instruction-set", &instruction_set);
    initialize_set((char*)"res/conditions", &condition_set);

    char c = fgetc(input_file);
    while((c != EOF))
    {
        //printf("char %c\n", c);
        Type token = get_token(c);
        //if(token != WHITESPACE)
            printf("%s\n", type_to_string(token));
        //if(token == BAD_TOKEN)
        //    return -1;
    }
    print_log("End of file\n");
    print_log("Finished\n");
    return 0;
}