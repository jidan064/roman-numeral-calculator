/*************************************************************************
 * Description: Implementation of Roman Numeral ADD/SUB functions
*************************************************************************/
#include "RomanNumeralCalculator.h"
#include "assert.h"
// Define bool since compiler doesnt support it
typedef enum { false, true } bool;

// Replace oldstr location tok substr with replacement
char* replace_single_occurance(char* oldstr, char* tok, const char* substr, const char* replacement)
{
    char* newstr = malloc(strlen(oldstr) - strlen(substr) + strlen(replacement) + 1);
    if (newstr == NULL){
        free(oldstr);
        return NULL;
    }
    memcpy(newstr, oldstr, tok - oldstr);
    memcpy(newstr + (tok - oldstr), replacement, strlen(replacement));
    memcpy(newstr + (tok - oldstr) + strlen(replacement), tok + strlen(substr), strlen(oldstr) - strlen(substr) - (tok - oldstr));
    memset(newstr + strlen(oldstr) - strlen(substr) + strlen(replacement), 0, 1);
    free(oldstr);
    return newstr;
}

// Replace all substr in a given string with replacement
char* str_replace(const char *string, const char *substr, const char *replacement){
    char *tok = NULL;
    char *newstr = NULL;
    char *oldstr = NULL;
    newstr = strdup(string);
    while (tok = strstr(newstr, substr)){
        oldstr = newstr;
        newstr = replace_single_occurance(oldstr, tok, substr, replacement);
    }
    return newstr;
}

// Return true if a is greater than b in roman numeral
bool compare_roman_letter(char a, char b)
{
    switch(b)
    {
        case 'M':   return false;
        case 'D':
                    if (a == 'M')
                        return true;
                    else
                        return false;
        case 'C':
                    if (a == 'M' || a == 'D')
                        return true;
                    else
                        return false;
        case 'L':
                    if (a == 'M' || a == 'D' || a == 'C')
                        return true;
                    else
                        return false;
        case 'X':
                    if (a == 'M' || a == 'D' || a == 'C' || a == 'L')
                        return true;
                    else
                        return false;
        case 'V':
                    if (a == 'M' || a == 'D' || a == 'C' || a == 'L' || a == 'X')
                        return true;
                    else
                        return false;
        case 'I':
                    if (a == 'M' || a == 'D' || a == 'C' || a == 'L' || a == 'X' || a == 'V')
                        return true;
                    else
                        return false;
        case '\0':  return true;
    }
    return false;
}

char* convert_char_to_str(char ch)
{
    switch(ch)
    {
        case 'M':   return "M";
        case 'D':   return "D";
        case 'C':   return "C";
        case 'L':   return "L";
        case 'X':   return "X";
        case 'V':   return "V";
        case 'I':   return "I";
    }
}

// Sort roman string to M->I order
// Due to nature of Roman numeral, this sort is easier since order within a string 
// is already guaranteed
char* concatenate_and_sort_string(char* str1, char* str2)
{
    char* temp_str1 = str1;
    char* temp_str2 = str2;
    char* concat_str = malloc(strlen(str1) + strlen(str2) + 1);
    strcpy(concat_str, "");
    char* output = concat_str;
    while(*temp_str2 != '\0' || *temp_str1 != '\0')
    {
        if (compare_roman_letter(*temp_str1, *temp_str2) == true)
        {
            strcat(output, convert_char_to_str(*temp_str1));
            output++;
            temp_str1++;
        }
        else
        {
            strcat(output, convert_char_to_str(*temp_str2));
            output++;
            temp_str2++;
        }
    }
    return concat_str;
}

// Struct for grouping and substituion
typedef struct
{
    const char* str1;
    const char* str2;
} RomanNumeralMapElem;

RomanNumeralMapElem ReplaceMap[] = {
    {"IIIII", "V"},
    {"VV", "X"},
    {"XXXXX", "L"},
    {"LL", "C"},
    {"CCCCC", "D"},
    {"DD", "M"},
    {"0", NULL}
};

RomanNumeralMapElem SpecialReplaceMap[] = {
    {"DCCCC", "CM"},
    {"CCCC", "CD"},
    {"LXXXX", "XC"},
    {"XXXX", "XL"},
    {"VIIII", "IX"},
    {"IIII", "IV"},
    {"0", NULL}
};

// 3. Group smaller numeral to bigger
// 4. Substitute all substractives to legal Roman Numeral
char* group_and_construct_output(char* str)
{
    // Group
    RomanNumeralMapElem* temp = ReplaceMap;
    char* src = str;
    while(strcmp((*temp).str1, "0"))
    {
        char* newStr = str_replace(src, (*temp).str1, (*temp).str2);
        free(src);
        src = newStr;
        temp++;
    }

    temp = SpecialReplaceMap;
    while(strcmp((*temp).str1, "0"))
    {
        char* newStr = str_replace(src, (*temp).str1, (*temp).str2);
        free(src);
        src = newStr;
        temp++;
    }

    return src;
}

char* replace_subtractive_string(char* str)
{
    RomanNumeralMapElem* temp = SpecialReplaceMap;
    char* src = str;
    while(strcmp((*temp).str1, "0"))
    {
        char* newStr = str_replace(src, (*temp).str2, (*temp).str1);
        free(src);
        src = newStr;
        temp++;
    }

    char* temp_src = src;
    char prev_numeral = *temp_src;
    // Loop through string to make sure this string is a valid Roman Numeral
    while(*temp_src != '\0')
    {
        if (compare_roman_letter(*temp_src, prev_numeral) == true)
        {
            free(src);
            return("0");
        }
        prev_numeral = *temp_src;
        temp_src++;
    }
    return src;
}

// Remove all common strings within str1 and str2
// Rely on order of Roman Numeral
void remove_common_numeral(char* str1, char* str2)
{
    char* src1 = str1;
    char* src2 = str2;
    char* dst1 = str1;
    char* dst2 = str2;
    while(*src1 != '\0' || *src2 != '\0')
    {
        if (compare_roman_letter(*src1, *src2) == true)
        {
            *dst1 = *src1;
            dst1++;
            src1++;
        }
        else if (*src1 == *src2)
        {
            src1++;
            src2++;
        }
        else
        {
            *dst2 = *src2;
            dst2++;
            src2++;
        }
    }
    *dst1 = '\0';
    *dst2 = '\0';
}

// output = str1 + str2
// Steps of Roman Numeral Addition
// 1. substitute all subtractives with its original Numeral. For instamce, IV would be substitute with IIII.
// 2. Concatenate both strings and reorder them form M -> I
// 3. Group strings
// 4. Substitute all substractives to legal Roman Numeral
char* add(char* str1, char* str2)
{
    // Step1
    // Substitute for any subtractives
    // For calculation, we replace all subtractives with original Numeral.
    char* src1 = strdup(str1);
    char* src2 = strdup(str2);
    char* newStr1 = replace_subtractive_string(src1);
    char* newStr2 = replace_subtractive_string(src2);
    if (!strcmp(newStr1, "0") || !strcmp(newStr2, "0"))
    {
        return ("Invalid inputs");
    }
    // Step2
    // Concatenat and sort both strings
    char* concatenated_str = concatenate_and_sort_string(newStr1, newStr2);
    free(newStr1);
    free(newStr2);

    // Step3 -> Step4
    return group_and_construct_output(concatenated_str);
}

// output = str1 - str2
// Steps of Roman Numeral Subtraction
// 1. substitute all subtractives with its original Numeral. For instamce, IV would be substitute with IIII.
// 2. cross out all common numerals
// 3. Break down big numeral into small ones until str2 is empty
// 4. Group strings
// 5.Substitute all substractives to legal Roman Numeral
char* sub(char* str1, char* str2)
{
    // Step1
    // Substitute for any subtractives
    // For calculation, we replace all subtractives with original Numeral.
    char* src1 = strdup(str1);
    char* src2 = strdup(str2);
    char* newStr1 = replace_subtractive_string(src1);
    char* newStr2 = replace_subtractive_string(src2);
    if (!strcmp(newStr1, "0") || !strcmp(newStr2, "0"))
    {
        return ("Invalid inputs");
    }

    // Step2
    remove_common_numeral(newStr1, newStr2);
    // If string 1 is already empty, illegal inputs
    if (!strcmp(newStr1, ""))
    {
        free(newStr1);
        free(newStr2);
        return("Invalid inputs");
    }
    // Step3
    // Process when string 2 is not empty
    while(strcmp(newStr2, ""))
    {
        // Smallest Roman Numeral in string 2
        char* temp = newStr2 + strlen(newStr2) - 1;
        // loop through string 1 in reverse order
        char* temp_str1 = newStr1 + strlen(newStr1) - 1;
        bool valid = false;
        while(temp_str1 >= newStr1)
        {
            // found a bigger one, break it down to next level
            if (compare_roman_letter(*temp_str1, *temp) == true)
            {
                valid = true;
                char* replacement;
                switch(*temp_str1) {
                    case 'M':   replacement = "DD"; break;
                    case 'D':   replacement = "CCCCC"; break;
                    case 'C':   replacement = "LL"; break;
                    case 'L':   replacement = "XXXXX"; break;
                    case 'X':   replacement = "VV"; break;
                    case 'V':   replacement = "IIIII"; break;
                }
                char* newStr1_temp = replace_single_occurance(newStr1, temp_str1, convert_char_to_str(*temp_str1), replacement);
                // new pointer to the location of replacement
                newStr1 = newStr1_temp;
                remove_common_numeral(newStr1, newStr2);
                break;
            }
            else 
                temp_str1--;
        }
        // If valid is not set, which means there is no bigger numeral in string1 that can be broken down.
        // Indicates string1 is not greater than string2
        if (valid == false)
        {
            free(newStr1);
            free(newStr2);
            return("Invalid inputs");
        }
    }
    free(newStr2);
    // Step4-5
    // If Step3 is done properly, there should not be any group needed.
    return group_and_construct_output(newStr1);
}
