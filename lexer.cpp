#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <utility>

#include "automata.h"
#include "options.h"
#include "output.h"

enum Type
{
    ADDRESS = 1,
    INSTRUCTION,
    HEX_NUMBER,
    REGISTER,
    COMMENT,
    OFFSET,
    MEMORY_ACCESS,
    HEX_OR_INST,
    DECIMAL_OFFSET,
    HEX_OFFSET,
    LEFT_SQ_BRACKET,
    RIGHT_SQ_BRACKET,
    FUNC_NAME,
};

Options options;
Automata automata; //[0-9a-f]+:?

void init_instruction_set()
{
    FILE* file = fopen("res/arm-instruction-set", "r+");
    if(!file)
    {
        print_fatal("Couldn't open instruction-set file!\n");
    }
    print_log("Instruction set file opened\n");
    fclose(file);
}

void init_automata()
{
    int states_count = 23;
    std::map < char, int > states[states_count];
    
    states[0][':'] = 2;
    states[0]['.'] = 10;
    for(char c = '0'; c <= '9'; ++c)
        states[0][c] = 1;
    for(char c = 'a'; c <= 'f'; ++c)
        states[0][c] = 0;
    for(char c = 'g'; c <= 'z'; ++c)
        states[0][c] = 10;

    states[1][':'] = 2;
    for(char c = '0'; c <= '9'; ++c)
        states[1][c] = 1;
    for(char c = 'a'; c <= 'f'; ++c)
        states[1][c] = 1;

    states[3]['f'] = 4;
    states[3]['p'] = 7;
    states[3]['s'] = 6;
    states[3]['w'] = 5;
    states[3]['x'] = 5;
    states[3]['l'] = 11;

    states[4]['p'] = 9;
    states[4][':'] = 2;
    for(char c = '0'; c <= '9'; ++c)
        states[4][c] = 1;
    for(char c = 'a'; c <= 'f'; ++c)
        states[4][c] = 0;
    for(char c = 'g'; c <= 'o'; ++c)
        states[4][c] = 10;
    for(char c = 'q'; c <= 'z'; ++c)
        states[4][c] = 10;

    for(char c = '0'; c <= '9'; ++c)
        states[5][c] = 8;
    for(char c = 'a'; c <= 'z'; ++c)
        states[5][c] = 10;

    states[6]['p'] = 9;
    for(char c = 'a'; c <= 'o'; ++c)
        states[6][c] = 10;
    for(char c = 'q'; c <= 'z'; ++c)
        states[6][c] = 10;

    states[7]['a'] = 10;
    states[7]['b'] = 10;
    states[7]['c'] = 9;
    for(char c = 'd'; c <= 'z'; ++c)
        states[7][c] = 10;

    for(char c = '0'; c <= '9'; ++c)
        states[8][c] = 9;

    for(char c = 'a'; c <= 'z'; ++c)
        states[10][c] = 10;

    states[11]['r'] = 9;
    for(char c = 'a'; c <= 'q'; ++c)
        states[11][c] = 10;
    for(char c = 's'; c <= 'z'; ++c)
        states[11][c] = 10;

    states[12]['#'] = 13;
    
    states[13]['0'] = 14;
    for(char c = '1'; c <= '9'; ++c)
        states[13][c] = 15;

    states[14]['x'] = 16;
    for(char c = '0'; c <= '9'; ++c)
        states[14][c] = 15;

    for(char c = '0'; c <= '9'; ++c)
        states[15][c] = 15;

    for(char c = '0'; c <= '9'; ++c)
        states[16][c] = 17;
    for(char c = 'a'; c <= 'f'; ++c)
        states[16][c] = 17;

    for(char c = '0'; c <= '9'; ++c)
        states[17][c] = 17;
    for(char c = 'a'; c <= 'f'; ++c)
        states[17][c] = 17;

    states[18]['/'] = 19;
    states[19]['/'] = 20;

    states[21]['<'] = 22;
    states[22]['>'] = 23;
    for(char c = '0'; c <= '9'; ++c)
        states[22][c] = 22;
    for(char c = 'a'; c <= 'z'; ++c)
        states[22][c] = 22;

    int i;
    for(i = 0; i < states_count; ++i)
    {
        automata.push(states[i]);
    }
    automata.add_start_state(3);
    automata.add_start_state(0);
    automata.add_start_state(12);
    automata.add_start_state(18);
    automata.add_start_state(21);
    automata.add_accept(std::make_pair(0, HEX_OR_INST));
    automata.add_accept(std::make_pair(1, HEX_NUMBER));
    automata.add_accept(std::make_pair(2, ADDRESS));
    automata.add_accept(std::make_pair(4, HEX_NUMBER));
    automata.add_accept(std::make_pair(8, REGISTER));
    automata.add_accept(std::make_pair(9, REGISTER));
    automata.add_accept(std::make_pair(10, INSTRUCTION));
    automata.add_accept(std::make_pair(15, DECIMAL_OFFSET));
    automata.add_accept(std::make_pair(17, HEX_OFFSET));
    automata.add_accept(std::make_pair(20, COMMENT));
    automata.add_accept(std::make_pair(22, FUNC_NAME));
}

void init_register_automata()
{
    std::map < char, int > state0, state1;
}

void printUsage()
{
    printf("Usage: lexer [FILE]");
    printf("\nRun lexer on provided FILE");
    printf("\n");
}

char* type_to_str(int a)
{
    switch(a)
    {
        case ADDRESS:
            return (char*)"address of instruction";
        case HEX_NUMBER:
            return (char*)"hex number";
        case REGISTER:
            return (char*)"register";
        case COMMENT:
            return (char*)"coment";
        case OFFSET:
            return (char*)"offset";
        case MEMORY_ACCESS:
            return (char*)"memory access";
        case HEX_OR_INST:
            return (char*)"hex or instruction";
        case INSTRUCTION:
            return (char*)"instruction";
        case DECIMAL_OFFSET:
            return (char*)"decimal offset";
        case HEX_OFFSET:
            return (char*)"hex offset";
        case LEFT_SQ_BRACKET:
            return (char*)"left square bracket";
        case RIGHT_SQ_BRACKET:
            return (char*)"right square bracket";
        default:
            print_fatal("Type unknown\n");
    }
    return (char*)"bad type";
}

void process_line(char* line)
{
    int len = strlen(line);
    int it = 0;
    int buf_idx = 0;
    char buf[len];
    while(it < len && (line[it] == ' ' || line[it] == '\t' || line[it] == '\n')) it++;
    while(it < len)
    {
        if(line[it] == ' ' || line[it] == '\n' || line[it] == '\t' || line[it] == ',' || line[it] == ']')
        {
            if(automata.is_started())
            {
                buf[buf_idx] = '\0';
                int status = automata.get_accept();
                if(status == COMMENT)
                {
                    print_log("Comment found: %s", &line[it]);
                    automata.reset();
                    return;
                }
                else if(status != -1)
                {
                    print_log("Token accepted: %s is %s\n", buf, type_to_str(status));
                }
                else
                {
                    print_error("Token rejected %s\n", buf);
                }
                buf_idx = 0;
                automata.reset();
            }//else is empty string
            if(line[it] == ']')
            {
                print_log("Token accepted: ] is %s\n", type_to_str(RIGHT_SQ_BRACKET));
            }
        }
        else if(line[it] == '[' && !automata.is_started())
        {
            print_log("Token accepted: [ is %s\n", type_to_str(LEFT_SQ_BRACKET));
        }
        else if(automata.next_state(line[it]) == -1)
        {
            print_fatal("Wrong character \'%c\' in line: %s", line[it], line);
        }
        else
        {
            buf[buf_idx++] = line[it];
        }

        it++;
    }
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
    init_instruction_set();
    FILE* input_file = fopen(filepath, "r");
    if(input_file == NULL)
    {
        print_fatal("Error while reading file: %s\n", filepath);
    }
    print_log("File \"%s\" opened\n", filepath);
    init_automata();

    char* line = NULL;
    size_t line_len = 0;
    while(getline(&line, &line_len, input_file) != -1)
    {
        process_line(line);
        line = NULL;
        line_len = 0;
    }
    print_log("End of file\n");
    print_log("Finished\n");
    return 0;
}