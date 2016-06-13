#include <cstdio>

#include "parser.h"
#include "options.h"

Options options;

void printUsage()
{
    printf("Usage: lexer [FILE]");
    printf("\nRun lexer on provided FILE");
    printf("\n");
}

int main(int argc, char** argv)
{
    std::vector<Instruction> instructions;
    if(argc < 2)
    {
        printUsage();
        return 0;
    }
    options.verbose = true;
    char* filepath = argv[1];    
    Parser parser(filepath);
    parser.parse(instructions);   
    return 0;
}