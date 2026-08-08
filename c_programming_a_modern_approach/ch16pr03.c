#include <ctype.h>
#include <stdio.h>

#define MAX_PARTS 100
#define NAME_LEN 25

struct part {
  int number;
  char name[NAME_LEN + 1];
  int on_hand;
};

int find_part(const struct part inventory[], int num_parts, int number);
int read_line(char str[], int n);
void insert(struct part inventory[], int *num_parts);
void search_part(const struct part inventory[], int num_parts);
void update(struct part inventory[], int num_parts);
void print_parts(const struct part inventory[], int num_parts);

int main(void) {
  struct part inventory[MAX_PARTS];
  int num_parts = 0;
  char code;

  for (;;) {
    printf("Enter operation code: ");
    scanf(" %c", &code);
    switch (code) {
      case 'i': insert(inventory, &num_parts); break;
      case 's': search_part(inventory, num_parts); break;
      case 'u': update(inventory, num_parts); break;
      case 'p': print_parts(inventory, num_parts); break;
      case 'q': return 0;
      default: printf("Illegal code\n");
    }
    putchar('\n');
  }
}

int find_part(const struct part inventory[], int num_parts, int number) {
  int i;
  for (i = 0; i < num_parts; i++)
    if (inventory[i].number == number)
      return i;
  return -1;
}

void insert(struct part inventory[], int *num_parts) {
  int number;
  if (*num_parts == MAX_PARTS) {
    printf("Database is full.\n");
    return;
  }
  printf("Enter part number: ");
  scanf("%d", &number);
  if (find_part(inventory, *num_parts, number) >= 0) {
    printf("Part already exists.\n");
    return;
  }
  inventory[*num_parts].number = number;
  printf("Enter part name: ");
  read_line(inventory[*num_parts].name, NAME_LEN);
  printf("Enter quantity on hand: ");
  scanf("%d", &inventory[*num_parts].on_hand);
  (*num_parts)++;
}

void search_part(const struct part inventory[], int num_parts) {
  int number, i;
  printf("Enter part number: ");
  scanf("%d", &number);
  i = find_part(inventory, num_parts, number);
  if (i < 0)
    printf("Part not found.\n");
  else
    printf("Part name: %s\nQuantity on hand: %d\n", inventory[i].name,
           inventory[i].on_hand);
}

void update(struct part inventory[], int num_parts) {
  int number, i, change;
  printf("Enter part number: ");
  scanf("%d", &number);
  i = find_part(inventory, num_parts, number);
  if (i < 0) {
    printf("Part not found.\n");
    return;
  }
  printf("Enter change in quantity on hand: ");
  scanf("%d", &change);
  inventory[i].on_hand += change;
}

void print_parts(const struct part inventory[], int num_parts) {
  int i;
  printf("Part Number   Part Name                 Quantity on Hand\n");
  for (i = 0; i < num_parts; i++)
    printf("%7d       %-25s%11d\n", inventory[i].number,
           inventory[i].name, inventory[i].on_hand);
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
