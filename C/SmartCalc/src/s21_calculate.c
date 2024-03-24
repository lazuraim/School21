#include "s21_SmartCalc.h"

double s21_calculate(struct token **top, double x) {
  double result = 0;
  struct token *stack = NULL;
  double value = 0;
  calc c = {0};
  while (!is_empty(*top)) {
    if ((*top)->type == number) {
      push(&stack, (*top)->value, 0, 0);
    } else if ((*top)->type == 2) {
      push(&stack, x, 0, 0);
    } else {
      if (!is_empty(stack)) {
        if ((*top)->type >= 3 && (*top)->type <= 10) {
          c.value_2 = stack->value;
          if (!is_empty(stack)) {
            pop(&stack);
            c.value_1 = stack->value;
            pop(&stack);
          }
          value = binary_calculation(&c, (*top)->type);
          push(&stack, value, 0, 0);
        } else {
          c.value_1 = stack->value;
          if (!is_empty(stack)) {
            pop(&stack);
          }
          value = unary_calculation(&c, (*top)->type);
          push(&stack, value, 0, 0);
        }
      }
    }
    pop(top);
  }
  if (!is_empty(stack)) {
    result = stack->value;
  }
  free(stack);
  return result;
}

double unary_calculation(calc *c, int operation) {
  double result = 0;
  if (operation == s21_sin) {
    result = sin(c->value_1);
  } else if (operation == s21_cos) {
    result = cos(c->value_1);
  } else if (operation == s21_tan) {
    result = tan(c->value_1);
  } else if (operation == s21_asin) {
    result = asin(c->value_1);
  } else if (operation == s21_acos) {
    result = acos(c->value_1);
  } else if (operation == s21_atan) {
    result = atan(c->value_1);
  } else if (operation == s21_sqrt) {
    result = sqrt(c->value_1);
  } else if (operation == s21_log) {
    result = log10(c->value_1);
  } else if (operation == s21_ln) {
    result = log(c->value_1);
  }
  return result;
}

double binary_calculation(calc *c, int operation) {
  double result = 0;
  if (operation == plus) {
    result = c->value_1 + c->value_2;
  } else if (operation == minus) {
    result = c->value_1 - c->value_2;
  } else if (operation == multiplication) {
    result = c->value_1 * c->value_2;
  } else if (operation == division) {
    result = c->value_1 / c->value_2;
  } else if (operation == s21_mod) {
    result = fmod(c->value_1, c->value_2);
  } else if (operation == power) {
    result = pow(c->value_1, c->value_2);
  }
  return result;
}

double s21_result(char *string, double x) {
  struct token *tmp = s21_parser(string);
  struct token *top = s21_rpn(&tmp);
  double res = s21_calculate(&top, x);
  return res;
}
