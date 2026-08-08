#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LEN 25

struct part {
  int number;
  char name[NAME_LEN + 1];
  int on_hand;
  struct part *next;
};

struct stored_part {
  int number;
  char name[NAME_LEN + 1];
  int on_hand;
};

static struct part *inventory;

static int read_line(char str[], int n) {
  int ch, i = 0;

  while (isspace(ch = getchar()))
    ;
  while (ch != '\n' && ch != EOF) {
    if (i < n)
      str[i++] = (char)ch;
    ch = getchar();
  }
  str[i] = '\0';
  return i;
}

static void skip_line(void) {
  int ch;

  while ((ch = getchar()) != '\n' && ch != EOF)
    ;
}

static struct part *find_part(int number) {
  struct part *p;

  for (p = inventory; p != NULL && number > p->number; p = p->next)
    ;
  return p != NULL && p->number == number ? p : NULL;
}

static void insert(void) {
  struct part *current, *previous = NULL;
  struct part *new_node = malloc(sizeof(*new_node));

  if (new_node == NULL) {
    printf("Database is full; can't add more parts.\n");
    return;
  }
  printf("Enter part number: ");
  if (scanf("%d", &new_node->number) != 1) {
    free(new_node);
    return;
  }
  for (current = inventory;
       current != NULL && new_node->number > current->number;
       previous = current, current = current->next)
    ;
  if (current != NULL && current->number == new_node->number) {
    printf("Part already exists.\n");
    free(new_node);
    return;
  }
  printf("Enter part name: ");
  read_line(new_node->name, NAME_LEN);
  printf("Enter quantity on hand: ");
  if (scanf("%d", &new_node->on_hand) != 1) {
    free(new_node);
    return;
  }
  new_node->next = current;
  if (previous == NULL)
    inventory = new_node;
  else
    previous->next = new_node;
}

static void search(void) {
  int number;
  struct part *p;

  printf("Enter part number: ");
  if (scanf("%d", &number) != 1)
    return;
  p = find_part(number);
  if (p == NULL) {
    printf("Part not found.\n");
    return;
  }
  printf("Part name: %s\nQuantity on hand: %d\n", p->name, p->on_hand);
}

static void update(void) {
  int number, change;
  struct part *p;

  printf("Enter part number: ");
  if (scanf("%d", &number) != 1)
    return;
  p = find_part(number);
  if (p == NULL) {
    printf("Part not found.\n");
    return;
  }
  printf("Enter change in quantity on hand: ");
  if (scanf("%d", &change) == 1)
    p->on_hand += change;
}

static void print_parts(void) {
  struct part *p;

  printf("Part Number   Part Name                Quantity on Hand\n");
  for (p = inventory; p != NULL; p = p->next)
    printf("%7d       %-25s%11d\n", p->number, p->name, p->on_hand);
}

static void clear_inventory(void) {
  while (inventory != NULL) {
    struct part *old = inventory;

    inventory = inventory->next;
    free(old);
  }
}

static void dump(void) {
  char name[FILENAME_MAX];
  FILE *fp;

  printf("Enter name of output file: ");
  read_line(name, (int)sizeof(name) - 1);
  fp = fopen(name, "wb");
  if (fp == NULL) {
    printf("Can't open %s\n", name);
    return;
  }
  for (struct part *p = inventory; p != NULL; p = p->next) {
    struct stored_part item = {p->number, "", p->on_hand};

    strcpy(item.name, p->name);
    if (fwrite(&item, sizeof(item), 1, fp) != 1) {
      printf("Error writing %s\n", name);
      break;
    }
  }
  fclose(fp);
}

static void restore(void) {
  char name[FILENAME_MAX];
  FILE *fp;
  struct part *last = NULL;
  struct stored_part item;

  printf("Enter name of input file: ");
  read_line(name, (int)sizeof(name) - 1);
  fp = fopen(name, "rb");
  if (fp == NULL) {
    printf("Can't open %s\n", name);
    return;
  }
  clear_inventory();
  while (fread(&item, sizeof(item), 1, fp) == 1) {
    struct part *new_node = malloc(sizeof(*new_node));

    if (new_node == NULL) {
      printf("Database is full; restore stopped.\n");
      break;
    }
    new_node->number = item.number;
    strcpy(new_node->name, item.name);
    new_node->on_hand = item.on_hand;
    new_node->next = NULL;
    if (last == NULL)
      inventory = new_node;
    else
      last->next = new_node;
    last = new_node;
  }
  if (ferror(fp))
    printf("Error reading %s\n", name);
  fclose(fp);
}

int main(void) {
  char code;

  for (;;) {
    printf("Enter operation code: ");
    if (scanf(" %c", &code) != 1)
      break;
    skip_line();
    switch (code) {
    case 'i': insert(); break;
    case 's': search(); break;
    case 'u': update(); break;
    case 'p': print_parts(); break;
    case 'd': dump(); break;
    case 'r': restore(); break;
    case 'q': clear_inventory(); return 0;
    default: printf("Illegal code\n");
    }
    putchar('\n');
  }
  clear_inventory();
  return 0;
}
