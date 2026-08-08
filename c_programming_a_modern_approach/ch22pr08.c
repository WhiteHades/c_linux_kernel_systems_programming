#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define NAME_LEN 25
#define MAX_PARTS 100

struct part {
  int number;
  char name[NAME_LEN + 1];
  int on_hand;
};

static struct part inventory[MAX_PARTS];
static int num_parts;

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

static int find_part(int number) {
  for (int i = 0; i < num_parts; i++)
    if (inventory[i].number == number)
      return i;
  return -1;
}

static void insert(void) {
  int number;

  if (num_parts == MAX_PARTS) {
    printf("Database is full; can't add more parts.\n");
    return;
  }
  printf("Enter part number: ");
  if (scanf("%d", &number) != 1)
    return;
  if (find_part(number) >= 0) {
    printf("Part already exists.\n");
    return;
  }
  inventory[num_parts].number = number;
  printf("Enter part name: ");
  read_line(inventory[num_parts].name, NAME_LEN);
  printf("Enter quantity on hand: ");
  if (scanf("%d", &inventory[num_parts].on_hand) == 1)
    num_parts++;
}

static void search(void) {
  int number, i;

  printf("Enter part number: ");
  if (scanf("%d", &number) != 1)
    return;
  i = find_part(number);
  if (i < 0) {
    printf("Part not found.\n");
    return;
  }
  printf("Part name: %s\n", inventory[i].name);
  printf("Quantity on hand: %d\n", inventory[i].on_hand);
}

static void update(void) {
  int number, change, i;

  printf("Enter part number: ");
  if (scanf("%d", &number) != 1)
    return;
  i = find_part(number);
  if (i < 0) {
    printf("Part not found.\n");
    return;
  }
  printf("Enter change in quantity on hand: ");
  if (scanf("%d", &change) == 1)
    inventory[i].on_hand += change;
}

static void print_parts(void) {
  printf("Part Number   Part Name                Quantity on Hand\n");
  for (int i = 0; i < num_parts; i++)
    printf("%7d       %-25s%11d\n", inventory[i].number,
           inventory[i].name, inventory[i].on_hand);
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
  if (fwrite(inventory, sizeof(inventory[0]), (size_t)num_parts, fp) !=
      (size_t)num_parts)
    printf("Error writing %s\n", name);
  if (fclose(fp) == EOF)
    printf("Error closing %s\n", name);
}

static void restore(void) {
  char name[FILENAME_MAX];
  FILE *fp;
  size_t count;

  printf("Enter name of input file: ");
  read_line(name, (int)sizeof(name) - 1);
  fp = fopen(name, "rb");
  if (fp == NULL) {
    printf("Can't open %s\n", name);
    return;
  }
  count = fread(inventory, sizeof(inventory[0]), MAX_PARTS, fp);
  if (ferror(fp)) {
    printf("Error reading %s\n", name);
  } else {
    num_parts = (int)count;
  }
  fclose(fp);
}

int main(void) {
  char code;

  for (;;) {
    printf("Enter operation code: ");
    if (scanf(" %c", &code) != 1)
      return 0;
    skip_line();
    switch (code) {
    case 'i':
      insert();
      break;
    case 's':
      search();
      break;
    case 'u':
      update();
      break;
    case 'p':
      print_parts();
      break;
    case 'd':
      dump();
      break;
    case 'r':
      restore();
      break;
    case 'q':
      return 0;
    default:
      printf("Illegal code\n");
    }
    putchar('\n');
  }
}
