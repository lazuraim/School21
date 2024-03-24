#include "model_deposit.h"

namespace s21 {

DepositResult CalcDeposit::CalculateDeposit(double tax_rate, Date start,
                                            Date first_replenishment,
                                            Date first_withdrawal,
                                            double interest_rate,
                                            int capitalization,
                                            double current) {
  tax_rate_ = tax_rate;
  start_ = start;
  replenishments_ = first_replenishment;
  withdrawals_ = first_withdrawal;
  current_ = current;
  interest_rate_ = interest_rate;
  capitalization_ = capitalization;
  deadline_ = (365 + CheckLeapYear(start_.year)) -
              NumberOfDay(start_.day, start_.month);
  double accrued_interest = CalculateAccruedInterest();
  DepositResult res =
      DepositResult(accrued_interest, tax_amount_, end_deposit_);
  tax_amount_ = 0;
  end_deposit_ = 0;
  return res;
}

double CalcDeposit::MonthsToDays(int month_quantity) {
  double days = 0;
  int year = start_.year;
  int month = start_.month;
  for (int i = 0; i < month_quantity; ++i) {
    if (month == 12) {
      ++year;
      days += CheckLeapYear(year);
    }
    days += days_in_month_[month];
    ++month;
    if (month % 12 == 0) {
      month = 12;
    } else {
      month = month % 12;
    }
  }
  return days;
}

int CalcDeposit::NumberOfDay(int day_number, int month_number) {
  int days = 0;
  for (int i = 1; i < month_number; i++) {
    days += days_in_month_[i];
  }
  days += day_number;
  return days;
}

double CalcDeposit::CalculateAccruedInterest() {
  double accrued_interest = 0, accrued_term = 0, accrued_total = 0;
  current_year_in_loop_ = start_.year;
  leap_year_ = CheckLeapYear(current_year_in_loop_);
  end_deposit_ = start_.amount;
  for (int i = 1; i < current_ + 1; ++i) {
    if (replenishments_.amount != 0) {
      ReplenishmentOrWithdrawal(&(replenishments_), i);
    }
    if (withdrawals_.amount != 0) {
      ReplenishmentOrWithdrawal(&(withdrawals_), i);
    }
    accrued_interest =
        (start_.amount * interest_rate_ / (365 + leap_year_)) / 100;

    if (start_.periodicity == kEVERY_DAY || !capitalization_) {
      accrued_interest = RoundTwoPlaces(accrued_interest);
    }
    accrued_term += accrued_interest;
    accrued_total += accrued_interest;
    accrued_year_ += accrued_interest;
    TaxForYear(i);
    if (capitalization_ && start_.periodicity != kAT_THE_END) {
      if ((i % start_.periodicity) == 0) {
        start_.amount += RoundTwoPlaces(accrued_term);
        accrued_term = 0;
      }
    }
    CheckNewYearInLoop(i);
    leap_year_ = CheckLeapYear(current_year_in_loop_);
  }
  if (start_.periodicity == kAT_THE_END) {
    tax_amount_ = CalculateTaxAmount(accrued_total, tax_rate_);
  }
  end_deposit_ += accrued_total;
  return accrued_total;
}

void CalcDeposit::ReplenishmentOrWithdrawal(Date *transaction, int iteration) {
  int first_transaction = 0;
  if (start_.year == transaction->year) {
    first_transaction = NumberOfDay(transaction->day, transaction->month) -
                        NumberOfDay(start_.day, start_.month);
  } else {
    first_transaction = NumberOfDay(transaction->day, transaction->month) +
                        deadline_ +
                        (365 + leap_year_) * (transaction->year - start_.year);
  }
  if (iteration ==
      first_transaction +
          transaction->periodicity * transaction->number_of_transactions) {
    start_.amount += transaction->amount;
    end_deposit_ += transaction->amount;
    if (transaction->periodicity == kONCE) {
      transaction->number_of_transactions = 1;
    } else {
      transaction->number_of_transactions++;
    }
  }
}

void CalcDeposit::CheckNewYearInLoop(int iteration) {
  if (iteration ==
      ((deadline_ + 1) + (365 + leap_year_) * number_of_full_365_)) {
    ++current_year_in_loop_;
    ++number_of_full_365_;
  }
}

double CalcDeposit::TimeForTax() {
  return (deadline_ - 30) + (365 + leap_year_) * number_of_full_365_;
}

void CalcDeposit::TaxForYear(int iteration) {
  if (iteration == TimeForTax() || (iteration == current_)) {
    tax_amount_ += CalculateTaxAmount(accrued_year_, tax_rate_);
    accrued_year_ = 0;
  }
}

double CalcDeposit::CalculateTaxAmount(double accrued_interest,
                                       double tax_rate) {
  double tax = accrued_interest - kWITHOUT_TAXES;
  if (tax > 0) {
    tax = RoundTwoPlaces(tax * tax_rate * 0.01);
  } else {
    tax = 0;
  }
  return tax;
}

int CalcDeposit::CheckLeapYear(int year) { return (year % 4 == 0) ? 1 : 0; }

double CalcDeposit::RoundTwoPlaces(double number) {
  return round(number * 100) / 100;
}

} // namespace s21
