#include "RomanNumeral.h"
typedef struct
{
    const char*  roman_symbol;
    const char*  roman_replace;
} NumeralElement;

// Define all possible subtractives
const NumeralElement NumeralLookUpTable[] = {
    {"CM", "DCCCC"},
    {"CD", "CCCC"},
    {"XC", "LXXXX"},
    {"XL", "XXXX"},
    {"IX", "VIIII"},
    {"IV", "IIII"},
 };

const NumeralElement NumeralGroupTable[] = {
    {"IIIII", "V"},
    {"VV", "X"},
    {"XXXXX","L"},
    {"LL", "C"},
    {"CCCCC", "D"},
    {"DD", "M"}
};

// Replace all substr in a given string with replacement 
char* str_replace ( const char *string, const char *substr, const char *replacement ){
  char *tok = NULL;
  char *newstr = NULL;
  char *oldstr = NULL;
  newstr = strdup (string);
  while (tok = strstr(newstr,substr)){
    oldstr = newstr;
    newstr = malloc (strlen(oldstr) - strlen(substr) + strlen(replacement) + 1);
    if (newstr == NULL){
      free(oldstr);
      return NULL;
    }
    memcpy(newstr, oldstr,tok - oldstr );
    memcpy(newstr + (tok - oldstr),replacement,strlen(replacement));
    memcpy(newstr + (tok - oldstr) + strlen(replacement), tok + strlen(substr), strlen(oldstr) - strlen(substr) - (tok - oldstr));
    memset (newstr + strlen(oldstr) - strlen(substr) + strlen(replacement), 0, 1);
    free (oldstr);
  }
  return newstr;
}

// This serves as a map funciton. key is array idx which ranges from 0-6, and return value is Roman symbol.
char roman_symbol(unsigned int i)
{
    switch(i){
    case 0: return 'M';
    case 1: return 'D';
    case 2: return 'C';
    case 3: return 'L';
    case 4: return 'X';
    case 5: return 'V';
    case 6: return 'I';
    }
}

// Count total Roman Numeral Count given a string
void symbol_count(int* count, char* str)
{
    unsigned int idx = 0;
    while(str[idx] != '\0')
    {   
        switch(str[idx])
        {
        case 'M': count[0]++; break;
        case 'D': count[1]++; break;
        case 'C': count[2]++; break;
        case 'L': count[3]++; break;
        case 'X': count[4]++; break;
        case 'V': count[5]++; break;
        case 'I': count[6]++; break;
        default: break;
        }
        idx++;
    }
}

// This function generates number of Numerals roll down from a bigger symbol to smaller one.
void update_count(int* count, unsigned int idx)
{
    count[idx]--;
    if (idx == 5 || idx == 3 || idx == 1) //V, L, D
    {
        count[idx+1] += 5;
    }
    else if (idx == 4 || idx == 2 || idx == 0) // X, C, M
    {
        count[idx+1] += 2;
    }
}

// If a partitular Roman numeral group exceeds next big numeral, update the array here.
void group(int* count, unsigned int idx)
{
    if (idx == 6 || idx == 4 || idx == 2) // need 5 to group
    {
        count[idx-1] += (count[idx] / 5);
        count[idx] = count[idx] % 5;
    }
    else // need 2 to group
    {
        count[idx-1] += (count[idx] / 2);
        count[idx] = count[idx] % 2;
    }
}

// output = a + b 
void add(char* output, char* a, char* b)
{
    // reset output to empty string
    strcpy(output, "");
    int i;
    char* temp_a = malloc(strlen(a) + 1);
    char* temp_b = malloc(strlen(b) + 1);
    strcpy(temp_a, a);
    strcpy(temp_b, b);
    // Substitute for any subtractives
    // For calculation, we replace all subtractives with original Numeral.
    // For instance, IV would be replaced with IIII
    for (i = 0; i < (sizeof(NumeralLookUpTable) / sizeof(NumeralLookUpTable[0])); ++i)
    {
        char* newStr_a = str_replace(temp_a, NumeralLookUpTable[i].roman_symbol, NumeralLookUpTable[i].roman_replace);
        temp_a = newStr_a;  
        char* newStr_b = str_replace(temp_b, NumeralLookUpTable[i].roman_symbol, NumeralLookUpTable[i].roman_replace);
        temp_b = newStr_b;  
    }
    // Calculate total number of Numeral letters in input string including a and b
    int count[7] = {0,0,0,0,0,0,0}; // M, D, C, L, X, V, I
    symbol_count(count, temp_a);
    symbol_count(count, temp_b);
    //Group each bucket together and advance to next big Numeral bucket if possible
    unsigned int total_size = 0;
    for (i = 6; i > 0; --i)
    {   
        group(count, i);
        total_size += count[i];
    }
    // Construct output 
    char* raw_output = malloc(total_size + 1);
    int total = 0;
    for (i = 0; i < 7; ++i)
    {
        while(count[i] > 0)
        {
            raw_output[total] = roman_symbol(i);
            total++;
            count[i]--;
        }  
    }
    raw_output[total] = '\0'; 
    // substitue any subtractive to produce final output
    char* temp_output = raw_output;
    for (i = 0; i < (sizeof(NumeralLookUpTable) / sizeof(NumeralLookUpTable[0])); ++i)
    {
        char* newStr = str_replace(temp_output, NumeralLookUpTable[i].roman_replace, NumeralLookUpTable[i].roman_symbol);
        temp_output = newStr;  
    }
    strcpy(output, temp_output);
    free(temp_output);
}


void sub(char* output, char* a, char* b)
{
    // reset output string to empty
    strcpy(output, "");
    int i, j, k;
    char* temp_a = malloc(strlen(a) + 1);
    char* temp_b = malloc(strlen(b) + 1);
    strcpy(temp_a, a);
    strcpy(temp_b, b);
    // Substitute for any subtractives for future calculation
    for (i = 0; i < (sizeof(NumeralLookUpTable) / sizeof(NumeralLookUpTable[0])); ++i)
    {
        char* newStr_a = str_replace(temp_a, NumeralLookUpTable[i].roman_symbol, NumeralLookUpTable[i].roman_replace);
        temp_a = newStr_a;  
        char* newStr_b = str_replace(temp_b, NumeralLookUpTable[i].roman_symbol, NumeralLookUpTable[i].roman_replace);
        temp_b = newStr_b;  
    }
    // Calculate number of Numeral symbols in both of the string.
    int count_a[7] = {0,0,0,0,0,0,0}; // M, D, C, L, X, V, I
    int count_b[7] = {0,0,0,0,0,0,0}; // M, D, C, L, X, V, I
    symbol_count(count_a, temp_a);
    symbol_count(count_b, temp_b);
    // Subtract a buckets with b.
    // Calcualted value might be negative. Our goal here is to make them positive or 0!!
    for(i = 0; i < 7; ++i)
    {
        count_a[i] -= count_b[i];
    }

    // done here indicates whether all negative values are resolved.
    bool done = false;
    while(done == false)
    {
        // I -> M direction
        for(i = 6; i >= 1; --i)
        {
            if (count_a[i] < 0)
            {
                // If current count is negative, seach through bucket that has bigger Numeral
                for(j = i - 1; j >= 0; --j)
                {
                    // If bigger bucket has positive value, break it down to its next smaller bucket
                    if (count_a[j] > 0)
                    {
                        update_count(count_a, j);
                        break;
                    }
                } 
            }
        }
        // Calculate if done
        done = true;
        for(i = 0; i < 7; ++i)
        {
            if (count_a[i] < 0)
            {
                done = false;
                break;
            }
        }
    }
    //Group. Ideally if above logic is done correctly, we should only have minimal buckets to group.
    unsigned int total_size = 0;
    for (i = 6; i > 0; --i)
    {   
        group(count_a, i);
        total_size += count_a[i];
    }
    // Construct output 
    int total = 0;
    char* raw_output = malloc ( total_size + 1 );
    for (i = 0; i < 7; ++i)
    {
        while(count_a[i] > 0)
        {
            raw_output[total] = roman_symbol(i);
            total++;
            count_a[i]--;
        }  
    } 
    raw_output[total] = '\0'; 
    // substitue any subtractive
    char* temp_output = raw_output;
    for (i = 0; i < (sizeof(NumeralLookUpTable) / sizeof(NumeralLookUpTable[0])); ++i)
    {
        char* newStr = str_replace(temp_output, NumeralLookUpTable[i].roman_replace, NumeralLookUpTable[i].roman_symbol);
        temp_output = newStr;  
    }
    strcpy(output, temp_output);
    free(temp_output);
}
