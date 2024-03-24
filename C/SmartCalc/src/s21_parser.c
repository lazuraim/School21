#include "s21_SmartCalc.h"

struct token *s21_parser(char *input_string) {
  struct token *top = NULL;
  size_t len = strlen(input_string);
  parser p = {0};
  if (!s21_check_str(input_string)) {
    while (*input_string) {
      if (*input_string == '-' &&
          ((strlen(input_string) == len) || (p.unary == 1))) {
        unary_minus_set(&top);
        p.unary = 0;
      } else if (isdigit(*input_string) || check_dot(*input_string)) {
        p.number[p.index_of_num_array++] = *input_string;
        p.is_number = 1;
        p.unary = 0;
      } else {
        p.unary = 0;
        push_number_and_clear_array(&top, &p);
        while (isalpha(*input_string) && *input_string != 'x') {
          p.function[p.index_of_function_array++] = *input_string;
          input_string++;
        }
        if (*input_string == '(') {
          p.unary = 1;
        }
        if (p.index_of_function_array != 0) {
          push(&top, 0, define_precedence(p.function[0]),
               define_type_fun(p.function));
          p.index_of_function_array = 0;
        }
        if (!(isdigit(*input_string))) {
          push(&top, 0, define_precedence(*input_string),
               define_type(*input_string));
        } else {
          input_string--;
        }
        memset(p.function, 0, sizeof(p.function));
      }
      if (p.is_number == 1 && strlen(input_string) == 1) {
        push_number(&top, p.number);
      }
      if (*input_string) {
        input_string++;
      }
    }
  }
  return reverse(top);
}

void push_number_and_clear_array(struct token **top, parser *p) {
  if (p->is_number == 1) {
    push_number(top, p->number);
    memset(p->number, 0, sizeof(p->number));
    p->index_of_num_array = 0;
    p->is_number = 0;
  }
}

void push_number(struct token **top, char *number) {
  double value = 0;
  sscanf(number, "%lf", &value);
  push(top, value, 0, 1);
}

void push(struct token **top, double value, int precedence, int type) {
  struct token *new = (struct token *)malloc(sizeof(struct token));
  if (new != NULL) {
    new->value = value;
    new->precedence = precedence;
    new->type = type;
    new->next = *top;
    *top = new;
  }
}

void pop(struct token **top) {
  if (*top != NULL) {
    struct token *tmp = NULL;
    tmp = (*top);
    *top = (*top)->next;
    free(tmp);
  }
}

struct token *reverse(struct token *top) {
  struct token *result = NULL;
  struct token *tmp = NULL;
  while (top) {
    push(&result, top->value, top->precedence, top->type);
    tmp = top;
    top = top->next;
    free(tmp);
  }
  return result;
}

int is_empty(struct token *top) {
  int res = 0;
  if (top == NULL) {
    res = 1;
  }
  return res;
}

int define_type(char token) {
  int type = 0;
  if (token == 'x') {
    type = x;
  } else if (token == '-') {
    type = minus;
  } else if (token == '+') {
    type = plus;
  } else if (token == '*') {
    type = multiplication;
  } else if (token == '/') {
    type = division;
  } else if (token == '(') {
    type = left_bracket;
  } else if (token == ')') {
    type = right_bracket;
  } else if (token == '^') {
    type = power;
  }
  return type;
}

int define_type_fun(char *function) {
  int type = 0;
  if (strcmp(function, "sin") == 0) {
    type = s21_sin;
  } else if (strcmp(function, "asin") == 0) {
    type = s21_asin;
  } else if (strcmp(function, "cos") == 0) {
    type = s21_cos;
  } else if (strcmp(function, "acos") == 0) {
    type = s21_acos;
  } else if (strcmp(function, "tan") == 0) {
    type = s21_tan;
  } else if (strcmp(function, "atan") == 0) {
    type = s21_atan;
  } else if (strcmp(function, "sqrt") == 0) {
    type = s21_sqrt;
  } else if (strcmp(function, "ln") == 0) {
    type = s21_ln;
  } else if (strcmp(function, "log") == 0) {
    type = s21_log;
  } else if (strcmp(function, "mod") == 0) {
    type = s21_mod;
  }
  return type;
}

int define_precedence(char token) {
  int precedence = 0;
  if (token == 'x' || token == '(' || token == ')' || token == '.' ||
      token == ',') {
    precedence = 0;
  } else if (token == '+' || token == '-') {
    precedence = 1;
  } else if (token == '*' || token == '/' || token == 'm') {
    precedence = 2;
  } else if (token == '^') {
    precedence = 3;
  } else {
    precedence = 4;
  }
  return precedence;
}

void unary_minus_set(struct token **top) {
  push(top, 0, 0, 1);
  push(top, 0, 1, 4);
}

void free_stack(struct token **top) {
  if (*top) {
    free_stack(&((*top)->next));
    free(*top);
    *top = NULL;
  }
}
