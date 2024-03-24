#include <math.h>
#include <stdio.h>

typedef struct {
  int day;
  int month;
  int year;
  int periodicity;
  double amount;
  int number_of_transactions;
} date;

typedef struct term {
  double tax_rate;
  double current;
  int deadline;
  int leap_year;
  date start;
  date withdrawals;
  date replenishments;
  int current_year_in_loop;
  int number_of_full_365;
  double accrued_year;
  double tax_amount;
  double end_deposit;
} term;

enum {
  once = 0,
  every_day = 1,
  every_week = 7,
  every_month = 30,
  every_two_months = 60,
  every_quarter = 91,
  every_half_year = 182,
  every_year = 365,
  at_the_end = -1,
  without_taxes = 75000,
};

date *s21_define_replenishment(double r_amount, int day, int month, int r_year,
                               int periodicity);
double months_to_days(term *term_type, int month_quantity);
double calculate_accrued_interest(term *term_type, double interest_rate,
                                  int capitalization);
int number_of_day(int day_number, int month_number);
double calculate_tax_amount(double accrued_interest, double tax_rate);
double s21_deposit(term *t, double interest_rate, int capitalization);
int check_leap_year(int year);
void check_new_year_in_loop(term *t, int iteration);
double round_two_places(double number);
void tax_for_year(term *t, int iteration);
void replenishment_or_withdrawal(term *t, date *transaction, int iteration);