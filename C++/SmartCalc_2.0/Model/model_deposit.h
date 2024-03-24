#ifndef CPP3_SMARTCALC_V2_0_1_SRC_MODEL_MODEL_DEPOSIT_H
#define CPP3_SMARTCALC_V2_0_1_SRC_MODEL_MODEL_DEPOSIT_H

#include <cmath>

namespace s21 {

enum Periodicity {
  kONCE = 0,
  kEVERY_DAY = 1,
  kEVERY_WEEK = 7,
  kEVERY_MONTH = 30,
  kEVERY_TWO_MONTHS = 60,
  kEVERY_QUARTER = 91,
  kEVERY_HALF_YEAR = 182,
  kEVERY_YEAR = 365,
  kAT_THE_END = -1,
  kWITHOUT_TAXES = 150000,
};

struct Date {
public:
  Date() = default;
  Date(int d, int m, int y, int p, double a, int num)
      : day(d), month(m), year(y), periodicity(p), amount(a),
        number_of_transactions(num) {}
  int day{};
  int month{};
  int year{};
  int periodicity{};
  double amount{};
  int number_of_transactions{};
};

struct DepositResult {
public:
  DepositResult() = default;
  DepositResult(double a, double t, double e)
      : accrued_interest(a), tax_amount(t), end_deposit(e) {}

  double accrued_interest{};
  double tax_amount{};
  double end_deposit{};
};

class CalcDeposit {
public:
  void set_start_date(Date start) { start_ = start; }
  double get_tax_amount() { return tax_amount_; }
  DepositResult CalculateDeposit(double tax_rate, Date start,
                                 Date first_replenishment,
                                 Date first_withdrawal, double interest_rate,
                                 int capitalization, double current);
  Date *s21_define_replenishment(double r_amount, int day, int month,
                                 int r_year, int periodicity);
  double MonthsToDays(int month_quantity);
  double CalculateAccruedInterest();
  int NumberOfDay(int day_number, int month_number);
  double CalculateTaxAmount(double accrued_interest, double tax_rate);
  int CheckLeapYear(int year);
  void CheckNewYearInLoop(int iteration);
  double RoundTwoPlaces(double number);
  void TaxForYear(int iteration);
  void ReplenishmentOrWithdrawal(Date *transaction, int iteration);
  double TimeForTax();

private:
  int days_in_month_[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  double tax_rate_{};
  double current_{};
  int deadline_{};
  int leap_year_{};
  Date start_;
  Date withdrawals_;
  Date replenishments_;
  int current_year_in_loop_{};
  int number_of_full_365_{};
  double accrued_year_{};
  double tax_amount_{};
  double end_deposit_{};
  double interest_rate_{};
  int capitalization_{};
};

} // namespace s21

#endif // CPP3_SMARTCALC_V2_0_1_SRC_MODEL_MODEL_DEPOSIT_H
