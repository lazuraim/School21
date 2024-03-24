#ifndef CPP3_SMARTCALC_V2_0_1_SRC_CONTROLLER_H
#define CPP3_SMARTCALC_V2_0_1_SRC_CONTROLLER_H

#include "Model/model.h"
#include "Model/model_credit.h"
#include "Model/model_deposit.h"
#include <QString>

namespace s21 {

class Controller {

public:
  Controller(Model *m, CalcDeposit *d) : model(m), deposit(d) {}

  std::string Calculate(const char *input, const char *X_str, double X);
  std::string ResultForGraph(const char *input, double X);
  double CreditCalc(int type, double credit_amount, double interest_rate,
                    double term, int paid);
  DepositResult DepositCalc(double tax_rate, Date start,
                            Date first_replenishment, Date first_withdrawal,
                            double interest_rate, int capitalization,
                            int current);
  double MonthToDays(double term);

private:
  Model *model;
  CalcDeposit *deposit;
};

} // namespace s21

#endif // CPP3_SMARTCALC_V2_0_1_SRC_CONTROLLER_H
