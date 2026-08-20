#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define NAME_LEN 25

struct part {
  int number;
  char name[NAME_LEN + 1];
  int on_hand;
  struct part *next;
};

struct part *inventory;

struct part *find_part(int number);
int read_line(char str[], int n);
void insert(void);
void erase(void);
void search_part(void);
void update(void);
void print_parts(void);
void free_inventory(void);

int main(void) {
  char code;
  for (;;) {
    printf("Enter operation code: ");
    scanf(" %c", &code);
    switch (code) {
      case 'i': insert(); break;
      case 'e': erase(); break;
      case 's': search_part(); break;
      case 'u': update(); break;
      case 'p': print_parts(); break;
      case 'q': free_inventory(); return 0;
      default: printf("Illegal code\n");
    }
    putchar('\n');
  }
}

struct part *find_part(int number) {
  struct part *p;
  for (p = inventory; p != NULL && p->number < number; p = p->next)
    ;
  return p != NULL && p->number == number ? p : NULL;
}

void insert(void) {
  struct part *cur = inventory, *prev = NULL, *node;
  int number;

  printf("Enter part number: ");
  scanf("%d", &number);
  if (find_part(number) != NULL) {
    printf("Part already exists.\n");
    return;
  }
  node = malloc(sizeof(*node));
  if (node == NULL) {
    printf("Database is full.\n");
    return;
  }
  node->number = number;
  printf("Enter part name: ");
  read_line(node->name, NAME_LEN);
  printf("Enter quantity on hand: ");
  scanf("%d", &node->on_hand);
  while (cur != NULL && cur->number < number) {
    prev = cur;
    cur = cur->next;
  }
  node->next = cur;
  if (prev == NULL)
    inventory = node;
  else
    prev->next = node;
}

void erase(void) {
  struct part *cur = inventory, *prev = NULL;
  int number;

  printf("Enter part number: ");
  scanf("%d", &number);
  while (cur != NULL && cur->number < number) {
    prev = cur;
    cur = cur->next;
  }
  if (cur == NULL || cur->number != number) {
    printf("Part not found.\n");
    return;
  }
  if (prev == NULL)
    inventory = cur->next;
  else
    prev->next = cur->next;
  free(cur);
}

void search_part(void) {
  struct part *p;
  int number;

  printf("Enter part number: ");
  scanf("%d", &number);
  p = find_part(number);
  if (p == NULL)
    printf("Part not found.\n");
  else
    printf("Part name: %s\nQuantity on hand: %d\n", p->name, p->on_hand);
}

void update(void) {
  struct part *p;
  int number, change;

  printf("Enter part number: ");
  scanf("%d", &number);
  p = find_part(number);
  if (p == NULL) {
    printf("Part not found.\n");
    return;
  }
  printf("Enter change in quantity on hand: ");
  scanf("%d", &change);
  p->on_hand += change;
}

void print_parts(void) {
  struct part *p;
  printf("Part Number   Part Name                 Quantity on Hand\n");
  for (p = inventory; p != NULL; p = p->next)
    printf("%7d       %-25s%11d\n", p->number, p->name, p->on_hand);
}

void free_inventory(void) {
  while (inventory != NULL) {
    struct part *next = inventory->next;
    free(inventory);
    inventory = next;
  }
}

int read_line(char str[], int n) {
  int ch, i = 0;
  while (isspace(ch = getchar()))
    ;
  while (ch != '\n' && ch != EOF) {
    if (i < n)
      str[i++] = (char) ch;
    ch = getchar();
  }
  str[i] = '\0';
  return i;
}
