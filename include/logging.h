#pragma once
#include<stdio.h>
#include<stdarg.h>

#define ANSI_CODE_RESET      "\033[00m"
#define ANSI_CODE_ERROR      "\033[31m"
#define ANSI_CODE_INFO       "\033[36m"
#define ANSI_CODE_SUCCESS    "\033[32m"
#define ANSI_CODE_WARNING    "\033[35m"

void print_error(char *format, ...) {
    printf(ANSI_CODE_ERROR);
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    printf(ANSI_CODE_RESET);
}

void print_success(char *format, ...) {
    printf(ANSI_CODE_SUCCESS);
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    printf(ANSI_CODE_RESET);
}

void print_info(char *format, ...) {
    printf(ANSI_CODE_INFO);
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    printf(ANSI_CODE_RESET);
}

void print_warning(char *format, ...) {
    printf(ANSI_CODE_WARNING);
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    printf(ANSI_CODE_RESET);
}
