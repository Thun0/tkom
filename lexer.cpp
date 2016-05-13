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
    RIGHT_SQ_BRACKET
};

Options options;
Automata automata; //[0-9a-f]+:?

void init_automata()
{
    int states_count = 21;
    std::map < char, int > states[states_count];
    states[0]['0'] = 1;
    states[0]['1'] = 1;
    states[0]['2'] = 1;
    states[0]['3'] = 1;
    states[0]['4'] = 1;
    states[0]['5'] = 1;
    states[0]['6'] = 1;
    states[0]['7'] = 1;
    states[0]['8'] = 1;
    states[0]['9'] = 1;
    states[0]['a'] = 0;
    states[0]['b'] = 0;
    states[0]['c'] = 0;
    states[0]['d'] = 0;
    states[0]['e'] = 0;
    states[0]['f'] = 0;
    states[0]['g'] = 10;
    states[0]['h'] = 10;
    states[0]['i'] = 10;
    states[0]['j'] = 10;
    states[0]['k'] = 10;
    states[0]['l'] = 10;
    states[0]['m'] = 10;
    states[0]['n'] = 10;
    states[0]['o'] = 10;
    states[0]['p'] = 10;
    states[0]['q'] = 10;
    states[0]['r'] = 10;
    states[0]['s'] = 10;
    states[0]['t'] = 10;
    states[0]['u'] = 10;
    states[0]['v'] = 10;
    states[0]['w'] = 10;
    states[0]['x'] = 10;
    states[0]['y'] = 10;
    states[0]['z'] = 10;
    states[0]['.'] = 10;
    states[0][':'] = 2;

    states[1]['0'] = 1;
    states[1]['1'] = 1;
    states[1]['2'] = 1;
    states[1]['3'] = 1;
    states[1]['4'] = 1;
    states[1]['5'] = 1;
    states[1]['6'] = 1;
    states[1]['7'] = 1;
    states[1]['8'] = 1;
    states[1]['9'] = 1;
    states[1]['a'] = 1;
    states[1]['b'] = 1;
    states[1]['c'] = 1;
    states[1]['d'] = 1;
    states[1]['e'] = 1;
    states[1]['f'] = 1;
    states[1][':'] = 2;

    states[3]['f'] = 4;
    states[3]['p'] = 7;
    states[3]['s'] = 6;
    states[3]['w'] = 5;
    states[3]['x'] = 5;
    states[3]['l'] = 11;

    states[4]['0'] = 1;
    states[4]['1'] = 1;
    states[4]['2'] = 1;
    states[4]['3'] = 1;
    states[4]['4'] = 1;
    states[4]['5'] = 1;
    states[4]['6'] = 1;
    states[4]['7'] = 1;
    states[4]['8'] = 1;
    states[4]['9'] = 1;
    states[4]['a'] = 0;
    states[4]['b'] = 0;
    states[4]['c'] = 0;
    states[4]['d'] = 0;
    states[4]['e'] = 0;
    states[4]['f'] = 0;
    states[4]['g'] = 10;
    states[4]['h'] = 10;
    states[4]['i'] = 10;
    states[4]['j'] = 10;
    states[4]['k'] = 10;
    states[4]['l'] = 10;
    states[4]['m'] = 10;
    states[4]['n'] = 10;
    states[4]['o'] = 10;
    states[4]['p'] = 9;
    states[4]['q'] = 10;
    states[4]['r'] = 10;
    states[4]['s'] = 10;
    states[4]['t'] = 10;
    states[4]['u'] = 10;
    states[4]['v'] = 10;
    states[4]['w'] = 10;
    states[4]['x'] = 10;
    states[4]['y'] = 10;
    states[4]['z'] = 10;
    states[4][':'] = 2;

    states[5]['0'] = 8;
    states[5]['1'] = 8;
    states[5]['2'] = 8;
    states[5]['3'] = 8;
    states[5]['4'] = 8;
    states[5]['5'] = 8;
    states[5]['6'] = 8;
    states[5]['7'] = 8;
    states[5]['8'] = 8;
    states[5]['9'] = 8;
    states[5]['a'] = 10;
    states[5]['b'] = 10;
    states[5]['c'] = 10;
    states[5]['d'] = 10;
    states[5]['e'] = 10;
    states[5]['f'] = 10;
    states[5]['g'] = 10;
    states[5]['h'] = 10;
    states[5]['i'] = 10;
    states[5]['j'] = 10;
    states[5]['k'] = 10;
    states[5]['l'] = 10;
    states[5]['m'] = 10;
    states[5]['n'] = 10;
    states[5]['o'] = 10;
    states[5]['p'] = 10;
    states[5]['q'] = 10;
    states[5]['r'] = 10;
    states[5]['s'] = 10;
    states[5]['t'] = 10;
    states[5]['u'] = 10;
    states[5]['v'] = 10;
    states[5]['w'] = 10;
    states[5]['x'] = 10;
    states[5]['y'] = 10;
    states[5]['z'] = 10;

    states[6]['a'] = 10;
    states[6]['b'] = 10;
    states[6]['c'] = 10;
    states[6]['d'] = 10;
    states[6]['e'] = 10;
    states[6]['f'] = 10;
    states[6]['g'] = 10;
    states[6]['h'] = 10;
    states[6]['i'] = 10;
    states[6]['j'] = 10;
    states[6]['k'] = 10;
    states[6]['l'] = 10;
    states[6]['m'] = 10;
    states[6]['n'] = 10;
    states[6]['o'] = 10;
    states[6]['p'] = 9;
    states[6]['q'] = 10;
    states[6]['r'] = 10;
    states[6]['s'] = 10;
    states[6]['t'] = 10;
    states[6]['u'] = 10;
    states[6]['v'] = 10;
    states[6]['w'] = 10;
    states[6]['x'] = 10;
    states[6]['y'] = 10;
    states[6]['z'] = 10;

    states[7]['a'] = 10;
    states[7]['b'] = 10;
    states[7]['c'] = 9;
    states[7]['d'] = 10;
    states[7]['e'] = 10;
    states[7]['f'] = 10;
    states[7]['g'] = 10;
    states[7]['h'] = 10;
    states[7]['i'] = 10;
    states[7]['j'] = 10;
    states[7]['k'] = 10;
    states[7]['l'] = 10;
    states[7]['m'] = 10;
    states[7]['n'] = 10;
    states[7]['o'] = 10;
    states[7]['p'] = 10;
    states[7]['q'] = 10;
    states[7]['r'] = 10;
    states[7]['s'] = 10;
    states[7]['t'] = 10;
    states[7]['u'] = 10;
    states[7]['v'] = 10;
    states[7]['w'] = 10;
    states[7]['x'] = 10;
    states[7]['y'] = 10;
    states[7]['z'] = 10;

    states[8]['0'] = 9;
    states[8]['1'] = 9;
    states[8]['2'] = 9;
    states[8]['3'] = 9;
    states[8]['4'] = 9;
    states[8]['5'] = 9;
    states[8]['6'] = 9;
    states[8]['7'] = 9;
    states[8]['8'] = 9;
    states[8]['9'] = 9;

    states[10]['a'] = 10;
    states[10]['b'] = 10;
    states[10]['c'] = 10;
    states[10]['d'] = 10;
    states[10]['e'] = 10;
    states[10]['f'] = 10;
    states[10]['g'] = 10;
    states[10]['h'] = 10;
    states[10]['i'] = 10;
    states[10]['j'] = 10;
    states[10]['k'] = 10;
    states[10]['l'] = 10;
    states[10]['m'] = 10;
    states[10]['n'] = 10;
    states[10]['o'] = 10;
    states[10]['p'] = 10;
    states[10]['q'] = 10;
    states[10]['r'] = 10;
    states[10]['s'] = 10;
    states[10]['t'] = 10;
    states[10]['u'] = 10;
    states[10]['v'] = 10;
    states[10]['w'] = 10;
    states[10]['x'] = 10;
    states[10]['y'] = 10;
    states[10]['z'] = 10;

    states[11]['a'] = 10;
    states[11]['b'] = 10;
    states[11]['c'] = 10;
    states[11]['d'] = 10;
    states[11]['e'] = 10;
    states[11]['f'] = 10;
    states[11]['g'] = 10;
    states[11]['h'] = 10;
    states[11]['i'] = 10;
    states[11]['j'] = 10;
    states[11]['k'] = 10;
    states[11]['l'] = 10;
    states[11]['m'] = 10;
    states[11]['n'] = 10;
    states[11]['o'] = 10;
    states[11]['p'] = 10;
    states[11]['q'] = 10;
    states[11]['r'] = 9;
    states[11]['s'] = 10;
    states[11]['t'] = 10;
    states[11]['u'] = 10;
    states[11]['v'] = 10;
    states[11]['w'] = 10;
    states[11]['x'] = 10;
    states[11]['y'] = 10;
    states[11]['z'] = 10;

    states[12]['#'] = 13;

    states[13]['0'] = 14;
    states[13]['1'] = 15;
    states[13]['2'] = 15;
    states[13]['3'] = 15;
    states[13]['4'] = 15;
    states[13]['5'] = 15;
    states[13]['6'] = 15;
    states[13]['7'] = 15;
    states[13]['8'] = 15;
    states[13]['9'] = 15;

    states[14]['x'] = 16;
    states[14]['0'] = 15;
    states[14]['1'] = 15;
    states[14]['2'] = 15;
    states[14]['3'] = 15;
    states[14]['4'] = 15;
    states[14]['5'] = 15;
    states[14]['6'] = 15;
    states[14]['7'] = 15;
    states[14]['8'] = 15;
    states[14]['9'] = 15;

    states[15]['0'] = 15;
    states[15]['1'] = 15;
    states[15]['2'] = 15;
    states[15]['3'] = 15;
    states[15]['4'] = 15;
    states[15]['5'] = 15;
    states[15]['6'] = 15;
    states[15]['7'] = 15;
    states[15]['8'] = 15;
    states[15]['9'] = 15;

    states[16]['0'] = 17;
    states[16]['1'] = 17;
    states[16]['2'] = 17;
    states[16]['3'] = 17;
    states[16]['4'] = 17;
    states[16]['5'] = 17;
    states[16]['6'] = 17;
    states[16]['7'] = 17;
    states[16]['8'] = 17;
    states[16]['9'] = 17;
    states[16]['a'] = 17;
    states[16]['b'] = 17;
    states[16]['c'] = 17;
    states[16]['d'] = 17;
    states[16]['e'] = 17;
    states[16]['f'] = 17;

    states[17]['0'] = 17;
    states[17]['1'] = 17;
    states[17]['2'] = 17;
    states[17]['3'] = 17;
    states[17]['4'] = 17;
    states[17]['5'] = 17;
    states[17]['6'] = 17;
    states[17]['7'] = 17;
    states[17]['8'] = 17;
    states[17]['9'] = 17;
    states[17]['a'] = 17;
    states[17]['b'] = 17;
    states[17]['c'] = 17;
    states[17]['d'] = 17;
    states[17]['e'] = 17;
    states[17]['f'] = 17;

    states[18]['/'] = 19;
    states[19]['/'] = 20;

    int i;
    for(i = 0; i < states_count; ++i)
    {
        automata.push(states[i]);
    }
    automata.add_start_state(3);
    automata.add_start_state(0);
    automata.add_start_state(12);
    automata.add_start_state(18);
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