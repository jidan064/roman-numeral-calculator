#include "../src/RomanNumeralCalculator.h"
#include <check.h>

// Romain numeral convert to integer
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

char output[100] = "";
FILE* fp;
START_TEST(test_file)
{
    // Open testcase file. 1st value is a, 2nd value is b, and 3rd is sum.
    char buff[256];
    fp = fopen("testcase.txt", "r");
    if (fp != NULL)
    {
        char a[100], b[100], sum[100];
        char* token;
        while(fgets(buff, 255, fp) != NULL)
        {
            // read in a, b and sum
            token = strtok(buff," \n");
            strcpy(a, token);
            token = strtok(NULL," \n");
            strcpy(b, token);
            token = strtok(NULL," \n");
            strcpy(sum, token);
            // perform operation and check
            // Addition
            char* result = add(a,b);
            ck_assert_str_eq(result, sum);
            free(result);
            result = add(b,a);
            ck_assert_str_eq(result, sum);
            free(result);
            // Subtraction
            result = sub(sum, a);
            ck_assert_str_eq(result, b);
            free(result);
            result = sub(sum, b);
            ck_assert_str_eq(result, a);
            free(result);
            // check invalid inputs
            ck_assert_str_eq(sub(a,sum), "Invalid inputs");
        }
    }
    fclose(fp);
}
END_TEST

START_TEST(test_illegal_case)
{
    ck_assert_str_eq(sub("I", "II"), "Invalid inputs");
    ck_assert_str_eq(sub("I", "I"), "Invalid inputs");
    ck_assert_str_eq(add("XM", "I"), "Invalid inputs");
}
END_TEST

START_TEST(test_exhaust)
{
    int i, j;
    char a[100], b[100], sum[100];
    for (i=1; i < 1001; i = i + 3)
        for (j=i; j < 1001; j = j + 3)
        {
            convert_to_roman(a, i);
            convert_to_roman(b, j);
            convert_to_roman(sum, i+j);
            char* result = add(a,b);
            ck_assert_str_eq(result, sum);
            free(result);
            result = add(b,a);
            ck_assert_str_eq(result, sum);
            free(result);
            // Subtraction
            result = sub(sum, a);
            ck_assert_str_eq(result, b);
            free(result);
            result = sub(sum, b);
            ck_assert_str_eq(result, a);
            free(result);
        }
}
END_TEST

Suite *
calculator_suite (void)
{
  Suite *s = suite_create ("Calculator");

  /* test case */
  TCase *tc_core = tcase_create ("AddAndSub");
  tcase_add_test (tc_core, test_file);
  tcase_add_test (tc_core, test_exhaust);
  tcase_add_test (tc_core, test_illegal_case);
  suite_add_tcase (s, tc_core);

  return s;
}

int main(void)
{
    int number_failed;
    Suite *s = calculator_suite();
    SRunner *sr = srunner_create(s);
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
