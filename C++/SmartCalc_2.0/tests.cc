#include <gtest/gtest.h>

#include "Model/Model.cc"
#include "Model/model_credit.cc"
#include "Model/model_deposit.cc"

#define EPS 1e-6

TEST(CheckLine, RPN_x) {
  s21::Model Expression;
  Expression.set_input("x");
  Expression.ReversedPolishNotation();
  std::stack<s21::Token> res = Expression.get_result();
  ASSERT_EQ((res.top()).type, s21::kX);
}

TEST(CheckLine, RPN_basic) {
  s21::Model Expression;
  Expression.set_input("+");
  Expression.ReversedPolishNotation();
  std::stack<s21::Token> res = Expression.get_result();
  ASSERT_EQ((res.top()).type, s21::kPLUS);
  res.pop();
}

TEST(CheckLine, RPN_num) {
  s21::Model Expression;
  Expression.set_input("2+1");
  Expression.ReversedPolishNotation();
  std::stack<s21::Token> res = Expression.get_result();
  ASSERT_EQ((res.top()).type, s21::kPLUS);
  res.pop();
  ASSERT_EQ((res.top()).type, s21::kNUM);
  ASSERT_EQ((res.top()).value, 1);
}

TEST(CheckLine, RPN_num_brackets) {
  s21::Model Expression;
  Expression.set_input("(1+1)");
  Expression.ReversedPolishNotation();
  std::stack<s21::Token> res = Expression.get_result();
  ASSERT_EQ((res.top()).type, s21::kPLUS);
}

TEST(CheckLine, RPN_num_brackets_2) {
  s21::Model Expression;
  Expression.set_input("(1+1)+1");
  Expression.ReversedPolishNotation();
  std::stack<s21::Token> res = Expression.get_result();
  ASSERT_EQ((res.top()).type, s21::kPLUS);
}

TEST(CheckLine, RPN_multi_brackets) {
  s21::Model Expression;
  Expression.set_input("(1*1)*1");
  Expression.ReversedPolishNotation();
  std::stack<s21::Token> res = Expression.get_result();
  ASSERT_EQ((res.top()).type, s21::kMULTI);
}

TEST(CheckLine, RPN_pow_brackets) {
  s21::Model Expression;
  Expression.set_input("(2^1)^2");
  Expression.ReversedPolishNotation();
  std::stack<s21::Token> res = Expression.get_result();
  ASSERT_EQ((res.top()).type, s21::kPOW);
}

TEST(CheckLine, RPN_DIV) {
  s21::Model Expression;
  Expression.set_input("(2-1)-2");
  Expression.ReversedPolishNotation();
  std::stack<s21::Token> res = Expression.get_result();
  ASSERT_EQ((res.top()).type, s21::kMINUS);
}

TEST(CheckLine, RPN_mod) {
  s21::Model Expression;
  Expression.set_input("(2mod1)mod2");
  Expression.ReversedPolishNotation();
  std::stack<s21::Token> res = Expression.get_result();
  ASSERT_EQ((res.top()).type, s21::kMOD);
}

TEST(CheckLine, RPN_unary) {
  s21::Model Expression;
  Expression.set_input("-2+1");
  Expression.ReversedPolishNotation();
  std::stack<s21::Token> res = Expression.get_result();
  ASSERT_EQ((res.top()).type, s21::kPLUS);
  res.pop();
  ASSERT_EQ((res.top()).type, s21::kNUM);
}

TEST(CheckLine, RPN_function) {
  s21::Model Expression;
  Expression.set_input("sin(1)");
  Expression.ReversedPolishNotation();
  std::stack<s21::Token> res = Expression.get_result();
  ASSERT_EQ((res.top()).type, s21::kSIN);
  res.pop();
  ASSERT_EQ((res.top()).type, s21::kNUM);
}

TEST(CheckLine, RPN_function_2) {
  s21::Model Expression;
  Expression.set_input("sin(1)+1");
  Expression.ReversedPolishNotation();
  std::stack<s21::Token> res = Expression.get_result();
  ASSERT_EQ((res.top()).type, s21::kPLUS);
  res.pop();
  ASSERT_EQ((res.top()).type, s21::kNUM);
  res.pop();
  ASSERT_EQ((res.top()).type, s21::kSIN);
  res.pop();
  ASSERT_EQ((res.top()).type, s21::kNUM);
  ASSERT_EQ((res.top()).value, 1);
}

TEST(CheckLine, RPN_function_3) {
  s21::Model Expression;
  Expression.set_input("4mod3");
  Expression.ReversedPolishNotation();
  std::stack<s21::Token> res = Expression.get_result();
  ASSERT_EQ((res.top()).type, s21::kMOD);
  res.pop();
  ASSERT_EQ((res.top()).type, s21::kNUM);
  ASSERT_EQ((res.top()).value, 3);
  res.pop();
  ASSERT_EQ((res.top()).type, s21::kNUM);
  ASSERT_EQ((res.top()).value, 4);
}

TEST(CheckLine, RPN_function_4) {
  s21::Model Expression;
  Expression.set_input("cos(x)");
  Expression.ReversedPolishNotation();
  std::stack<s21::Token> res = Expression.get_result();
  ASSERT_EQ((res.top()).type, s21::kCOS);
  res.pop();
  ASSERT_EQ((res.top()).type, s21::kX);
}

TEST(CheckLine, RPN_function_5) {
  s21::Model Expression;
  Expression.set_input("cos(x)*3+5-sin(10)");
  Expression.ReversedPolishNotation();
  std::stack<s21::Token> res = Expression.get_result();
  ASSERT_EQ((res.top()).type, s21::kMINUS);
  res.pop();
  ASSERT_EQ((res.top()).type, s21::kSIN);
  res.pop();
  ASSERT_EQ((res.top()).type, s21::kNUM);
  ASSERT_EQ((res.top()).value, 10);
  res.pop();
  ASSERT_EQ((res.top()).type, s21::kPLUS);
  res.pop();
  ASSERT_EQ((res.top()).type, s21::kNUM);
  ASSERT_EQ((res.top()).value, 5);
  res.pop();
  ASSERT_EQ((res.top()).type, s21::kMULTI);
  res.pop();
  ASSERT_EQ((res.top()).type, s21::kNUM);
  ASSERT_EQ((res.top()).value, 3);
  res.pop();
  ASSERT_EQ((res.top()).type, s21::kCOS);
  res.pop();
  ASSERT_EQ((res.top()).type, s21::kX);
}

TEST(CheckLine, RPN_function_6) {
  s21::Model Expression;
  Expression.set_input("4.15+6.18");
  Expression.ReversedPolishNotation();
  std::stack<s21::Token> res = Expression.get_result();
  ASSERT_EQ((res.top()).type, s21::kPLUS);
  res.pop();
  ASSERT_EQ((res.top()).type, s21::kNUM);
  ASSERT_EQ((res.top()).value, 6.18);
  res.pop();
  ASSERT_EQ((res.top()).type, s21::kNUM);
  ASSERT_EQ((res.top()).value, 4.15);
}

TEST(CheckLine, RPN_exp) {
  s21::Model Expression;
  Expression.set_input("2e10");
  Expression.ReversedPolishNotation();
  std::stack<s21::Token> res = Expression.get_result();
  ASSERT_EQ((res.top()).type, s21::kEXP);
  res.pop();
  ASSERT_EQ((res.top()).type, s21::kNUM);
  ASSERT_EQ((res.top()).value, 10);
  res.pop();
  ASSERT_EQ((res.top()).type, s21::kNUM);
  ASSERT_EQ((res.top()).value, 2);
}

TEST(CheckLine, checks1) {
  s21::Model Expression;
  Expression.set_input("-0.1");
  Expression.ReversedPolishNotation();
  std::stack<s21::Token> res = Expression.get_result();
  ASSERT_EQ((res.top()).type, s21::kNUM);
  ASSERT_EQ((res.top()).value, -0.1);
}

TEST(CheckLine, Brackets_1) {
  s21::Model Expression;
  Expression.set_input("sin(1*(10^(65/4)))");
  Expression.ReversedPolishNotation();
  std::stack<s21::Token> res = Expression.get_result();
  ASSERT_EQ((res.top()).type, s21::kSIN);
  res.pop();
  ASSERT_EQ((res.top()).type, s21::kMULTI);
  res.pop();
  ASSERT_EQ((res.top()).type, s21::kPOW);
  res.pop();
  ASSERT_EQ((res.top()).type, s21::kDIV);
  res.pop();
  ASSERT_EQ((res.top()).type, s21::kNUM);
  ASSERT_EQ((res.top()).value, 4);
  res.pop();
  ASSERT_EQ((res.top()).type, s21::kNUM);
  ASSERT_EQ((res.top()).value, 65);
  res.pop();
  ASSERT_EQ((res.top()).type, s21::kNUM);
  ASSERT_EQ((res.top()).value, 10);
  res.pop();
  ASSERT_EQ((res.top()).type, s21::kNUM);
  ASSERT_EQ((res.top()).value, 1);
}

TEST(CheckLine, Floating) {
  s21::Model Expression;
  Expression.set_input("4.602736+1");
  Expression.ReversedPolishNotation();
  std::stack<s21::Token> res = Expression.get_result();
  ASSERT_EQ((res.top()).type, s21::kPLUS);
  res.pop();
  ASSERT_EQ((res.top()).type, s21::kNUM);
  ASSERT_EQ((res.top()).value, 1);
  res.pop();
  ASSERT_EQ((res.top()).type, s21::kNUM);
  ASSERT_EQ((res.top()).value, 4.602736);
}

TEST(CheckLine, Brackets_3) {
  s21::Model Expression;
  Expression.set_input("sqrt(x+((3600/6)+3^2))^2");
  Expression.ReversedPolishNotation();
  std::stack<s21::Token> res = Expression.get_result();
  ASSERT_EQ((res.top()).type, s21::kPOW);
  res.pop();
  ASSERT_EQ((res.top()).type, s21::kNUM);
  ASSERT_EQ((res.top()).value, 2);
  res.pop();
  ASSERT_EQ((res.top()).type, s21::kSQRT);
  res.pop();
  ASSERT_EQ((res.top()).type, s21::kPLUS);
  res.pop();
  ASSERT_EQ((res.top()).type, s21::kPLUS);
  res.pop();
  ASSERT_EQ((res.top()).type, s21::kPOW);
  res.pop();
  ASSERT_EQ((res.top()).type, s21::kNUM);
  ASSERT_EQ((res.top()).value, 2);
  res.pop();
  ASSERT_EQ((res.top()).type, s21::kNUM);
  ASSERT_EQ((res.top()).value, 3);
  res.pop();
  ASSERT_EQ((res.top()).type, s21::kDIV);
  res.pop();
  ASSERT_EQ((res.top()).type, s21::kNUM);
  ASSERT_EQ((res.top()).value, 6);
  res.pop();
  ASSERT_EQ((res.top()).type, s21::kNUM);
  ASSERT_EQ((res.top()).value, 3600);
  res.pop();
  ASSERT_EQ((res.top()).type, s21::kX);
}

TEST(CheckLine, Brackets_4) {
  s21::Model Expression;
  Expression.set_input("(x*(-1.0))-((x*(-1.0)))");
  Expression.ReversedPolishNotation();
  std::stack<s21::Token> res = Expression.get_result();
  ASSERT_EQ((res.top()).type, s21::kMINUS);
  res.pop();
  ASSERT_EQ((res.top()).type, s21::kMULTI);
  res.pop();
  ASSERT_EQ((res.top()).type, s21::kNUM);
  ASSERT_EQ((res.top()).value, -1);
  res.pop();
  ASSERT_EQ((res.top()).type, s21::kX);
  res.pop();
  ASSERT_EQ((res.top()).type, s21::kMULTI);
  res.pop();
  ASSERT_EQ((res.top()).type, s21::kNUM);
  ASSERT_EQ((res.top()).value, -1);
  res.pop();
  ASSERT_EQ((res.top()).type, s21::kX);
  res.pop();
}

TEST(CheckLine, Brackets_5) {
  s21::Model Expression;
  Expression.set_input("8/(-3.6^12)");
  Expression.ReversedPolishNotation();
  std::stack<s21::Token> res = Expression.get_result();
  ASSERT_EQ((res.top()).type, s21::kDIV);
  res.pop();
  ASSERT_EQ((res.top()).type, s21::kPOW);
  res.pop();
  ASSERT_EQ((res.top()).type, s21::kNUM);
  ASSERT_EQ((res.top()).value, 12);
  res.pop();
  ASSERT_EQ((res.top()).type, s21::kNUM);
  ASSERT_EQ((res.top()).value, -3.6);
  res.pop();
  ASSERT_EQ((res.top()).type, s21::kNUM);
  ASSERT_EQ((res.top()).value, 8);
  res.pop();
}

TEST(CheckLine, CheckX) {
  s21::Model Expression;
  bool res = Expression.CheckX("123");
  ASSERT_EQ(res, true);
}

TEST(CheckLine, CheckX_2) {
  s21::Model Expression;
  bool res = Expression.CheckX("1df");
  ASSERT_EQ(res, false);
}

TEST(CheckLine, CheckX_3) {
  s21::Model Expression;
  bool res = Expression.CheckX("1.143");
  ASSERT_EQ(res, true);
}

TEST(CheckLine, CheckStr) {
  s21::Model Expression;
  int res = Expression.CheckStr("8/(-3.6^12)");
  ASSERT_EQ(res, 0);
}

TEST(CheckLine, CheckStr_2) {
  s21::Model Expression;
  int res = Expression.CheckStr("-1+1*-1");
  ASSERT_EQ(res, 0);
}

TEST(CheckLine, CheckStr_3) {
  s21::Model Expression;
  int res = Expression.CheckStr("1*^3");
  ASSERT_EQ(res, 1);
}

TEST(CheckLine, CheckStr_4) {
  s21::Model Expression;
  int res = Expression.CheckStr("cos(x))");
  ASSERT_EQ(res, 1);
}

TEST(CheckLine, CheckStr_5) {
  s21::Model Expression;
  int res = Expression.CheckStr("cos(x)+x");
  ASSERT_EQ(res, 0);
}

TEST(Calculation, Calculate_1) {
  s21::Model Expression;
  EXPECT_NEAR(std::stod(Expression.Engine("1+1", "", 0)), 2, EPS);
}

TEST(Calculation, Calculate_2) {
  s21::Model Expression;
  EXPECT_NEAR(std::stod(Expression.Engine("42mod21", "", 0)), 0, EPS);
}

TEST(Calculation, Calculate_3) {
  s21::Model Expression;
  EXPECT_NEAR(std::stod(Expression.Engine("cos(0)", "", 0)), 1, EPS);
}

TEST(Calculation, Calculate_4) {
  s21::Model Expression;
  EXPECT_NEAR(std::stold(Expression.Engine("tan(10)+sin(10)", "", 0)),
              0.1043397, EPS);
}

TEST(Calculation, Calculate_5) {
  s21::Model Expression;
  EXPECT_NEAR(std::stod(Expression.Engine("sqrt(16+((3600/6)+3^2))", "", 0)),
              25, EPS);
}

TEST(Calculation, Calculate_6) {
  s21::Model Expression;
  EXPECT_NEAR(std::stod(Expression.Engine("sqrt(x+((3600/6)+3^2))^2", "", 16)),
              625, EPS);
}

TEST(Calculation, Calculate_7) {
  s21::Model Expression;
  EXPECT_NEAR(std::stod(Expression.Engine("(x*(-1.0))-((x*(-1.0)))", "", 16)),
              0, EPS);
}

TEST(Calculation, Calculate_8) {
  s21::Model Expression;
  EXPECT_NEAR(std::stod(Expression.Engine("8/(-3.6^12)", "", 0)), 0.00000168834,
              EPS);
}

TEST(Calculation, Calculate_9) {
  s21::Model Expression;
  EXPECT_NEAR(std::stod(Expression.Engine("sin(cos(3+9)^3)", "", 0)),
              0.56538467272, EPS);
}

TEST(Calculation, Calculate_10) {
  s21::Model Expression;
  EXPECT_NEAR(std::stod(Expression.Engine("2^2^2", "", 0)), 16, EPS);
}

TEST(Calculation, Calculate_11) {
  s21::Model Expression;
  EXPECT_NEAR(std::stod(Expression.Engine("2*3", "", 0)), 6, EPS);
}

TEST(Calculation, Calculate_12) {
  s21::Model Expression;
  EXPECT_NEAR(std::stod(Expression.Engine("3/6", "", 0)), 0.5, EPS);
}

TEST(Calculation, Calculate_13) {
  s21::Model Expression;
  EXPECT_NEAR(std::stod(Expression.Engine("sin(-10)", "", 0)), sin(-10), EPS);
}

TEST(Calculation, Calculate_14) {
  s21::Model Expression;
  EXPECT_NEAR(std::stod(Expression.Engine("sqrt(16+((3600/6)+3^2))", "", 0)),
              25, EPS);
}

TEST(Calculation, Calculate_15) {
  s21::Model Expression;
  EXPECT_NEAR(std::stod(Expression.Engine("sqrt(x+((3600/6)+3^2))^2", "", 16)),
              625, EPS);
}

TEST(Calculation, Calculate_16) {
  s21::Model Expression;
  EXPECT_NEAR(std::stod(Expression.Engine("sqrt(16+(600+3^2))", "", 0)), 25,
              EPS);
}

TEST(Calculation, Calculate_17) {
  s21::Model Expression;
  EXPECT_NEAR(std::stod(Expression.Engine("3*(-1+(-1+7.0))", "", 0)), 15, EPS);
}

TEST(Calculation, Calculate_18) {
  s21::Model Expression;
  EXPECT_NEAR(std::stod(Expression.Engine("(x*(-1.0))-((x*(-1.0)))", "", 16)),
              0, EPS);
}

TEST(Calculation, Calculate_19) {
  s21::Model Expression;
  EXPECT_NEAR(std::stod(Expression.Engine("sin(cos(3+9)^3)", "", 0)),
              sin(pow(cos(3 + 9), 3)), EPS);
}

TEST(Calculation, Calculate_20) {
  s21::Model Expression;
  EXPECT_NEAR(std::stod(Expression.Engine("8/(-3.6^12)", "", 0)),
              8 / (pow(-3.6, 12)), EPS);
}

TEST(Calculation, Calculate_21) {
  s21::Model Expression;
  EXPECT_NEAR(std::stod(Expression.Engine("log(100)", "", 0)), 2, EPS);
}

TEST(Calculation, Calculate_22) {
  s21::Model Expression;
  EXPECT_NEAR(std::stod(Expression.Engine("ln(10)", "", 0)), 2.30258509299,
              EPS);
}

TEST(Calculation, Calculate_23) {
  s21::Model Expression;
  EXPECT_NEAR(std::stod(Expression.Engine("asin(-0.5)", "", 0)), asin(-0.5),
              EPS);
}

TEST(Calculation, Calculate_24) {
  s21::Model Expression;
  EXPECT_NEAR(std::stod(Expression.Engine("acos(-0.5)", "", 0)), acos(-0.5),
              EPS);
}

TEST(Calculation, Calculate_25) {
  s21::Model Expression;
  EXPECT_NEAR(std::stod(Expression.Engine("atan(1)", "", 0)), atan(1), EPS);
}

TEST(Calculation, Calculate_26) {
  s21::Model Expression;
  EXPECT_NEAR(std::stod(Expression.Engine("2e3", "", 0)), 2000, EPS);
}

TEST(Calculation, Calculate_27) {
  s21::Model Expression;
  EXPECT_NEAR(std::stod(Expression.Engine("2e-3", "", 0)), 0.002, EPS);
}

TEST(Calculation, Calculate_28) {
  s21::Model Expression;
  EXPECT_EQ(Expression.Engine("2e-3))", "", 0), "error");
}

TEST(Calculation, Credit_Annuity_1) {
  double result = s21::AnnuityMonth(1000000, 5, 24);
  EXPECT_NEAR(result, 43871.39, EPS);
}

TEST(Calculation, Credit_Annuity_2) {
  double result = s21::AnnuityMonth(10000000, 5, 24);
  EXPECT_NEAR(result, 438713.90, EPS);
}

TEST(Calculation, Credit_Annuity_3) {
  double result = s21::AnnuityMonth(1000000, 5, 50 * 12);
  EXPECT_NEAR(result, 4541.39, EPS);
}

TEST(Calculation, Credit_Annuity_4) {
  double result = s21::AnnuityMonth(1000000000, 5, 24 * 12);
  EXPECT_NEAR(result, 5968975.12, EPS);
}

TEST(Calculation, Credit_Annuity_5) {
  double result = s21::AnnuityMonth(4000000000, 45, 7);
  EXPECT_NEAR(result, 660294782.41, EPS);
}

TEST(Calculation, Credit_Differentiated_1) {
  double result = s21::DifferentiatedMonth(1000000, 12, 24, 0);
  EXPECT_NEAR(result, 51666.67, 1e-2);
}

TEST(Calculation, Credit_Differentiated_2) {
  double result = s21::DifferentiatedMonth(1000000, 12, 24, 1);
  EXPECT_NEAR(result, 51250.00, 1e-2);
}

TEST(Calculation, Credit_Differentiated_3) {
  double result = s21::DifferentiatedMonth(1000000, 12, 24, 2);
  EXPECT_NEAR(result, 50833.33, 1e-2);
}

TEST(Calculation, Credit_Differentiated_4) {
  double result = s21::DifferentiatedMonth(1000000, 12, 24, 3);
  EXPECT_NEAR(result, 50416.67, 1e-2);
}

TEST(Calculation, Credit_Differentiated_5) {
  double result = s21::DifferentiatedMonth(10000000, 12, 24 * 12, 1);
  EXPECT_NEAR(result, 134375.00, 1e-2);
}

TEST(Calculation, Deposit_1) {
  s21::CalcDeposit obj{};
  s21::Date first_replenishment = s21::Date();
  s21::Date first_withdrawal = s21::Date();

  s21::Date start = s21::Date(21, 6, 2023, s21::kEVERY_DAY, 1000000, 0);
  obj.set_start_date(start);
  s21::DepositResult res =
      obj.CalculateDeposit(13, start, first_replenishment, first_withdrawal, 5,
                           1, obj.MonthsToDays(5));
  EXPECT_NEAR(res.accrued_interest, 21178.63, 1e-2);
  EXPECT_NEAR(res.tax_amount, 0, 1e-2);
}

TEST(Calculation, Deposit_2) {
  s21::CalcDeposit obj{};
  s21::Date first_replenishment = s21::Date();
  s21::Date first_withdrawal = s21::Date();
  s21::Date start = s21::Date(21, 6, 2023, s21::kEVERY_DAY, 1000000, 0);
  s21::DepositResult res = obj.CalculateDeposit(13, start, first_replenishment,
                                                first_withdrawal, 5, 1, 120);
  EXPECT_NEAR(res.accrued_interest, 16573.08, 1e-3);
  EXPECT_NEAR(res.tax_amount, 0, 1e-3);
}

TEST(Calculation, Deposit_3) {
  s21::CalcDeposit obj{};
  s21::Date first_replenishment = s21::Date();
  s21::Date first_withdrawal = s21::Date();
  s21::Date start = s21::Date(21, 6, 2023, s21::kEVERY_DAY, 1000000, 0);
  obj.set_start_date(start);
  s21::DepositResult res =
      obj.CalculateDeposit(13, start, first_replenishment, first_withdrawal, 5,
                           1, obj.MonthsToDays(50));
  EXPECT_NEAR(res.accrued_interest, 231634.22, 1e-2);
  EXPECT_NEAR(res.tax_amount, 0, 1e-2);
}

TEST(Calculation, Deposit_4) {
  s21::CalcDeposit obj{};
  s21::Date first_replenishment = s21::Date();
  s21::Date first_withdrawal = s21::Date();
  s21::Date start = s21::Date(23, 6, 2023, s21::kONCE, 500000, 0);
  obj.set_start_date(start);
  s21::DepositResult res =
      obj.CalculateDeposit(13, start, first_replenishment, first_withdrawal, 5,
                           0, obj.MonthsToDays(5));
  EXPECT_NEAR(res.accrued_interest, 10478.97, 1e-2);
  EXPECT_NEAR(res.tax_amount, 0, 1e-2);
}

TEST(Calculation, Deposit_5) {
  s21::CalcDeposit obj{};
  s21::Date first_replenishment = s21::Date();
  s21::Date first_withdrawal = s21::Date();
  s21::Date start = s21::Date(21, 6, 2023, s21::kEVERY_WEEK, 50000000, 0);
  obj.set_start_date(start);
  s21::DepositResult res =
      obj.CalculateDeposit(13, start, first_replenishment, first_withdrawal, 5,
                           1, obj.MonthsToDays(12 * 5));
  EXPECT_NEAR(res.accrued_interest, 14198222.00, 1e-1);
  EXPECT_NEAR(res.tax_amount, 1728768.86, 1e-1);
}

TEST(Calculation, Deposit_6) {
  s21::CalcDeposit obj{};
  s21::Date first_replenishment =
      s21::Date(25, 7, 2024, s21::kEVERY_YEAR, 10000, 0);
  s21::Date first_withdrawal = s21::Date();
  s21::Date start = s21::Date(25, 6, 2023, s21::kEVERY_DAY, 350000, 0);
  obj.set_start_date(start);
  s21::DepositResult res =
      obj.CalculateDeposit(13, start, first_replenishment, first_withdrawal, 5,
                           1, obj.MonthsToDays(12));
  EXPECT_NEAR(res.accrued_interest, 17969.7, 1e-1);
  EXPECT_NEAR(res.tax_amount, 0, 1e-1);
}

TEST(Calculation, Deposit_7) {
  s21::CalcDeposit obj{};
  s21::Date first_replenishment = s21::Date();
  s21::Date first_withdrawal = s21::Date(25, 8, 2023, s21::kONCE, -20000, 0);
  s21::Date start = s21::Date(25, 6, 2023, s21::kEVERY_DAY, 350000, 0);
  obj.set_start_date(start);
  s21::DepositResult res =
      obj.CalculateDeposit(13, start, first_replenishment, first_withdrawal, 5,
                           1, obj.MonthsToDays(15));
  EXPECT_NEAR(res.accrued_interest, 21507.68, 1e+1);
  EXPECT_NEAR(res.tax_amount, 0, 1e-1);
}

TEST(Calculation, Deposit_8) {
  s21::CalcDeposit obj{};
  s21::Date first_replenishment =
      s21::Date(25, 8, 2023, s21::kEVERY_YEAR, -20000, 0);
  s21::Date first_withdrawal = s21::Date();
  s21::Date start = s21::Date(24, 6, 2023, s21::kAT_THE_END, 5000000, 0);
  obj.set_start_date(start);
  s21::DepositResult res =
      obj.CalculateDeposit(13, start, first_replenishment, first_withdrawal, 5,
                           1, obj.MonthsToDays(12 * 4));
  EXPECT_NEAR(res.accrued_interest, 994510.55, 4000);
  EXPECT_NEAR(res.tax_amount, 108486.37, 1500);
}

TEST(Calculation, Deposit_9) {
  s21::CalcDeposit obj{};
  s21::Date first_replenishment = s21::Date();
  s21::Date first_withdrawal = s21::Date();
  s21::Date start = s21::Date(24, 6, 2023, s21::kAT_THE_END, 5000000, 0);
  obj.set_start_date(start);
  s21::DepositResult res =
      obj.CalculateDeposit(13, start, first_replenishment, first_withdrawal, 5,
                           1, obj.MonthsToDays(12 * 4));
  EXPECT_NEAR(res.accrued_interest, 1000000.0, 1e+1);
  EXPECT_NEAR(res.tax_amount, 109200.0, 1500);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
