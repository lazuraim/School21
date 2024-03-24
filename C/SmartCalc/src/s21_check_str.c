#include "s21_SmartCalc.h"

int s21_check_str(char *input_string) {
  check_str s = {0};
  while (*input_string && s.error == 0) {
    s.bracket += check_bracket(*input_string);
    if (s.oper == 1 && check_operator(*input_string)) {
      s.error = 1;
    }
    s.oper = check_operator(*input_string);
    if (s.dot == 1) {
      s.error = check_dot_errors(input_string);
      s.dot = 0;
    }
    s.dot = check_dot(*input_string);
    if (s.operand) {
      if (check_operator(*input_string) || *input_string == ' ' ||
          *input_string == ')') {
        s.error = 1;
      }
      s.operand = 0;
    }
    if (isalpha(*input_string) && *input_string != 'x') {
      s.alpha = 1;
      s.oper = 1;
    } else if (!isalpha(*input_string) && s.alpha == 1) {
      s.alpha = 0;
      s.operand = 1;
      s.oper = 0;
    }
    input_string++;
  }
  if (s.bracket != 0 || s.fun_res != 0 || s.error > 0) {
    s.error = 1;
  }
  return s.error;
}

int check_operator(char sym) {
  int result = 0;
  char operators[5] = {"+-*/^"};
  for (int i = 0; i < 5 && result == 0; i++) {
    if (sym == operators[i]) {
      result = 1;
    }
  }
  return result;
}

int check_bracket(char token) {
  int result = 0;
  if (token == '(') {
    result = 1;
  } else if (token == ')') {
    result = -1;
  }
  return result;
}

int check_dot(char token) {
  int result = 0;
  if (token == ',' || token == '.') {
    result = 1;
  }
  return result;
}

int check_dot_errors(char *input_string) {
  int error = 0;
  error = !isdigit(*input_string);
  input_string--;
  input_string--;
  error += !isdigit(*input_string);
  input_string++;
  input_string++;
  return error;
}