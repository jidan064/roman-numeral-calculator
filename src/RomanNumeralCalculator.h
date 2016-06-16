#ifndef _ROMAN_NUMERAL_CALCULATOR_H_
#define _ROMAN_NUMERAL_CALCULATOR_H_
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    unsigned int possible_value;
    const char*  roman_symbol;
} NumeralElement;

void add(char* output, const char* a, const char* b);
void sub(char* output, const char* a, const char* b);
#endif
