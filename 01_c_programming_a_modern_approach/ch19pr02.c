#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef int Item;
typedef struct stack_type *Stack;

struct node {
  Item data;
  struct node *next;
};

struct stack_type {
  struct node *top;
};

static Stack create(void) {
  Stack s = malloc(sizeof(*s));

  if (s == NULL) {
    fprintf(stderr, "Expression is too complex\n");
    exit(EXIT_FAILURE);
  }
  s->top = NULL;
  return s;
}

static bool is_empty(Stack s) { return s->top == NULL; }

static void push(Stack s, Item item) {
  struct node *new_node = malloc(sizeof(*new_node));

  if (new_node == NULL) {
    fprintf(stderr, "Expression is too complex\n");
    exit(EXIT_FAILURE);
  }
  new_node->data = item;
  new_node->next = s->top;
  s->top = new_node;
}

static Item pop(Stack s) {
  struct node *old_top;
  Item item;

  if (is_empty(s)) {
    fprintf(stderr, "Not enough operands in expression\n");
    exit(EXIT_FAILURE);
  }
  old_top = s->top;
  item = old_top->data;
  s->top = old_top->next;
  free(old_top);
  return item;
}

static void make_empty(Stack s) {
  while (!is_empty(s))
    (void)pop(s);
}

int main(void) {
  Stack s = create();
  char ch;

  for (;;) {
    printf("Enter an RPN expression: ");
    while (scanf(" %c", &ch) == 1) {
      int left, right;

      if (ch >= '0' && ch <= '9') {
        push(s, ch - '0');
        continue;
      }
      if (ch == '=') {
        printf("Value of expression: %d\n", pop(s));
        make_empty(s);
        break;
      }
      if (ch != '+' && ch != '-' && ch != '*' && ch != '/') {
        make_empty(s);
        free(s);
        return 0;
      }
      right = pop(s);
      left = pop(s);
      if (ch == '+')
        push(s, left + right);
      else if (ch == '-')
        push(s, left - right);
      else if (ch == '*')
        push(s, left * right);
      else {
        if (right == 0) {
          fprintf(stderr, "Division by zero\n");
          exit(EXIT_FAILURE);
        }
        push(s, left / right);
      }
    }
    if (feof(stdin))
      break;
  }

  make_empty(s);
  free(s);
  return 0;
}
