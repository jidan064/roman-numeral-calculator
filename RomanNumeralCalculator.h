#ifndef _ROMAN_NUMERAL_CALCULATOR_H_
#define _ROMAN_NUMERAL_CALCULATOR_H_
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXROMANLETTER  100
typedef struct
{
    unsigned int possible_value;
    const char*  roman_symbol;
} NumeralElement;

char* add(char* a, char* b);
char* sub(char* a, char* b);
#endif
