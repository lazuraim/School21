#include "s21_deposit_calc.h"

double s21_deposit(term *t, double interest_rate, int capitalization) {
  double accrued_interest = 0;
  t->deadline = (365 + check_leap_year(t->start.year)) -
                number_of_day(t->start.day, t->start.month);
  accrued_interest =
      calculate_accrued_interest(t, interest_rate, capitalization);
  return accrued_interest;
}

double months_to_days(term *term_type, int month_quantity) {
  int days_in_month[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  double days = 0;
  int year = term_type->start.year;
  int month = term_type->start.month;
  for (int i = 0; i < month_quantity; i++) {
    if (month == 12) {
      year++;
      days += check_leap_year(year);
    }
    days += days_in_month[month];
    month++;
    if (month % 12 == 0) {
      month = 12;
    } else {
      month = month % 12;
    }
  }
  return days;
}

int number_of_day(int day_number, int month_number) {
  int days_in_month[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  int days = 0;
  for (int i = 1; i < month_number; i++) {
    days += days_in_month[i];
  }
  days += day_number;
  return days;
}

double calculate_accrued_interest(term *t, double interest_rate,
                                  int capitalization) {
  double accrued_interest = 0;
  double accrued_term = 0;
  double accrued_total = 0;
  t->current_year_in_loop = t->start.year;
  t->leap_year = check_leap_year(t->current_year_in_loop);
  t->end_deposit = t->start.amount;
  for (int i = 1; i < t->current + 1; i++) {
    if (t->replenishments.amount != 0) {
      replenishment_or_withdrawal(t, &(t->replenishments), i);
    }
    if (t->withdrawals.amount != 0) {
      replenishment_or_withdrawal(t, &(t->withdrawals), i);
    }
    accrued_interest =
        (t->start.amount * interest_rate / (365 + t->leap_year)) / 100;

    if (t->start.periodicity == every_day || !capitalization) {
      accrued_interest = round_two_places(accrued_interest);
    }
    accrued_term += accrued_interest;
    accrued_total += accrued_interest;
    t->accrued_year += accrued_interest;
    tax_for_year(t, i);
    if (capitalization && t->start.periodicity != at_the_end) {
      if ((i % t->start.periodicity) == 0) {
        t->start.amount += round_two_places(accrued_term);
        accrued_term = 0;
      }
    }
    check_new_year_in_loop(t, i);
    t->leap_year = check_leap_year(t->current_year_in_loop);
  }
  if (t->start.periodicity == at_the_end) {
    t->tax_amount = calculate_tax_amount(accrued_total, t->tax_rate);
  }
  if (capitalization) {
    t->end_deposit += accrued_total;
  }
  return accrued_total;
}

void replenishment_or_withdrawal(term *t, date *transaction, int iteration) {
  int first_transaction = 0;
  if (t->start.year == transaction->year) {
    first_transaction = number_of_day(transaction->day, transaction->month) -
                        number_of_day(t->start.day, t->start.month);
  } else {
    first_transaction =
        number_of_day(transaction->day, transaction->month) + t->deadline +
        (365 + t->leap_year) * (transaction->year - t->start.year);
  }
  if (iteration ==
      first_transaction +
          transaction->periodicity * transaction->number_of_transactions) {
    t->start.amount += transaction->amount;
    t->end_deposit += transaction->amount;
    if (transaction->periodicity == once) {
      transaction->number_of_transactions = 1;
    } else {
      transaction->number_of_transactions++;
    }
  }
}

void check_new_year_in_loop(term *t, int iteration) {
  if (iteration ==
      ((t->deadline + 1) + (365 + t->leap_year) * t->number_of_full_365)) {
    t->current_year_in_loop++;
    t->number_of_full_365++;
  }
}

void tax_for_year(term *t, int iteration) {
  if (iteration ==
          ((t->deadline - 30) + (365 + t->leap_year) * t->number_of_full_365) ||
      (iteration == t->current)) {
    t->tax_amount += calculate_tax_amount(t->accrued_year, t->tax_rate);
    t->accrued_year = 0;
  }
}

double calculate_tax_amount(double accrued_interest, double tax_rate) {
  double tax_amount = accrued_interest - without_taxes;
  if (tax_amount > 0) {
    tax_amount = round_two_places(tax_amount * tax_rate * 0.01);
  } else {
    tax_amount = 0;
  }
  return tax_amount;
}

int check_leap_year(int year) { return (year % 4 == 0) ? 1 : 0; }
double round_two_places(double number) { return round(number * 100) / 100; }