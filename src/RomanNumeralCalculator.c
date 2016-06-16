#include "RomanNumeralCalculator.h"
// Define all possible values
const NumeralElement NumeralLookUpTable[] = {
    {1000, "M"},
    {900, "DM"},
    {500, "D"},
    {400, "CD"},
    {100, "C"},
    {90, "XC"},
    {50, "L"},
    {40, "XL"},
    {10, "X"},
    {9, "IX"},
    {5, "V"},
    {4, "IV"},
    {1, "I"}
};

// Convert Roman Numerial to integer for calculation
unsigned int digit(char i)
{
    switch (i)
    {
    case 'I':   return 1;
    case 'V':   return 5;
    case 'X':   return 10;
    case 'L':   return 50;
    case 'C':   return 100;
    case 'D':   return 500;
    case 'M':   return 1000;
    default:    return 0;
    }
}
// Convert Roman to integer
long long convert_to_digit(const char roman[])
{
    long long numeral_value = 0;
    char previous_roman = '$';
    unsigned int roman_length = strlen(roman);
    int i;
    for (i = roman_length - 1; i >= 0; i--)
    {
        // If a lesser numeral is put before a bigger it means subtraction of the lesser from the bigger.
        if (digit(roman[i]) < digit(previous_roman))
        {
            numeral_value -= digit(roman[i]);
            previous_roman = roman[i];
        }
        else
        {
            numeral_value += digit(roman[i]);
            previous_roman = roman[i];
        }
    }
    return numeral_value;
}

// Convert integer to Roman
void convert_to_roman(char* roman, long long numeral_value)
{
    // Loop through all possible supported values. Start with the MAX possible value. And if remainer is greater than current 
    // supported value, keep subtracting until remainer is smaller than current value. Move on to next one.
    int i;
    for (i = 0; (numeral_value > 0) && i < (sizeof(NumeralLookUpTable) / sizeof(NumeralLookUpTable[0])); i++)
    {
        while (numeral_value >= NumeralLookUpTable[i].possible_value)
        {
            numeral_value -= NumeralLookUpTable[i].possible_value;
            strcat(roman, NumeralLookUpTable[i].roman_symbol);
        }
    }
}

void add(char* output, const char* a, const char* b)
{
    strcpy(output, "");
    long long result = convert_to_digit(a) + convert_to_digit(b);
    convert_to_roman(output, result);
}

void sub(char* output, const char* a, const char* b)
{
    strcpy(output, "");
    long long result = convert_to_digit(a) - convert_to_digit(b);
    // When result is less or equal to zero, Roman numeral doesnt exist...
    if (result >0)
        convert_to_roman(output, result);
    printf("here %s\n", output);
}
