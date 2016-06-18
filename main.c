#include "RomanNumeral.h"
typedef struct
{
    unsigned int possible_value;
    const char*  roman_symbol;
} NumeralElement;

// Define all possible values
const NumeralElement LookUpTable[] = {
    {1000, "M"},
    {900, "CM"},
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

// Convert integer to Roman
void convert_to_roman(char* roman, unsigned int numeral_value)
{
    strcpy(roman, "");
    // Loop through all possible supported values. Start with the MAX possible value. And if remainer is greater than current 
    // supported value, keep subtracting until remainer is smaller than current value. Move on to next one.
    int i;
    for (i = 0; (numeral_value > 0) && i < (sizeof(LookUpTable) / sizeof(LookUpTable[0])); i++)
    {
        while (numeral_value >= LookUpTable[i].possible_value)
        {
            numeral_value -= LookUpTable[i].possible_value;

            strcat(roman, LookUpTable[i].roman_symbol);
        }
    }
}


int main(void)
{
    char output[100] = "";
    char buff[256];
    FILE* fp = fopen("testcase.txt", "r");
    char a[100], b[100], sum[100];
    char* token;
    while (fgets(buff, 255, fp) != NULL)
    {
        token = strtok(buff, " \n");
        strcpy(a, token);
        token = strtok(NULL, " \n");
        strcpy(b, token);
        token = strtok(NULL, " \n");
        strcpy(sum, token);
        add(a, b);

        if (strcmp(add(a,b),sum))
            printf("%s %s %s %s\n", a, b, add(a,b), sum);
        if (strcmp(add(b,a),sum))
            printf("%s %s %s %s\n", b, a, add(b,a), sum);
        if (strcmp(sub(sum,b),a))
            printf("%s %s %s %s\n", sum, b, sub(sum,b), a);
        if (strcmp(sub(sum,a),b))
            printf("%s %s %s %s\n", sum, a, sub(sum,a), b);
    }

    int i, j;
    for (i=1; i < 2000; i++)
        for (j=i; j < 2000; j++)
        {
            convert_to_roman(a, i);
            convert_to_roman(b, j);
            convert_to_roman(sum, i+j);
            if (strcmp(add(a,b),sum))
                printf("%s %s %s %s\n", a, b, add(a,b), sum);
            if (strcmp(add(b,a),sum))
                printf("%s %s %s %s\n", b, a, add(b,a), sum);
            if (strcmp(sub(sum,b),a))
                printf("%s %s %s %s\n", sum, b, sub(sum,b), a);
            if (strcmp(sub(sum,a),b))
                printf("%s %s %s %s\n", sum, a, sub(sum,a), b);

        }
    printf("Finished\n");
    return 0;
}
