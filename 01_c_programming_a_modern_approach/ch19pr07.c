#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef int Item;
typedef struct queue_type *Queue;

struct node {
  Item data;
  struct node *next;
};

struct queue_type {
  struct node *first;
  struct node *last;
};

static Queue create(void) {
  Queue q = malloc(sizeof(*q));

  if (q == NULL)
    return NULL;
  q->first = NULL;
  q->last = NULL;
  return q;
}

static bool is_empty(Queue q) { return q->first == NULL; }

static void insert(Queue q, Item item) {
  struct node *new_node = malloc(sizeof(*new_node));

  if (new_node == NULL)
    exit(EXIT_FAILURE);
  new_node->data = item;
  new_node->next = NULL;
  if (q->last == NULL)
    q->first = new_node;
  else
    q->last->next = new_node;
  q->last = new_node;
}

static Item remove_item(Queue q) {
  struct node *old_first;
  Item item;

  if (is_empty(q)) {
    fprintf(stderr, "Queue is empty.\n");
    exit(EXIT_FAILURE);
  }
  old_first = q->first;
  item = old_first->data;
  q->first = old_first->next;
  if (q->first == NULL)
    q->last = NULL;
  free(old_first);
  return item;
}

static Item first_item(Queue q) {
  if (is_empty(q))
    exit(EXIT_FAILURE);
  return q->first->data;
}

static Item last_item(Queue q) {
  if (is_empty(q))
    exit(EXIT_FAILURE);
  return q->last->data;
}

static void destroy(Queue q) {
  while (!is_empty(q))
    (void)remove_item(q);
  free(q);
}

int main(void) {
  Queue q = create();
  int first, second, third;

  if (q == NULL)
    return EXIT_FAILURE;
  insert(q, 7);
  insert(q, 8);
  insert(q, 9);
  printf("first: %d, last: %d\n", first_item(q), last_item(q));
  first = remove_item(q);
  second = remove_item(q);
  third = remove_item(q);
  printf("removal order: %d %d %d\n", first, second, third);
  printf("empty: %s\n", is_empty(q) ? "yes" : "no");
  destroy(q);
  return 0;
}
