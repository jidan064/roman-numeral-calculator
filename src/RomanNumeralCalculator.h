/*********************************************************
 * Description: A simple Roman Numeral Calculator with ADD/SUB functions
                It doesnt handle invalid Roman input. 
                If Roman input is not valid or subtraction result is invalid, 
                It might result in un-predictable behavior. 
 * Date:        6/17/2016
 * Author:      Ji, Dan
*********************************************************/

#ifndef _ROMAN_NUMERAL_CALCULATOR_
#define _ROMAN_NUMERAL_CALCULATOR_
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// Add function
// output = str1 + str2
char* add(char* str1, char* str2);

// Subtract function
// output = str1 - str2
char* sub(char* str1, char* str2);

#endif
