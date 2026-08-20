#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define QUEUE_SIZE 10

typedef int Item;
typedef struct queue_type *Queue;

struct queue_type {
  Item contents[QUEUE_SIZE];
  int first;
  int next;
  int count;
};

static Queue create(void) {
  Queue q = malloc(sizeof(*q));

  if (q == NULL)
    exit(EXIT_FAILURE);
  q->first = 0;
  q->next = 0;
  q->count = 0;
  return q;
}

static void destroy(Queue q) { free(q); }
static bool is_empty(Queue q) { return q->count == 0; }
static bool is_full(Queue q) { return q->count == QUEUE_SIZE; }

static void insert(Queue q, Item item) {
  if (is_full(q)) {
    fprintf(stderr, "Queue is full.\n");
    exit(EXIT_FAILURE);
  }
  q->contents[q->next] = item;
  q->next = (q->next + 1) % QUEUE_SIZE;
  q->count++;
}

static Item remove_item(Queue q) {
  Item item;

  if (is_empty(q)) {
    fprintf(stderr, "Queue is empty.\n");
    exit(EXIT_FAILURE);
  }
  item = q->contents[q->first];
  q->first = (q->first + 1) % QUEUE_SIZE;
  q->count--;
  return item;
}

static Item first_item(Queue q) {
  if (is_empty(q))
    exit(EXIT_FAILURE);
  return q->contents[q->first];
}

static Item last_item(Queue q) {
  if (is_empty(q))
    exit(EXIT_FAILURE);
  return q->contents[(q->next + QUEUE_SIZE - 1) % QUEUE_SIZE];
}

int main(void) {
  Queue q1 = create();
  Queue q2 = create();

  insert(q1, 10);
  insert(q1, 20);
  insert(q2, 30);
  printf("q1 first: %d, q1 last: %d\n", first_item(q1), last_item(q1));
  printf("q1 removed: %d\n", remove_item(q1));
  printf("q2 removed: %d\n", remove_item(q2));
  printf("q2 is empty: %s\n", is_empty(q2) ? "yes" : "no");

  destroy(q1);
  destroy(q2);
  return 0;
}
