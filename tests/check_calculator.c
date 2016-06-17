#include "../src/RomanNumeral.h"
#include <check.h>

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
            add(output, a, b);
            ck_assert_str_eq(output, sum);
            // swap a and b
            add(output, b, a);
            ck_assert_str_eq(output, sum);
            // Subtraction
            sub(output, sum, a);
            ck_assert_str_eq(output, b);
            sub(output, sum, b);
            ck_assert_str_eq(output, a);
        }
    }
    fclose(fp);
}
END_TEST

Suite *
calculator_suite (void)
{
  Suite *s = suite_create ("Calculator");

  /* test case */
  TCase *tc_core = tcase_create ("AddAndSub");
  tcase_add_test (tc_core, test_file);
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
