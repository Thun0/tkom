#include <cstdio>
#include <cstdarg>
#include <cstdlib>
#include <cstring>
#include <map>
#include <utility>

#include "automata.h"
#include "options.h"

enum Type
{
    ADDRESS = 1,
    OPCODE,
    HEX_NUMBER,
    REGISTER,
    COMMENT,
    OFFSET,
    MEMORY_ACCESS
};

Options options;
Automata automata; //[0-9a-f]+:?

void init_automata()
{
    std::map < char, int > state0, state1;
    state0['0'] = 0;
    state0['1'] = 0;
    state0['2'] = 0;
    state0['3'] = 0;
    state0['4'] = 0;
    state0['5'] = 0;
    state0['6'] = 0;
    state0['7'] = 0;
    state0['8'] = 0;
    state0['9'] = 0;
    state0['a'] = 0;
    state0['b'] = 0;
    state0['c'] = 0;
    state0['d'] = 0;
    state0['e'] = 0;
    state0['f'] = 0;
    state0[':'] = 1;
    automata.push(state0);
    automata.push(state1);
    automata.add_start_state(0);
    automata.add_accept(std::make_pair(0, HEX_NUMBER));
    automata.add_accept(std::make_pair(1, ADDRESS));
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

void print_log(const char* fmt, ...)
{
    if(options.verbose)
    {
        printf("Log: ");
        va_list argp;
        va_start(argp, fmt);
        vfprintf(stdout, fmt, argp);
        va_end(argp);
    }
}

void print_fatal(const char* fmt, ...)
{
    va_list argp;
    printf("Fatal: ");
    va_start(argp, fmt);
    vfprintf(stdout, fmt, argp);
    va_end(argp);
    printf("Terminated\n");
    exit(-1);
}

void print_error(const char* fmt, ...)
{
    va_list argp;
    printf("Error: ");
    va_start(argp, fmt);
    vfprintf(stdout, fmt, argp);
    va_end(argp);
}

char* type_to_str(int a)
{
    switch(a)
    {
        case ADDRESS:
            return (char*)"address";
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
        if(line[it] == ' ' || line[it] == '\n' || line[it] == '\t')
        {
            buf[buf_idx] = '\0';
            int status = automata.get_accept();
            if(status != -1)
            {
                print_log("Token accepted: %s is %s\n", buf, type_to_str(status));
            }
            else
            {
                print_error("Token rejected %s\n", buf);
            }
            buf_idx = 0;
            automata.reset();
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
    //print_log("Line processed\n");
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
        //print_log("Read nextline, len: %d\n", strlen(line));
        process_line(line);

        line = NULL;
        line_len = 0;
    }
    print_log("End of file\n");
    print_log("Finished\n");
    return 0;
}