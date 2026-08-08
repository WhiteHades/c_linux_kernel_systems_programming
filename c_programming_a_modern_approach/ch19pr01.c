#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef char Item;
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
    fprintf(stderr, "Stack could not be created.\n");
    exit(EXIT_FAILURE);
  }
  s->top = NULL;
  return s;
}

static bool is_empty(Stack s) { return s->top == NULL; }

static void push(Stack s, Item item) {
  struct node *new_node = malloc(sizeof(*new_node));

  if (new_node == NULL) {
    fprintf(stderr, "Stack overflow\n");
    exit(EXIT_FAILURE);
  }
  new_node->data = item;
  new_node->next = s->top;
  s->top = new_node;
}

static bool pop(Stack s, Item *item) {
  struct node *old_top;

  if (is_empty(s))
    return false;
  old_top = s->top;
  *item = old_top->data;
  s->top = old_top->next;
  free(old_top);
  return true;
}

static void destroy(Stack s) {
  Item ignored;

  while (pop(s, &ignored))
    ;
  free(s);
}

int main(void) {
  Stack s = create();
  int ch;
  bool proper = true;

  printf("Enter parentheses and/or braces: ");
  while ((ch = getchar()) != '\n' && ch != EOF) {
    if (ch == '(' || ch == '{') {
      push(s, (char)ch);
    } else if (ch == ')' || ch == '}') {
      Item opening;

      if (!pop(s, &opening) ||
          (ch == ')' && opening != '(') ||
          (ch == '}' && opening != '{')) {
        proper = false;
        break;
      }
    }
  }

  if (!is_empty(s))
    proper = false;
  printf("Parentheses/braces are %snested properly\n", proper ? "" : "not ");
  destroy(s);
  return 0;
}
