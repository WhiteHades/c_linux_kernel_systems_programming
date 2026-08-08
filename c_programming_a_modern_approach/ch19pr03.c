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
  int len;
};

static Stack create(void) {
  Stack s = malloc(sizeof(*s));

  if (s == NULL)
    exit(EXIT_FAILURE);
  s->top = NULL;
  s->len = 0;
  return s;
}

static bool is_empty(Stack s) { return s->top == NULL; }
static int length(Stack s) { return s->len; }

static void push(Stack s, Item item) {
  struct node *new_node = malloc(sizeof(*new_node));

  if (new_node == NULL)
    exit(EXIT_FAILURE);
  new_node->data = item;
  new_node->next = s->top;
  s->top = new_node;
  s->len++;
}

static Item pop(Stack s) {
  struct node *old_top;
  Item item;

  if (is_empty(s))
    exit(EXIT_FAILURE);
  old_top = s->top;
  item = old_top->data;
  s->top = old_top->next;
  s->len--;
  free(old_top);
  return item;
}

static void make_empty(Stack s) {
  while (!is_empty(s))
    (void)pop(s);
}

static void destroy(Stack s) {
  make_empty(s);
  free(s);
}

static void show_length(const char *name, Stack s) {
  printf("Length of %s: %d\n", name, length(s));
}

int main(void) {
  Stack s1 = create();
  Stack s2 = create();
  int n;

  push(s1, 1);
  show_length("s1", s1);
  push(s1, 2);
  show_length("s1", s1);
  n = pop(s1);
  show_length("s1", s1);
  push(s2, n);
  show_length("s2", s2);
  n = pop(s1);
  show_length("s1", s1);
  push(s2, n);
  show_length("s2", s2);
  make_empty(s2);
  show_length("s2", s2);

  destroy(s1);
  destroy(s2);
  return 0;
}
