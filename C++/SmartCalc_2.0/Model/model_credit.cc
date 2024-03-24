#include "model_credit.h"

namespace s21 {

double AnnuityMonth(double credit_amount, double interest_rate, double term) {
  interest_rate = (interest_rate / (12 * 100));
  double annuity_month = credit_amount * interest_rate *
                         (pow(1 + interest_rate, term)) /
                         ((pow(1 + interest_rate, term) - 1));
  return round(annuity_month * 100) / 100;
}

double DifferentiatedMonth(double credit_amount, double interest_rate,
                           double term, int paid) {
  double main_debt = credit_amount / term;
  double percent_sum =
      (credit_amount - main_debt * paid) * ((interest_rate * 0.01) / 12);
  return main_debt + percent_sum;
}

} // namespace s21
