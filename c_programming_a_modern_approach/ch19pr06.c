#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef int Item;
typedef struct queue_type *Queue;

struct queue_type {
  Item *contents;
  int first;
  int next;
  int count;
  int size;
};

static Queue create(int size) {
  Queue q;

  if (size <= 0)
    return NULL;
  q = malloc(sizeof(*q));
  if (q == NULL)
    return NULL;
  q->contents = malloc((size_t)size * sizeof(*q->contents));
  if (q->contents == NULL) {
    free(q);
    return NULL;
  }
  q->first = 0;
  q->next = 0;
  q->count = 0;
  q->size = size;
  return q;
}

static void destroy(Queue q) {
  free(q->contents);
  free(q);
}

static bool is_empty(Queue q) { return q->count == 0; }
static bool is_full(Queue q) { return q->count == q->size; }

static void insert(Queue q, Item item) {
  if (is_full(q)) {
    fprintf(stderr, "Queue is full.\n");
    exit(EXIT_FAILURE);
  }
  q->contents[q->next] = item;
  q->next = (q->next + 1) % q->size;
  q->count++;
}

static Item remove_item(Queue q) {
  Item item;

  if (is_empty(q)) {
    fprintf(stderr, "Queue is empty.\n");
    exit(EXIT_FAILURE);
  }
  item = q->contents[q->first];
  q->first = (q->first + 1) % q->size;
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
  return q->contents[(q->next + q->size - 1) % q->size];
}

int main(void) {
  Queue small = create(2);
  Queue large = create(4);
  int first, second, third;

  if (small == NULL || large == NULL)
    return EXIT_FAILURE;
  insert(small, 1);
  insert(small, 2);
  insert(large, 10);
  insert(large, 20);
  insert(large, 30);
  printf("small: first %d, last %d\n", first_item(small), last_item(small));
  first = remove_item(large);
  second = remove_item(large);
  third = remove_item(large);
  printf("large removal order: %d %d %d\n", first, second, third);

  destroy(small);
  destroy(large);
  return 0;
}
