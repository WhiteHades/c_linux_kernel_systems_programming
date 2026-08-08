#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

struct stack {
  int contents[100];
  int top;
};

void make_empty(struct stack *s);
bool push(struct stack *s, int value);
bool pop(struct stack *s, int *value);

int main(void) {
  char line[201];
  struct stack s;

  for (;;) {
    char *p;
    int left, right;

    printf("Enter an RPN expression: ");
    if (fgets(line, sizeof(line), stdin) == NULL || line[0] == 'q')
      break;
    make_empty(&s);
    for (p = line; *p; p++) {
      if (isdigit((unsigned char) *p)) {
        if (!push(&s, *p - '0')) {
          printf("Expression is too complex\n");
          return 1;
        }
      }
      else if (*p == '+' || *p == '-' || *p == '*' || *p == '/') {
        if (!pop(&s, &right) || !pop(&s, &left)) {
          printf("Not enough operands in expression\n");
          return 1;
        }
        if (*p == '+') push(&s, left + right);
        if (*p == '-') push(&s, left - right);
        if (*p == '*') push(&s, left * right);
        if (*p == '/') push(&s, left / right);
      } else if (*p == '=') {
        if (!pop(&s, &right)) {
          printf("Not enough operands in expression\n");
          return 1;
        }
        printf("Value of expression: %d\n", right);
        break;
      }
    }
  }
  return 0;
}

void make_empty(struct stack *s) {
  s->top = 0;
}

bool push(struct stack *s, int value) {
  if (s->top == 100)
    return false;
  s->contents[s->top++] = value;
  return true;
}

bool pop(struct stack *s, int *value) {
  if (s->top == 0)
    return false;
  *value = s->contents[--s->top];
  return true;
}
