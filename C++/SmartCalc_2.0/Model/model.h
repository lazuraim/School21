#ifndef CPP3_SMARTCALC_V2_0_1_SRC_MODEL_MODEL_H
#define CPP3_SMARTCALC_V2_0_1_SRC_MODEL_MODEL_H

#include <cmath>
#include <iostream>
#include <stack>

#define PI 3.14159265

namespace s21 {

enum OperationType {
  kNUM = 1,
  kX = 2,
  kPLUS = 3,
  kMINUS = 4,
  kMULTI = 5,
  kDIV = 6,
  kLEFT_BRACKET = 7,
  kRIGHT_BRACKET = 8,
  kMOD = 9,
  kPOW = 10,
  kEXP = 11,
  kCOS = 12,
  kSIN = 13,
  kTAN = 14,
  kACOS = 15,
  kASIN = 16,
  kATAN = 17,
  kSQRT = 18,
  kLN = 19,
  kLOG = 20,
};

struct Token {
public:
  int type{};
  int precedence{};
  double value{};

  Token() noexcept = default;
  Token(int t, int p, double v) : type(t), precedence(p), value(v) {}
};

class Model {
public:
  Model() = default;

  const char *get_exp() const { return input_; }
  std::stack<Token> get_result() const { return result_; }
  const char *get_input() const { return input_; }
  void set_input(const char *i) {
    input_ = i;
    size_ = strlen(i);
  }
  double get_x() const { return x_; }
  void set_x(double x) { x_ = x; }

  void ReversedPolishNotation();
  void DefineType(char token);
  void DefineFunctionType(char *function);
  void DefinePrecedence(char token);
  void StackRightBracket();
  bool CheckX(const char *Xpression);
  void PushNumber();
  void PushNumberAndClearArray();
  void MoveOperators();
  void MoveOperatorsAtTheEnd();
  void ReadFunction();
  void Calculate();
  double UnaryCalculation(int operation);
  double BinaryCalculation(int operation);
  std::string Engine(const char *input, const char *X_str, double X);

  int CheckDotErrors(const char *input_string);
  bool CheckDot(char token);
  bool CheckFunction(const char *str);
  void ResetFlags();
  int CheckBracket(char token);
  int CheckOperator(char sym);
  int CheckStr(const char *input_string);

private:
  const char *input_{};
  size_t size_{};
  double x_{};

  int error_{};
  int bracket_{};
  int dot_{};
  char oper_{};
  int operand_{};
  int alpha_{};
  int read_digits_{};
  int read_letters_{};
  char number_[256]{};
  char function_[10]{};
  char fun_names_[10][10] = {"cos(",  "sin(",  "tan(", "acos(", "asin(",
                             "atan(", "sqrt(", "ln(",  "log(",  "mod"};
  bool is_number_ = false;
  int unary_ = 1;
  bool move_done_ = false;
  int current_precedence_{};
  int current_type_{};

  double calculated_{};
  double value_1_{};
  double value_2_{};

  std::stack<Token> result_{};
  std::stack<Token> operators_{};
  std::stack<Token> calc_{};
};

} // namespace s21

#endif // CPP3_SMARTCALC_V2_0_1_SRC_MODEL_MODEL_H
