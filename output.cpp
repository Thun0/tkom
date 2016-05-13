#include <cstdio>
#include <cstdarg>
#include <cstdlib>

#include "options.h"
#include "output.h"

extern Options options;

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
