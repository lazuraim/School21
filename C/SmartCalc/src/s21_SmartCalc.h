#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct token {
  double value;
  int precedence;
  struct token *next;
  int type;
  int oper;
};

typedef struct {
  int error;
  int bracket;
  int dot;
  int oper;
  int index;
  int fun_res;
  int operand;
  int alpha;
} check_str;

typedef struct {
  int index_of_function_array;
  int index_of_num_array;
  int unary;
  int is_number;
  char number[256];
  char function[10];
} parser;

typedef struct {
  double value_1;
  double value_2;
} calc;

enum {
  number = 1,
  x = 2,
  plus = 3,
  minus = 4,
  multiplication = 5,
  division = 6,
  left_bracket = 7,
  right_bracket = 8,
  s21_mod = 9,
  power = 10,
  s21_cos = 11,
  s21_sin = 12,
  s21_tan = 13,
  s21_acos = 14,
  s21_asin = 15,
  s21_atan = 16,
  s21_sqrt = 17,
  s21_ln = 18,
  s21_log = 19,
};

int s21_check_str(char *input_string);
int check_fun(char *str);
int check_dot(char token);
int check_dot_errors(char *input_string);
int check_operator(char sym);
int check_bracket(char token);
void unary_minus_set(struct token **top);

struct token *s21_parser(char *input_string);
void push(struct token **top, double value, int precedence, int type);
void pop(struct token **top);
int is_empty(struct token *top);
void free_stack(struct token **top);
struct token *reverse(struct token *top);
void push_number(struct token **top, char *number);
void push_number_and_clear_array(struct token **top, parser *p);

int define_precedence(char token);
int define_type(char token);
int define_type_fun(char *function);

struct token *s21_rpn(struct token **top);
void stack_right_bracket(struct token **operators, struct token **result);

double s21_calculate(struct token **top, double x);
double unary_calculation(calc *c, int operation);
double binary_calculation(calc *c, int operation);

double s21_result(char *string, double x);
