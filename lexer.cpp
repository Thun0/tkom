#include <cstdio>
#include <cstdarg>
#include <cstdlib>
#include <cstring>
#include <map>

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
    MEMORY_ACCESS,
    ERROR
};

Options options;
Automata address_automata;

void init_address_automata()
{
    std::map < char, int > state0;
    std::map < char, int > state1;
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
    address_automata.push(state0);
    address_automata.push(state1);
    address_automata.add_accept(1);
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

void process_line(char* line)
{
    int len = strlen(line);
    int it = 0;
    int buf_idx = 0;
    char buf[len];
    while(it < len && (line[it] == ' ' || line[it] == '\t')) it++;
    while(it < len)
    {
        if(line[it] == ' ' || line[it] == '\n')
        {
            buf[buf_idx] = '\0';
            if(address_automata.is_accepted())
            {
                print_log("Token accepted: %s\n", buf);
            }
            else
            {
                print_error("Token rejected %s\n", buf);
            }
            buf_idx = 0;
            address_automata.reset();
        }
        else if(address_automata.next_state(line[it]) == -1)
        {
            print_fatal("Wrong character \'%c\' in line: %s", line[it], line);
        }
        else
        {
            buf[buf_idx++] = line[it];
        }

        it++;
    }
    print_log("Line processed\n");
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
    init_address_automata();

    char* line = NULL;
    size_t line_len = 0;
    while(getline(&line, &line_len, input_file) != -1)
    {
        print_log("Read nextline, len: %d\n", strlen(line));
        process_line(line);

        line = NULL;
        line_len = 0;
    }
    print_log("End of file\n");
    print_log("Finished\n");
    return 0;
}