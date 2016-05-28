#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <stdint.h>
#include <set>
#include <string>

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
    BAD_TOKEN,
    REGISTER,
    INSTRUCTION,
    CONDITION
};

FILE* input_file;
Options options;
std::set <uint64_t> instruction_set;
std::set <uint64_t> condition_set;
std::set <uint64_t> register_set;

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

Type get_token(char &c, std::string &str)
{
    str = "";
    if(is_whitespace(c))
    {
        while(is_whitespace(c))
        {
            str += c;
            c = fgetc(input_file);
        }
        return WHITESPACE;
    }
    if(c == '0')
    {
        str += c;
        c = fgetc(input_file);
        if(c == 'x')
        {
            str += c;
            c = fgetc(input_file);
            while(is_hex(c))
            {
                str += c;
                c = fgetc(input_file);
            }
            return HEX;
        }
        while(is_digit(c))
        {
            str += c;
            c = fgetc(input_file);
        }
        if(is_hex(c))
        {
            while(is_hex(c))
            {
                str += c;
                c = fgetc(input_file);
            }
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
            str += c;
            c = fgetc(input_file);
        }
        if(is_hex(c))
        {
            while(is_hex(c))
            {
                str += c;
                c = fgetc(input_file);
            }
            return HEX;
        }
        else
        {
            return DEC;
        }
    } 
    if(is_alpha(c) || c == '.' || c == '_')
    {
        int hash = 0;
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
                if(instruction_set.find(hash) != instruction_set.end())
                    return INSTRUCTION;
                if(condition_set.find(hash) != condition_set.end())
                    return CONDITION;
                if(register_set.find(hash) != register_set.end())
                    return REGISTER;
                return STRING;
            }
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
            if(instruction_set.find(hash) != instruction_set.end())
                return INSTRUCTION;
            if(condition_set.find(hash) != condition_set.end())
                return CONDITION;
            if(register_set.find(hash) != register_set.end())
                return REGISTER;
            return STRING;
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
    if(c == ':')
    {
        c = fgetc(input_file);
        return COLON;
    }
    if(c == ';')
    {
        c = fgetc(input_file);
        return SEMICOLON;
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
    return BAD_TOKEN;
}



/**************************/
/****     PARSER       ****/
/**************************/
void check_next_token(Type token, char& c, std::string& str)
{
    Type read_token = get_token(c, str);
    printf("Got token: %s\n", str.c_str());
    if(read_token != token)
    {
        print_fatal("Syntax error: expected %s but got %s which is %s\n", type_to_string(token), str.c_str(), type_to_string(read_token));
    }
}

void operands_symbol(char& c, std::string& str)
{
    print_fatal("Operands not yet supported\n\n\n");
}

void instruction_symbol(char& c, std::string& str)
{
    check_next_token(INSTRUCTION, c, str);
    check_next_token(WHITESPACE, c, str);
    operands_symbol(c, str);
}

void x_symbol(Type token, char& c, std::string& str)
{
    if(token != STRING)
        print_fatal("Syntax error: expected string but got %s\n", str.c_str());
    token = get_token(c, str);
    printf("Got token: %s\n", str.c_str());
    if(token == MINUS || token == PLUS)
    {
        check_next_token(HEX, c, str);
        check_next_token(MORE_THAN, c, str);
    }
    else if(token != MORE_THAN)
    {
        print_fatal("Syntax error: expected '>' but got %s which is %s\n", str.c_str(), type_to_string(token));
    }
    check_next_token(COLON, c, str);
    check_next_token(WHITESPACE, c, str);
}

void start_symbol(Type token, char& c, std::string& str)
{
    if(token == HEX)
    {
        check_next_token(WHITESPACE, c, str);
        check_next_token(LESS_THAN, c, str);
        check_next_token(STRING, c, str);
        check_next_token(AT, c, str);
        token = get_token(c, str);
        printf("Got token: %s\n", str.c_str());
        if(token == AT)
        {
            token = get_token(c, str);
            printf("Got token: %s\n", str.c_str());
        }
        x_symbol(token, c, str);
    }
    else if(token == WHITESPACE)
    {
        check_next_token(HEX, c, str);
        check_next_token(COLON, c, str);
        check_next_token(WHITESPACE, c, str);
        check_next_token(HEX, c, str);
        check_next_token(WHITESPACE, c, str);
        instruction_symbol(c, str);
    }
    else
    {
        print_fatal("Syntax error: expected starting symbol, got: %s\n", str.c_str());
    }
    printf("Finished line, back to starting symbol\n");
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
    initialize_set((char*)"res/registers", &register_set);

    char c = fgetc(input_file);
    while((c != EOF))
    {
        std::string str;
        Type token = get_token(c, str);
        printf("Got token: %s\n", str.c_str());
        //if(token != WHITESPACE)
        //    print_log("'%s' is %s\n", str.c_str(), type_to_string(token));
        if(token == BAD_TOKEN)
            return -1;
        start_symbol(token, c, str);
    }
    print_log("End of file\n");
    print_log("Finished\n");
    return 0;
}