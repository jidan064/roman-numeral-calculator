#include "../src/RomanNumeralCalculator.h"
#include <check.h>

START_TEST(test_two_plus_two)
{
    char output[10] = ""; 
    add(output, "II", "II");
    ck_assert_str_eq(output, "IV");
}
END_TEST

START_TEST(test_equal_subtract_null)
{
    char output[10] = "";
    sub(output, "IV", "IV");
    ck_assert_msg (!strcmp(output,""), "Empty string should be returned when subtracting two equal Roman Numeral");
}
END_TEST

Suite *
calculator_suite (void)
{
  Suite *s = suite_create ("Calculator");

  /* Core test case */
  TCase *tc_core = tcase_create ("Core");
  tcase_add_test (tc_core, test_two_plus_two);
  tcase_add_test (tc_core, test_equal_subtract_null);
  suite_add_tcase (s, tc_core);

  /* Limits test case */
  //TCase *tc_limits = tcase_create ("Limits");
  //tcase_add_test (tc_limits, test_money_create_neg);
  //tcase_add_test (tc_limits, test_money_create_zero);
  //suite_add_tcase (s, tc_limits);

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
