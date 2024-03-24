#include "model.h"

namespace s21 {

bool Model::CheckX(const char *Xpression) {
  bool dot = 0;
  for (size_t i = 0; i < strlen(Xpression); ++i) {
    if (!isdigit(Xpression[i])) {
      if (Xpression[i] == '.' && dot == false) {
        dot = true;
      } else {
        return false;
      }
    }
  }
  return true;
}

void Model::DefineType(char token) {
  if (token == 'x') {
    current_type_ = s21::kX;
  } else if (token == '-') {
    current_type_ = s21::kMINUS;
  } else if (token == '+') {
    current_type_ = s21::kPLUS;
  } else if (token == '*') {
    current_type_ = s21::kMULTI;
  } else if (token == '/') {
    current_type_ = s21::kDIV;
  } else if (token == '(') {
    current_type_ = s21::kLEFT_BRACKET;
  } else if (token == ')') {
    current_type_ = s21::kRIGHT_BRACKET;
  } else if (token == '^') {
    current_type_ = s21::kPOW;
  }
}

void Model::DefineFunctionType(char *function) {
  if (strcmp(function, "sin") == 0) {
    current_type_ = s21::kSIN;
  } else if (strcmp(function, "asin") == 0) {
    current_type_ = s21::kASIN;
  } else if (strcmp(function, "cos") == 0) {
    current_type_ = s21::kCOS;
  } else if (strcmp(function, "acos") == 0) {
    current_type_ = s21::kACOS;
  } else if (strcmp(function, "tan") == 0) {
    current_type_ = s21::kTAN;
  } else if (strcmp(function, "atan") == 0) {
    current_type_ = s21::kATAN;
  } else if (strcmp(function, "sqrt") == 0) {
    current_type_ = s21::kSQRT;
  } else if (strcmp(function, "ln") == 0) {
    current_type_ = s21::kLN;
  } else if (strcmp(function, "log") == 0) {
    current_type_ = s21::kLOG;
  } else if (strcmp(function, "mod") == 0) {
    current_type_ = s21::kMOD;
  } else if (strcmp(function, "e") == 0) {
    current_type_ = s21::kEXP;
  }
}

void Model::DefinePrecedence(char token) {
  if (token == 'x' || token == '(' || token == ')' || token == '.' ||
      token == ',') {
    current_precedence_ = 0;
  } else if (token == '+' || token == '-') {
    current_precedence_ = 1;
  } else if (token == '*' || token == '/' || token == 'm') {
    current_precedence_ = 2;
  } else if (token == '^' || token == 'e') {
    current_precedence_ = 3;
  } else {
    current_precedence_ = 4;
  }
}

void Model::ReversedPolishNotation() {
  while (*input_) {
    DefinePrecedence(*input_);
    DefineType(*input_);
    if (*input_ == '-' && ((strlen(input_) == size_) || unary_ == 2)) {
      unary_ = -1;
    } else if (isdigit(*input_) || *input_ == '.') {
      if (unary_ == -1) {
        number_[read_digits_++] = '-';
      }
      number_[read_digits_++] = *input_;
      is_number_ = true;
      unary_ = 1;
    } else if (*input_ == 'x') {
      result_.push(Token(current_type_, 1, 0));
      unary_ = 1;
    } else {
      PushNumberAndClearArray();
      ReadFunction();
      is_number_ = false;
      unary_ = 1;
      if (*input_ == '(' || *input_ == 'e' || CheckOperator(*input_))
        unary_ = 2;
      if (*input_ == ')') {
        StackRightBracket();
      } else if (*input_ == '(' || operators_.empty() ||
                 current_precedence_ > operators_.top().precedence ||
                 (current_type_ == kPOW && operators_.top().type == kPOW)) {
        operators_.push(Token(current_type_, current_precedence_, 0));
      } else if (!operators_.empty() &&
                 current_precedence_ <= operators_.top().precedence) {
        MoveOperators();
      }
      move_done_ = false;
    }
    if (is_number_ && strlen(input_) == 1)
      PushNumberAndClearArray();
    ++input_;
  }
  MoveOperatorsAtTheEnd();
}

void Model::ReadFunction() {
  while (isalpha(*input_) && *input_ != 'x') {
    function_[read_letters_++] = *input_;
    ++input_;
  }
  if (read_letters_) {
    function_[read_letters_] = '\0';
    read_letters_ = 0;
    --input_;
    DefineFunctionType(function_);
    DefinePrecedence(function_[0]);
  }
  memset(function_, 0, sizeof(function_));
}

void Model::MoveOperators() {
  Token tmp = Token(current_type_, current_precedence_, 0);
  while (!operators_.empty() && move_done_ == false) {
    if (current_precedence_ <= operators_.top().precedence) {
      result_.push(Token(operators_.top().type, operators_.top().precedence,
                         operators_.top().value));
      operators_.pop();
    } else {
      move_done_ = true;
    }
  }
  operators_.push(tmp);
}

void Model::MoveOperatorsAtTheEnd() {
  while (!operators_.empty()) {
    if (operators_.top().type != 7) {
      result_.push(Token(operators_.top().type, operators_.top().precedence,
                         operators_.top().value));
    }
    operators_.pop();
  }
}

void Model::PushNumber() {
  double value = 0;
  sscanf(number_, "%lf", &value);
  result_.push(Token(1, 0, value));
  unary_ = 1;
}

void Model::PushNumberAndClearArray() {
  if (is_number_) {
    PushNumber();
    memset(number_, 0, sizeof(number_));
    read_digits_ = 0;
    is_number_ = false;
  }
}

void Model::StackRightBracket() {
  while (operators_.top().type != 7 && !operators_.empty()) {
    if (operators_.top().type != 7) {
      result_.push(Token(operators_.top().type, operators_.top().precedence,
                         operators_.top().value));
    }
    operators_.pop();
  }
  if (!operators_.empty()) {
    operators_.pop();
  }
}

void InsertAtBottom(std::stack<Token> &s, Token item) {
  if (s.empty()) {
    s.push(item);
    return;
  }
  Token top = s.top();
  s.pop();
  InsertAtBottom(s, item);
  s.push(top);
}

void ReverseStack(std::stack<Token> &s) {
  if (s.empty())
    return;
  Token item = s.top();
  s.pop();
  ReverseStack(s);
  InsertAtBottom(s, item);
}

void Model::Calculate() {
  ReverseStack(result_);
  double value = 0;
  while (!result_.empty()) {
    if (result_.top().type == kNUM) {
      calc_.push(Token(0, 0, result_.top().value));
    } else if (result_.top().type == kX) {
      calc_.push(Token(0, 0, x_));
    } else {
      if (!calc_.empty()) {
        if (result_.top().type >= 3 && result_.top().type <= 11) {
          value_2_ = calc_.top().value;
          calc_.pop();
          if (!calc_.empty()) {
            value_1_ = calc_.top().value;
            if (!calc_.empty())
              calc_.pop();
          }
          value = BinaryCalculation(result_.top().type);
          calc_.push(Token(0, 0, value));
        } else {
          value_1_ = calc_.top().value;
          if (!calc_.empty()) {
            calc_.pop();
          }
          value = UnaryCalculation(result_.top().type);
          calc_.push(Token(0, 0, value));
        }
      }
    }
    result_.pop();
  }
  if (!calc_.empty()) {
    calculated_ = calc_.top().value;
  }
}

double Model::UnaryCalculation(int operation) {
  double result = 0;
  if (operation == s21::kSIN) {
    result = sin(value_1_);
  } else if (operation == s21::kCOS) {
    result = cos(value_1_);
  } else if (operation == s21::kTAN) {
    result = tan(value_1_);
  } else if (operation == s21::kASIN) {
    result = asin(value_1_);
  } else if (operation == s21::kACOS) {
    result = acos(value_1_);
  } else if (operation == s21::kATAN) {
    result = atan(value_1_);
  } else if (operation == s21::kSQRT) {
    result = sqrt(value_1_);
  } else if (operation == s21::kLOG) {
    result = log10(value_1_);
  } else if (operation == s21::kLN) {
    result = log(value_1_);
  }
  return result;
}

double Model::BinaryCalculation(int operation) {
  double result = 0;
  if (operation == s21::kPLUS) {
    result = value_1_ + value_2_;
  } else if (operation == s21::kMINUS) {
    result = value_1_ - value_2_;
  } else if (operation == s21::kMULTI) {
    result = value_1_ * value_2_;
  } else if (operation == s21::kDIV) {
    result = value_1_ / value_2_;
  } else if (operation == s21::kMOD) {
    result = fmod(value_1_, value_2_);
  } else if (operation == s21::kPOW) {
    result = pow(value_1_, value_2_);
  } else if (operation == s21::kEXP) {
    result = value_1_ * pow(10, value_2_);
  }
  return result;
}

std::string Model::Engine(const char *input, const char *X_str, double X) {
  if (CheckStr(input) || !CheckX(X_str)) {
    return "error";
  } else {
    input_ = input;
    size_ = strlen(input_);
    x_ = X;
    ReversedPolishNotation();
    Calculate();
    return std::to_string(calculated_);
  }
}

void Model::ResetFlags() {
  error_ = 0;
  bracket_ = 0;
  alpha_ = 0;
}

int Model::CheckStr(const char *input_string) {
  ResetFlags();
  while (*input_string && error_ == 0) {
    bracket_ += CheckBracket(*input_string);
    if (oper_ != '\0' &&
        (CheckOperator(*input_string) && *input_string != '-')) {
      error_ = 1;
    }
    oper_ = CheckOperator(*input_string);
    if (dot_) {
      error_ = CheckDotErrors(input_string);
      dot_ = 0;
    }
    dot_ = CheckDot(*input_string);
    if (isalpha(*input_string) && *input_string != 'x' &&
        *input_string != 'e') {
      function_[read_letters_++] = *input_string;
      alpha_ = 1;
      oper_ = *input_string;
    } else if (!isalpha(*input_string) && alpha_ == 1) {
      if (*input_string == '(')
        function_[read_letters_++] = *input_string;
      error_ += CheckFunction(function_);
      alpha_ = 0;
      read_letters_ = 0;
      operand_ = 1;
      oper_ = '\0';
      memset(function_, 0, sizeof(function_));
    }
    ++input_string;
  }
  if (bracket_ || error_ > 0 || alpha_) {
    error_ = 1;
  }
  return error_;
}

bool Model::CheckFunction(const char *str) {
  int result = true;
  for (int i = 0; i < 10 && result != 0; i++) {

    result = strcmp(str, fun_names_[i]);
  }
  return result;
}

int Model::CheckOperator(char sym) {
  int result = 0;
  char operators[7] = {"+-*/^e"};
  for (int i = 0; i < 6 && result == 0; i++) {
    if (sym == operators[i]) {
      result = 1;
    }
  }
  return result;
}

int Model::CheckBracket(char token) {
  int result = 0;
  if (token == '(') {
    result = 1;
  } else if (token == ')') {
    result = -1;
  }
  return result;
}

bool Model::CheckDot(char token) { return token == '.' ? true : false; }

int Model::CheckDotErrors(const char *input_string) {
  int error = 0;
  error = !isdigit(*input_string);
  --input_string;
  --input_string;
  error += !isdigit(*input_string);
  ++input_string;
  ++input_string;
  return error;
}

} // namespace s21
