#include "s21_SmartCalc.h"

struct token *s21_rpn(struct token **top) {
  struct token *operators = NULL;
  struct token *result = NULL;
  struct token *tmp = NULL;
  int flag = 0;
  while (!is_empty(*top)) {
    if ((*top)->type < 3) {
      push(&result, (*top)->value, (*top)->precedence, (*top)->type);
    } else {
      if ((*top)->type == 8) {
        stack_right_bracket(&operators, &result);
      } else if ((*top)->type == 7 || is_empty(operators) ||
                 (*top)->precedence > operators->precedence) {
        push(&operators, (*top)->value, (*top)->precedence, (*top)->type);
      } else if (!is_empty(operators) &&
                 (*top)->precedence <= operators->precedence) {
        push(&tmp, (*top)->value, (*top)->precedence, (*top)->type);
        while (!is_empty(operators) && flag == 0) {
          if ((*top)->precedence <= operators->precedence) {
            push(&result, operators->value, operators->precedence,
                 operators->type);
            pop(&operators);
          } else {
            flag = 1;
          }
        }
        push(&operators, tmp->value, tmp->precedence, tmp->type);
      }
      flag = 0;
    }
    if (!is_empty(*top)) {
      pop(top);
    }
  }
  while (!is_empty(operators)) {
    push(&result, operators->value, operators->precedence, operators->type);
    pop(&operators);
  }
  free_stack(&tmp);
  return reverse(result);
}

void stack_right_bracket(struct token **operators, struct token **result) {
  while ((*operators)->type != 7 && !is_empty(*operators)) {
    if ((*operators)->type != 7) {
      push(result, (*operators)->value, (*operators)->precedence,
           (*operators)->type);
    }
    pop(operators);
  }
  if (!is_empty(*operators)) {
    pop(operators);
  }
}
