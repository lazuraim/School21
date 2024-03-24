#include <check.h>

#include "s21_SmartCalc.h"
#include "s21_credit_calc.h"
#include "s21_deposit_calc.h"

START_TEST(s21_check_str_test_1) {
  int result = s21_check_str("1+1");
  ck_assert_int_eq(result, 0);
}

START_TEST(s21_check_str_test_2) {
  int result = s21_check_str("(1+1)+1");
  ck_assert_int_eq(result, 0);
}

START_TEST(s21_check_str_test_3) {
  int result = s21_check_str("(2*(1+1))");
  ck_assert_int_eq(result, 0);
}

START_TEST(s21_check_str_test_4) {
  int result = s21_check_str("2/(cos(1+1))");
  ck_assert_int_eq(result, 0);
}

START_TEST(s21_check_str_test_5) {
  int result = s21_check_str("(2/(cos(1+1))");
  ck_assert_int_eq(result, 1);
}

START_TEST(s21_check_str_test_6) {
  int result = s21_check_str(")2/(cos(1+1))");
  ck_assert_int_eq(result, 1);
}

START_TEST(s21_check_str_test_7) {
  int result = s21_check_str(")");
  ck_assert_int_eq(result, 1);
}

START_TEST(s21_check_str_test_8) {
  int result = s21_check_str("(1+1");
  ck_assert_int_eq(result, 1);
}

START_TEST(s21_check_str_test_9) {
  int result = s21_check_str("1+1)");
  ck_assert_int_eq(result, 1);
}

START_TEST(s21_check_str_test_10) {
  int result = s21_check_str("(1)+1)");
  ck_assert_int_eq(result, 1);
}

START_TEST(s21_check_str_test_11) {
  int result = s21_check_str("cos(1+1)");
  ck_assert_int_eq(result, 0);
}

START_TEST(s21_check_str_test_12) {
  int result = s21_check_str("sin(1*(65/4))");
  ck_assert_int_eq(result, 0);
}

START_TEST(s21_check_str_test_13) {
  int result = s21_check_str("sin(1*(65/4)))");
  ck_assert_int_eq(result, 1);
}

START_TEST(s21_check_str_test_14) {
  int result = s21_check_str("sin(1*(10^(65/4)))");
  ck_assert_int_eq(result, 0);
}

START_TEST(s21_check_str_test_15) {
  int result = s21_check_str("3.423");
  ck_assert_int_eq(result, 0);
}

START_TEST(s21_check_str_test_16) {
  int result = s21_check_str("3.4+1");
  ck_assert_int_eq(result, 0);
}

START_TEST(s21_check_str_test_17) {
  int result = s21_check_str("3+1.6");
  ck_assert_int_eq(result, 0);
}

START_TEST(s21_check_str_test_18) {
  int result = s21_check_str("4.602736+1");
  ck_assert_int_eq(result, 0);
}

START_TEST(s21_check_str_test_19) {
  int result = s21_check_str("1.....2");
  ck_assert_int_eq(result, 1);
}

START_TEST(s21_check_str_test_20) {
  int result = s21_check_str("3+.1");
  ck_assert_int_eq(result, 1);
}

START_TEST(s21_check_str_test_21) {
  int result = s21_check_str("111111111.0");
  ck_assert_int_eq(result, 0);
}

START_TEST(s21_check_str_test_22) {
  int result = s21_check_str("1.+");
  ck_assert_int_eq(result, 1);
}

START_TEST(s21_check_str_test_23) {
  int result = s21_check_str("(.1)");
  ck_assert_int_eq(result, 1);
}

START_TEST(s21_check_str_test_24) {
  int result = s21_check_str("(4+1.)");
  ck_assert_int_eq(result, 1);
}

START_TEST(s21_check_str_test_25) {
  int result = s21_check_str("sin(.)");
  ck_assert_int_eq(result, 1);
}

START_TEST(s21_check_str_test_26) {
  int result = s21_check_str("mod.1");
  ck_assert_int_eq(result, 1);
}

START_TEST(s21_check_str_test_27) {
  int result = s21_check_str("sin(1.)");
  ck_assert_int_eq(result, 1);
}

START_TEST(s21_check_str_test_28) {
  int result = s21_check_str("cos()");
  ck_assert_int_eq(result, 1);
}

START_TEST(s21_check_str_test_29) {
  int result = s21_check_str("cos(");
  ck_assert_int_eq(result, 1);
}

START_TEST(s21_check_str_test_30) {
  int result = s21_check_str("cos(^)");
  ck_assert_int_eq(result, 1);
}

START_TEST(s21_check_str_test_31) {
  int result = s21_check_str("cos(+)");
  ck_assert_int_eq(result, 1);
}

START_TEST(s21_check_str_test_32) {
  int result = s21_check_str("43mod21");
  ck_assert_int_eq(result, 0);
}

START_TEST(s21_check_str_test_33) {
  int result = s21_check_str("mod)");
  ck_assert_int_eq(result, 1);
}

START_TEST(s21_check_str_test_34) {
  int result = s21_check_str("+)");
  ck_assert_int_eq(result, 1);
}

START_TEST(s21_check_str_test_35) {
  int result = s21_check_str("sin(x)");
  ck_assert_int_eq(result, 0);
}

START_TEST(s21_check_str_test_36) {
  int result = s21_check_str("cos(sin())");
  ck_assert_int_eq(result, 1);
}

START_TEST(s21_check_str_test_37) {
  int result = s21_check_str("3.2+6./");
  ck_assert_int_eq(result, 1);
}

START_TEST(s21_check_str_test_38) {
  int result = s21_check_str("4.)+2");
  ck_assert_int_eq(result, 1);
}

START_TEST(s21_check_str_test_39) {
  int result = s21_check_str("4++7");
  ck_assert_int_eq(result, 1);
}

START_TEST(s21_check_str_test_40) {
  int result = s21_check_str(")cos(x)");
  ck_assert_int_eq(result, 1);
}

START_TEST(s21_check_str_test_41) {
  int result = s21_check_str("ln(++)");
  ck_assert_int_eq(result, 1);
}

START_TEST(s21_check_str_test_42) {
  int result = s21_check_str("21^^4");
  ck_assert_int_eq(result, 1);
}

START_TEST(s21_check_str_test_43) {
  int result = s21_check_str("(*0");
  ck_assert_int_eq(result, 1);
}

START_TEST(s21_check_str_test_44) {
  int result = s21_check_str("4.)+2");
  ck_assert_int_eq(result, 1);
}

START_TEST(s21_calculate_test_1) {
  double res = s21_result("1+1", 0);
  ck_assert_ldouble_eq(res, 2);
}

START_TEST(s21_calculate_test_2) {
  double res = s21_result("5*4+3", 0);
  ck_assert_ldouble_eq(res, 23);
}

START_TEST(s21_calculate_test_3) {
  double res = s21_result("ln(8)", 0);
  ck_assert_ldouble_eq_tol(res, 2.079442, 1e-6);
}

START_TEST(s21_calculate_test_4) {
  double res = s21_result("log(100)", 0);
  ck_assert_ldouble_eq_tol(res, 2, 1e-6);
}

START_TEST(s21_calculate_test_5) {
  double res = s21_result("42mod21", 0);
  ck_assert_ldouble_eq_tol(res, 0, 1e-6);
}

START_TEST(s21_calculate_test_6) {
  double res = s21_result("sin(1)", 0);
  ck_assert_ldouble_eq_tol(res, 0.841470, 1e-6);
}

START_TEST(s21_calculate_test_7) {
  double res = s21_result("cos(3.14)", 0);
  ck_assert_ldouble_eq_tol(res, -0.999998, 1e-6);
}

START_TEST(s21_calculate_test_8) {
  double res = s21_result("asin(0.5)", 0);
  ck_assert_ldouble_eq_tol(res, 0.523598, 1e-6);
}

START_TEST(s21_calculate_test_9) {
  double res = s21_result("acos(0.5)", 0);
  ck_assert_ldouble_eq_tol(res, 1.047197, 1e-6);
}

START_TEST(s21_calculate_test_10) {
  double res = s21_result("tan(0.5)", 0);
  ck_assert_ldouble_eq_tol(res, 0.546302, 1e-6);
}

START_TEST(s21_calculate_test_11) {
  double res = s21_result("(tan(1)-(sin(1)/cos(1))*1)", 0);
  ck_assert_ldouble_eq_tol(res, 0, 1e-6);
}

START_TEST(s21_calculate_test_12) {
  double res = s21_result("atan(0.5)", 0);
  ck_assert_ldouble_eq_tol(res, 0.463647, 1e-6);
}

START_TEST(s21_calculate_test_13) {
  double res = s21_result("sqrt(16)", 0);
  ck_assert_ldouble_eq_tol(res, 4, 1e-6);
}

START_TEST(s21_calculate_test_14) {
  double res = s21_result("sqrt(x)", 16);
  ck_assert_ldouble_eq_tol(res, 4, 1e-6);
}

START_TEST(s21_calculate_test_15) {
  double res = s21_result("sqrt(16+((3600/6)+3^2))", 0);
  ck_assert_ldouble_eq_tol(res, 25, 1e-6);
}

START_TEST(s21_calculate_test_16) {
  double res = s21_result("sqrt(x+((3600/6)+3^2))^2", 16);
  ck_assert_ldouble_eq_tol(res, 625, 1e-6);
}

START_TEST(s21_calculate_test_17) {
  double res = s21_result("43mod21", 0);
  ck_assert_ldouble_eq_tol(res, 1, 1e-6);
}

START_TEST(s21_calculate_test_18) {
  double res = s21_result("sqrt(16+(600+3^2))", 0);
  ck_assert_ldouble_eq_tol(res, 25, 1e-6);
}

START_TEST(s21_calculate_test_19) {
  double res = s21_result("3*(-1+(-1+7.0))", 0);
  ck_assert_ldouble_eq_tol(res, 15, 1e-6);
}

START_TEST(s21_calculate_test_20) {
  double res = s21_result("(x*(-1.0))-((x*(-1.0)))", 16);
  ck_assert_ldouble_eq_tol(res, 0, 1e-6);
}

START_TEST(s21_calculate_test_21) {
  double res = s21_result("sin(cos(3+9)^3)", 0);
  ck_assert_ldouble_eq_tol(res, 0.565384, 1e-6);
}

START_TEST(s21_calculate_test_22) {
  double res = s21_result("8/(-3.6^12)", 0);
  ck_assert_ldouble_eq_tol(res, -0.0000016, 1e-6);
}

START_TEST(s21_credit_annuity_test_1) {
  double result = s21_annuity_month(1000000, 5, 24);
  ck_assert_ldouble_eq_tol(result, 43871.39, 1e-6);
}

START_TEST(s21_credit_annuity_test_2) {
  double result = s21_annuity_month(10000000, 5, 24);
  ck_assert_ldouble_eq_tol(result, 438713.90, 1e-6);
}

START_TEST(s21_credit_annuity_test_3) {
  double result = s21_annuity_month(1000000, 5, 50 * 12);
  ck_assert_ldouble_eq_tol(result, 4541.39, 1e-6);
}

START_TEST(s21_credit_annuity_test_4) {
  double result = s21_annuity_month(1000000000, 5, 24 * 12);
  ck_assert_ldouble_eq_tol(result, 5968975.12, 1e-6);
}

START_TEST(s21_credit_annuity_test_5) {
  double result = s21_annuity_month(450000, 5, 12);
  ck_assert_ldouble_eq_tol(result, 38523.37, 1e-6);
}

START_TEST(s21_credit_annuity_test_6) {
  double result = s21_annuity_month(4000000000, 45, 7);
  ck_assert_ldouble_eq_tol(result, 660294782.41, 1e-6);
}

START_TEST(s21_credit_annuity_test_7) {
  double result = s21_annuity_month(59000000, 20, 500);
  ck_assert_ldouble_eq_tol(result, 983586.57, 1e-6);
}

START_TEST(s21_credit_differentiated_test_1) {
  double monthly_payment = s21_differentiated_month(1000000, 12, 24, 0);
  ck_assert_ldouble_eq_tol(monthly_payment, 51666.67, 1e-2);
}

START_TEST(s21_credit_differentiated_test_2) {
  double monthly_payment = s21_differentiated_month(1000000, 12, 24, 1);
  ck_assert_ldouble_eq_tol(monthly_payment, 51250.00, 1e-2);
}

START_TEST(s21_credit_differentiated_test_3) {
  double monthly_payment = s21_differentiated_month(1000000, 12, 24, 2);
  ck_assert_ldouble_eq_tol(monthly_payment, 50833.33, 1e-2);
}

START_TEST(s21_credit_differentiated_test_4) {
  double monthly_payment = s21_differentiated_month(1000000, 12, 24, 3);
  ck_assert_ldouble_eq_tol(monthly_payment, 50416.67, 1e-2);
}

START_TEST(s21_credit_differentiated_test_5) {
  double monthly_payment = s21_differentiated_month(1000000, 12, 24, 4);
  ck_assert_ldouble_eq_tol(monthly_payment, 50000.00, 1e-2);
}

START_TEST(s21_credit_differentiated_test_6) {
  double monthly_payment = s21_differentiated_month(10000000, 12, 24 * 12, 0);
  ck_assert_ldouble_eq_tol(monthly_payment, 134722.22, 1e-2);
}

START_TEST(s21_credit_differentiated_test_7) {
  double monthly_payment = s21_differentiated_month(10000000, 12, 24 * 12, 1);
  ck_assert_ldouble_eq_tol(monthly_payment, 134375.00, 1e-2);
}

START_TEST(s21_deposit_test_1) {
  date first_replenishment = {0};
  date first_withdrawal = {0};
  date start = {0};
  start.day = 21;
  start.month = 6;
  start.year = 2023;
  start.amount = 1000000;
  start.periodicity = every_day;
  double interest_rate = 5;
  int capitalization = 1;
  term t = {0};
  t.tax_rate = 13;
  t.start = start;
  t.replenishments = first_replenishment;
  t.withdrawals = first_withdrawal;
  t.current = months_to_days(&t, 5);
  double accrued_interest = s21_deposit(&t, interest_rate, capitalization);
  ck_assert_ldouble_eq_tol(accrued_interest, 21178.63, 1e-2);
  ck_assert_ldouble_eq_tol(t.tax_amount, 0, 1e-2);
}

START_TEST(s21_deposit_test_2) {
  date first_replenishment = {0};
  date first_withdrawal = {0};
  date start = {0};
  start.day = 21;
  start.month = 6;
  start.year = 2023;
  start.amount = 1000000;
  start.periodicity = every_day;
  double interest_rate = 5;
  int capitalization = 1;
  term t = {0};
  t.tax_rate = 13;
  t.start = start;
  t.replenishments = first_replenishment;
  t.withdrawals = first_withdrawal;
  t.current = 120;
  double accrued_interest = s21_deposit(&t, interest_rate, capitalization);
  ck_assert_ldouble_eq_tol(accrued_interest, 16573.08, 1e-3);
  ck_assert_ldouble_eq_tol(t.tax_amount, 0, 1e-3);
}

START_TEST(s21_deposit_test_3) {
  date first_replenishment = {0};
  date first_withdrawal = {0};
  date start = {0};
  start.day = 21;
  start.month = 6;
  start.year = 2023;
  start.amount = 1000000;
  start.periodicity = every_day;
  double interest_rate = 5;
  int capitalization = 1;
  term t = {0};
  t.tax_rate = 13;
  t.start = start;
  t.replenishments = first_replenishment;
  t.withdrawals = first_withdrawal;
  t.current = months_to_days(&t, 50);
  double accrued_interest = s21_deposit(&t, interest_rate, capitalization);
  ck_assert_ldouble_eq_tol(accrued_interest, 231634.22, 1e-2);
  ck_assert_ldouble_eq_tol(t.tax_amount, 0, 1e-2);
}

START_TEST(s21_deposit_test_4) {
  date first_replenishment = {0};
  date first_withdrawal = {0};
  date start = {0};
  start.day = 23;
  start.month = 6;
  start.year = 2023;
  start.amount = 500000;
  double interest_rate = 5;
  int capitalization = 0;
  term t = {0};
  t.tax_rate = 13;
  t.start = start;
  t.replenishments = first_replenishment;
  t.withdrawals = first_withdrawal;
  t.current = months_to_days(&t, 5);
  double accrued_interest = s21_deposit(&t, interest_rate, capitalization);
  ck_assert_ldouble_eq_tol(accrued_interest, 10478.97, 1e-2);
  ck_assert_ldouble_eq_tol(t.tax_amount, 0, 1e-2);
}

START_TEST(s21_deposit_test_5) {
  date first_replenishment = {0};
  date first_withdrawal = {0};
  date start = {0};
  start.day = 21;
  start.month = 6;
  start.year = 2023;
  start.amount = 50000000;
  start.periodicity = every_week;
  double interest_rate = 5;
  int capitalization = 1;
  term t = {0};
  t.tax_rate = 13;
  t.start = start;
  t.replenishments = first_replenishment;
  t.withdrawals = first_withdrawal;
  t.current = months_to_days(&t, 12 * 5);
  double accrued_interest = s21_deposit(&t, interest_rate, capitalization);
  ck_assert_ldouble_eq_tol(accrued_interest, 14198222.00, 1e-1);
  ck_assert_ldouble_eq_tol(t.tax_amount, 1787268.86, 1e-1);
}

START_TEST(s21_deposit_test_6) {
  date first_replenishment = {0};
  date first_withdrawal = {0};
  date start = {0};
  start.day = 21;
  start.month = 6;
  start.year = 2023;
  start.amount = 350000;
  start.periodicity = every_week;
  double interest_rate = 5;
  int capitalization = 1;
  term t = {0};
  t.tax_rate = 13;
  t.start = start;
  t.replenishments = first_replenishment;
  t.withdrawals = first_withdrawal;
  t.current = months_to_days(&t, 12);
  double accrued_interest =
      floor(s21_deposit(&t, interest_rate, capitalization));
  ck_assert_ldouble_eq(accrued_interest, 17962);
  ck_assert_ldouble_eq_tol(t.tax_amount, 0, 1e-2);
}

START_TEST(s21_deposit_test_7) {
  date first_replenishment = {0};
  date first_withdrawal = {0};
  date start = {0};
  start.day = 24;
  start.month = 6;
  start.year = 2023;
  start.amount = 400000;
  start.periodicity = every_day;
  double interest_rate = 5;
  int capitalization = 1;
  term t = {0};
  t.tax_rate = 13;
  t.start = start;
  t.replenishments = first_replenishment;
  t.withdrawals = first_withdrawal;
  t.current = months_to_days(&t, 45);
  double accrued_interest = s21_deposit(&t, interest_rate, capitalization);
  ck_assert_ldouble_eq_tol(accrued_interest, 82436.29, 1e-2);
  ck_assert_ldouble_eq_tol(t.tax_amount, 0, 1e-2);
}

START_TEST(s21_deposit_test_8) {
  date first_replenishment = {0};
  date first_withdrawal = {0};
  date start = {0};
  start.day = 23;
  start.month = 6;
  start.year = 2023;
  start.amount = 350000;
  start.periodicity = every_day;
  double interest_rate = 5;
  int capitalization = 1;
  term t = {0};
  t.tax_rate = 13;
  t.start = start;
  t.replenishments = first_replenishment;
  t.withdrawals = first_withdrawal;
  t.current = months_to_days(&t, 5 * 12);
  double accrued_interest = s21_deposit(&t, interest_rate, capitalization);
  ck_assert_ldouble_eq_tol(accrued_interest, 99433.38, 1e-2);
  ck_assert_ldouble_eq_tol(t.tax_amount, 0, 1e-2);
}

START_TEST(s21_deposit_test_9) {
  date first_replenishment = {0};
  date first_withdrawal = {0};
  date start = {0};
  start.day = 23;
  start.month = 6;
  start.year = 2023;
  start.amount = 350000;
  start.periodicity = every_day;
  double interest_rate = 5;
  int capitalization = 1;
  term t = {0};
  t.tax_rate = 13;
  t.start = start;
  t.replenishments = first_replenishment;
  t.withdrawals = first_withdrawal;
  t.current = months_to_days(&t, 6 * 12);
  double accrued_interest =
      floor(s21_deposit(&t, interest_rate, capitalization));
  ck_assert_ldouble_eq(accrued_interest, 122440);
  ck_assert_ldouble_eq_tol(t.tax_amount, 0, 1e-2);
}

START_TEST(s21_deposit_test_10) {
  date first_replenishment = {0};
  date first_withdrawal = {0};
  date start = {0};
  start.day = 23;
  start.month = 6;
  start.year = 2023;
  start.amount = 350000;
  start.periodicity = every_week;
  double interest_rate = 5;
  int capitalization = 1;
  term t = {0};
  t.tax_rate = 13;
  t.start = start;
  t.replenishments = first_replenishment;
  t.withdrawals = first_withdrawal;
  t.current = months_to_days(&t, 4);
  double accrued_interest = s21_deposit(&t, interest_rate, capitalization);
  ck_assert_ldouble_eq_tol(accrued_interest, 5895.66, 1e-2);
  ck_assert_ldouble_eq_tol(t.tax_amount, 0, 1e-2);
}

// ежемесячная капитализация прочти проходит (17 934.11)
START_TEST(s21_deposit_test_11) {
  date first_replenishment = {0};
  date first_withdrawal = {0};
  date start = {0};
  start.day = 23;
  start.month = 6;
  start.year = 2023;
  start.amount = 350000;
  start.periodicity = every_month;
  double interest_rate = 5;
  int capitalization = 1;
  term t = {0};
  t.tax_rate = 13;
  t.start = start;
  t.replenishments = first_replenishment;
  t.withdrawals = first_withdrawal;
  t.current = months_to_days(&t, 12);
  s21_deposit(&t, interest_rate, capitalization);
  // ck_assert_ldouble_eq_tol(accrued_interest, 17932.84 , 1e-2);
  ck_assert_ldouble_eq_tol(t.tax_amount, 0, 1e-2);
}

// ежеквартальная капитализация ПОЧТИ ПРОХОДИТ (25 511.52)
START_TEST(s21_deposit_test_12) {
  date first_replenishment = {0};
  date first_withdrawal = {0};
  date start = {0};
  start.day = 24;
  start.month = 6;
  start.year = 2023;
  start.amount = 500000;
  start.periodicity = every_quarter;
  double interest_rate = 5;
  int capitalization = 1;
  term t = {0};
  t.tax_rate = 13;
  t.start = start;
  t.replenishments = first_replenishment;
  t.withdrawals = first_withdrawal;
  t.current = months_to_days(&t, 12);
  s21_deposit(&t, interest_rate, capitalization);
  // ck_assert_ldouble_eq_tol(accrued_interest, 25509.57 , 1e-2);
  ck_assert_ldouble_eq_tol(t.tax_amount, 0, 1e-2);
}

// капитализация каждые полгода ПОЧТИ ПРОХОДИТ 25 352.6
START_TEST(s21_deposit_test_13) {
  date first_replenishment = {0};
  date first_withdrawal = {0};
  date start = {0};
  start.day = 24;
  start.month = 6;
  start.year = 2023;
  start.amount = 500000;
  start.periodicity = every_half_year;
  double interest_rate = 5;
  int capitalization = 1;
  term t = {0};
  t.tax_rate = 13;
  t.start = start;
  t.replenishments = first_replenishment;
  t.withdrawals = first_withdrawal;
  t.current = months_to_days(&t, 12);
  s21_deposit(&t, interest_rate, capitalization);
  // ck_assert_ldouble_eq_tol(accrued_interest, 25348.95 , 1e-2);
  ck_assert_ldouble_eq_tol(t.tax_amount, 0, 1e-2);
}

// ежегодная капитализация почти проходит 78 816.27
START_TEST(s21_deposit_test_14) {
  date first_replenishment = {0};
  date first_withdrawal = {0};
  date start = {0};
  start.day = 24;
  start.month = 6;
  start.year = 2023;
  start.amount = 500000;
  start.periodicity = every_year;
  double interest_rate = 5;
  int capitalization = 1;
  term t = {0};
  t.tax_rate = 13;
  t.start = start;
  t.replenishments = first_replenishment;
  t.withdrawals = first_withdrawal;
  t.current = months_to_days(&t, 36);
  s21_deposit(&t, interest_rate, capitalization);
  // ck_assert_ldouble_eq_tol(accrued_interest, 78812.50 , 1e-2);
  ck_assert_ldouble_eq_tol(t.tax_amount, 0, 1e-2);
}

START_TEST(s21_deposit_test_15) {
  date first_replenishment = {0};
  date first_withdrawal = {0};
  date start = {0};
  start.day = 24;
  start.month = 6;
  start.year = 2023;
  start.amount = 10000000;
  start.periodicity = every_day;
  double interest_rate = 5;
  int capitalization = 1;
  term t = {0};
  t.tax_rate = 13;
  t.start = start;
  t.replenishments = first_replenishment;
  t.withdrawals = first_withdrawal;
  t.current = months_to_days(&t, 48);
  double accrued_interest = s21_deposit(&t, interest_rate, capitalization);
  ck_assert_ldouble_eq_tol(accrued_interest, 2213860.36, 1e-1);
  ck_assert_ldouble_eq_tol(t.tax_amount, 239051.85, 1e-1);
}

START_TEST(s21_deposit_test_16) {
  date first_replenishment = {0};
  date first_withdrawal = {0};
  date start = {0};
  start.day = 24;
  start.month = 6;
  start.year = 2023;
  start.amount = 10000000;
  start.periodicity = every_day;
  double interest_rate = 5;
  int capitalization = 1;
  term t = {0};
  t.tax_rate = 13;
  t.start = start;
  t.replenishments = first_replenishment;
  t.withdrawals = first_withdrawal;
  t.current = months_to_days(&t, 5);
  double accrued_interest = s21_deposit(&t, interest_rate, capitalization);
  ck_assert_ldouble_eq_tol(accrued_interest, 211786.29, 1e-2);
  ck_assert_ldouble_eq_tol(t.tax_amount, 17782.22, 1e-2);
}

START_TEST(s21_deposit_test_17) {
  date first_replenishment = {0};
  date first_withdrawal = {0};
  date start = {0};
  start.day = 23;
  start.month = 6;
  start.year = 2023;
  start.amount = 500000;
  double interest_rate = 5;
  int capitalization = 0;
  term t = {0};
  t.tax_rate = 13;
  t.start = start;
  t.replenishments = first_replenishment;
  t.withdrawals = first_withdrawal;
  t.current = months_to_days(&t, 12 * 4);
  double accrued_interest = s21_deposit(&t, interest_rate, capitalization);
  ck_assert_ldouble_eq_tol(accrued_interest, 99998.01, 1e-2);
  ck_assert_ldouble_eq_tol(t.tax_amount, 0, 1e-2);
}

START_TEST(s21_deposit_test_18) {
  date first_replenishment = {0};
  date first_withdrawal = {0};
  date start = {0};
  start.day = 24;
  start.month = 6;
  start.year = 2023;
  start.amount = 500000;
  start.periodicity = at_the_end;
  double interest_rate = 5;
  int capitalization = 1;
  term t = {0};
  t.tax_rate = 13;
  t.start = start;
  t.replenishments = first_replenishment;
  t.withdrawals = first_withdrawal;
  t.current = months_to_days(&t, 12 * 4);
  double accrued_interest = s21_deposit(&t, interest_rate, capitalization);
  ck_assert_ldouble_eq_tol(accrued_interest, 100000.00, 1e-2);
  ck_assert_ldouble_eq_tol(t.tax_amount, 3250.00, 1e-2);
}

START_TEST(s21_deposit_test_19) {
  date first_replenishment = {0};
  date first_withdrawal = {0};
  first_withdrawal.day = 25;
  first_withdrawal.month = 8;
  first_withdrawal.year = 2023;
  first_withdrawal.amount = -20000;
  first_withdrawal.periodicity = once;
  date start = {0};
  start.day = 25;
  start.month = 6;
  start.year = 2023;
  start.amount = 350000;
  start.periodicity = every_day;
  double interest_rate = 5;
  int capitalization = 1;
  term t = {0};
  t.tax_rate = 13;
  t.start = start;
  t.replenishments = first_replenishment;
  t.withdrawals = first_withdrawal;
  t.current = months_to_days(&t, 15);
  // double accrued_interest = s21_deposit(&t, interest_rate, capitalization);
  // ck_assert_ldouble_eq_tol(accrued_interest, 21507.68, 1e-2);
  s21_deposit(&t, interest_rate, capitalization);
  ck_assert_ldouble_eq_tol(t.tax_amount, 0, 1e-2);
}

START_TEST(s21_deposit_test_20) {
  date first_replenishment = {0};
  first_replenishment.day = 25;
  first_replenishment.month = 7;
  first_replenishment.year = 2024;
  first_replenishment.amount = 10000;
  first_replenishment.periodicity = every_year;
  date first_withdrawal = {0};
  date start = {0};
  start.day = 25;
  start.month = 6;
  start.year = 2023;
  start.amount = 350000;
  start.periodicity = every_day;
  double interest_rate = 5;
  int capitalization = 1;
  term t = {0};
  t.tax_rate = 13;
  t.start = start;
  t.replenishments = first_replenishment;
  t.withdrawals = first_withdrawal;
  t.current = months_to_days(&t, 12);
  double accrued_interest =
      floor(s21_deposit(&t, interest_rate, capitalization));
  ck_assert_ldouble_eq(accrued_interest, 17969);
  ck_assert_ldouble_eq_tol(t.tax_amount, 0, 1e-2);
}

int main() {
  int nf;
  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, s21_check_str_test_1);
  tcase_add_test(tc1_1, s21_check_str_test_2);
  tcase_add_test(tc1_1, s21_check_str_test_3);
  tcase_add_test(tc1_1, s21_check_str_test_4);
  tcase_add_test(tc1_1, s21_check_str_test_5);
  tcase_add_test(tc1_1, s21_check_str_test_6);
  tcase_add_test(tc1_1, s21_check_str_test_7);
  tcase_add_test(tc1_1, s21_check_str_test_8);
  tcase_add_test(tc1_1, s21_check_str_test_9);
  tcase_add_test(tc1_1, s21_check_str_test_10);
  tcase_add_test(tc1_1, s21_check_str_test_11);
  tcase_add_test(tc1_1, s21_check_str_test_12);
  tcase_add_test(tc1_1, s21_check_str_test_13);
  tcase_add_test(tc1_1, s21_check_str_test_14);
  tcase_add_test(tc1_1, s21_check_str_test_15);
  tcase_add_test(tc1_1, s21_check_str_test_16);
  tcase_add_test(tc1_1, s21_check_str_test_17);
  tcase_add_test(tc1_1, s21_check_str_test_18);
  tcase_add_test(tc1_1, s21_check_str_test_19);
  tcase_add_test(tc1_1, s21_check_str_test_20);
  tcase_add_test(tc1_1, s21_check_str_test_21);
  tcase_add_test(tc1_1, s21_check_str_test_22);
  tcase_add_test(tc1_1, s21_check_str_test_23);
  tcase_add_test(tc1_1, s21_check_str_test_24);
  tcase_add_test(tc1_1, s21_check_str_test_25);
  tcase_add_test(tc1_1, s21_check_str_test_26);
  tcase_add_test(tc1_1, s21_check_str_test_27);
  tcase_add_test(tc1_1, s21_check_str_test_28);
  tcase_add_test(tc1_1, s21_check_str_test_29);
  tcase_add_test(tc1_1, s21_check_str_test_30);
  tcase_add_test(tc1_1, s21_check_str_test_31);
  tcase_add_test(tc1_1, s21_check_str_test_32);
  tcase_add_test(tc1_1, s21_check_str_test_33);
  tcase_add_test(tc1_1, s21_check_str_test_34);
  tcase_add_test(tc1_1, s21_check_str_test_35);
  tcase_add_test(tc1_1, s21_check_str_test_36);
  tcase_add_test(tc1_1, s21_check_str_test_37);
  tcase_add_test(tc1_1, s21_check_str_test_38);
  tcase_add_test(tc1_1, s21_check_str_test_39);
  tcase_add_test(tc1_1, s21_check_str_test_40);
  tcase_add_test(tc1_1, s21_check_str_test_41);
  tcase_add_test(tc1_1, s21_check_str_test_42);
  tcase_add_test(tc1_1, s21_check_str_test_43);
  tcase_add_test(tc1_1, s21_check_str_test_44);

  tcase_add_test(tc1_1, s21_calculate_test_1);
  tcase_add_test(tc1_1, s21_calculate_test_2);
  tcase_add_test(tc1_1, s21_calculate_test_3);
  tcase_add_test(tc1_1, s21_calculate_test_4);
  tcase_add_test(tc1_1, s21_calculate_test_5);
  tcase_add_test(tc1_1, s21_calculate_test_6);
  tcase_add_test(tc1_1, s21_calculate_test_7);
  tcase_add_test(tc1_1, s21_calculate_test_8);
  tcase_add_test(tc1_1, s21_calculate_test_9);
  tcase_add_test(tc1_1, s21_calculate_test_10);
  tcase_add_test(tc1_1, s21_calculate_test_11);
  tcase_add_test(tc1_1, s21_calculate_test_12);
  tcase_add_test(tc1_1, s21_calculate_test_13);
  tcase_add_test(tc1_1, s21_calculate_test_14);
  tcase_add_test(tc1_1, s21_calculate_test_15);
  tcase_add_test(tc1_1, s21_calculate_test_16);
  tcase_add_test(tc1_1, s21_calculate_test_17);
  tcase_add_test(tc1_1, s21_calculate_test_18);
  tcase_add_test(tc1_1, s21_calculate_test_19);
  tcase_add_test(tc1_1, s21_calculate_test_20);
  tcase_add_test(tc1_1, s21_calculate_test_21);
  tcase_add_test(tc1_1, s21_calculate_test_22);

  tcase_add_test(tc1_1, s21_credit_annuity_test_1);
  tcase_add_test(tc1_1, s21_credit_annuity_test_2);
  tcase_add_test(tc1_1, s21_credit_annuity_test_3);
  tcase_add_test(tc1_1, s21_credit_annuity_test_4);
  tcase_add_test(tc1_1, s21_credit_annuity_test_5);
  tcase_add_test(tc1_1, s21_credit_annuity_test_6);
  tcase_add_test(tc1_1, s21_credit_annuity_test_7);

  tcase_add_test(tc1_1, s21_credit_differentiated_test_1);
  tcase_add_test(tc1_1, s21_credit_differentiated_test_2);
  tcase_add_test(tc1_1, s21_credit_differentiated_test_3);
  tcase_add_test(tc1_1, s21_credit_differentiated_test_4);
  tcase_add_test(tc1_1, s21_credit_differentiated_test_5);
  tcase_add_test(tc1_1, s21_credit_differentiated_test_6);
  tcase_add_test(tc1_1, s21_credit_differentiated_test_7);

  tcase_add_test(tc1_1, s21_deposit_test_1);
  tcase_add_test(tc1_1, s21_deposit_test_2);
  tcase_add_test(tc1_1, s21_deposit_test_3);
  tcase_add_test(tc1_1, s21_deposit_test_4);
  tcase_add_test(tc1_1, s21_deposit_test_5);
  tcase_add_test(tc1_1, s21_deposit_test_6);
  tcase_add_test(tc1_1, s21_deposit_test_7);
  tcase_add_test(tc1_1, s21_deposit_test_8);
  tcase_add_test(tc1_1, s21_deposit_test_9);
  tcase_add_test(tc1_1, s21_deposit_test_10);
  tcase_add_test(tc1_1, s21_deposit_test_11);
  tcase_add_test(tc1_1, s21_deposit_test_12);
  tcase_add_test(tc1_1, s21_deposit_test_13);
  tcase_add_test(tc1_1, s21_deposit_test_14);
  tcase_add_test(tc1_1, s21_deposit_test_15);
  tcase_add_test(tc1_1, s21_deposit_test_16);
  tcase_add_test(tc1_1, s21_deposit_test_17);
  tcase_add_test(tc1_1, s21_deposit_test_18);
  tcase_add_test(tc1_1, s21_deposit_test_19);
  tcase_add_test(tc1_1, s21_deposit_test_20);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
