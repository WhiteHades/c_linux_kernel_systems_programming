#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct stack_type *Stack;

struct node {
  void *data;
  struct node *next;
};

struct stack_type {
  struct node *top;
};

static Stack create(void) {
  Stack s = malloc(sizeof(*s));

  if (s == NULL)
    exit(EXIT_FAILURE);
  s->top = NULL;
  return s;
}

static bool is_empty(Stack s) { return s->top == NULL; }

static void push(Stack s, void *item) {
  struct node *new_node = malloc(sizeof(*new_node));

  if (new_node == NULL)
    exit(EXIT_FAILURE);
  new_node->data = item;
  new_node->next = s->top;
  s->top = new_node;
}

static void *pop(Stack s) {
  struct node *old_top;
  void *item;

  if (is_empty(s))
    return NULL;
  old_top = s->top;
  item = old_top->data;
  s->top = old_top->next;
  free(old_top);
  return item;
}

static void destroy(Stack s) {
  while (!is_empty(s))
    (void)pop(s);
  free(s);
}

int main(void) {
  Stack s1 = create();
  Stack s2 = create();
  char *item;

  push(s1, "first");
  push(s1, "second");
  item = pop(s1);
  printf("Popped %s from s1\n", item);
  push(s2, item);
  item = pop(s1);
  printf("Popped %s from s1\n", item);
  push(s2, item);
  while ((item = pop(s2)) != NULL)
    printf("Popped %s from s2\n", item);

  destroy(s1);
  destroy(s2);
  return 0;
}
