#ifndef CPP3_SMARTCALC_V2_0_1_SRC_MODEL_MODEL_CREDIT_H
#define CPP3_SMARTCALC_V2_0_1_SRC_MODEL_MODEL_CREDIT_H

#include <cmath>

namespace s21 {

enum CreditType {
  kANNUITY = 0,
  kDIFFERENTIATED = 1,
};

double AnnuityMonth(double credit_amount, double interest_rate, double term);
double DifferentiatedMonth(double credit_amount, double interest_rate,
                           double term, int paid);

} // namespace s21

#endif // CPP3_SMARTCALC_V2_0_1_SRC_MODEL_MODEL_CREDIT_H
