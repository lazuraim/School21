#include "controller.h"

namespace s21 {

std::string Controller::Calculate(const char *input, const char *X_str,
                                  double X) {
  return model->Engine(input, X_str, X);
}

std::string Controller::ResultForGraph(const char *input, double X) {
  std::string result = model->Engine(input, "", X);
  return result;
}

double Controller::CreditCalc(int type, double credit_amount,
                              double interest_rate, double term, int paid) {
  if (type == kANNUITY) {
    return AnnuityMonth(credit_amount, interest_rate, term);
  } else if (type == kDIFFERENTIATED) {
    return DifferentiatedMonth(credit_amount, interest_rate, term, paid);
  }
  return 0;
}

DepositResult Controller::DepositCalc(double tax_rate, Date start,
                                      Date first_replenishment,
                                      Date first_withdrawal,
                                      double interest_rate, int capitalization,
                                      int current) {
  return deposit->CalculateDeposit(tax_rate, start, first_replenishment,
                                   first_withdrawal, interest_rate,
                                   capitalization, current);
}

double Controller::MonthToDays(double term) {
  return deposit->MonthsToDays(term);
}

} // namespace s21
