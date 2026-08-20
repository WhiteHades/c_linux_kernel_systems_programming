#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_PARTS 100
#define NAME_LEN 25

struct part {
  int number;
  char name[NAME_LEN + 1];
  int on_hand;
};

struct part inventory[MAX_PARTS];
int num_parts;

int compare_parts(const void *p, const void *q);
int find_part(int number);
int read_line(char str[], int n);

int main(void) {
  char code;

  for (;;) {
    int number, i, change;
    printf("Enter operation code: ");
    scanf(" %c", &code);
    if (code == 'q')
      return 0;
    if (code == 'i') {
      printf("Enter part number: ");
      scanf("%d", &number);
      if (num_parts == MAX_PARTS || find_part(number) >= 0) {
        printf("Part cannot be inserted.\n");
        continue;
      }
      inventory[num_parts].number = number;
      printf("Enter part name: ");
      read_line(inventory[num_parts].name, NAME_LEN);
      printf("Enter quantity on hand: ");
      scanf("%d", &inventory[num_parts].on_hand);
      num_parts++;
    } else if (code == 's') {
      printf("Enter part number: ");
      scanf("%d", &number);
      i = find_part(number);
      if (i < 0)
        printf("Part not found.\n");
      else
        printf("Part name: %s\nQuantity on hand: %d\n",
               inventory[i].name, inventory[i].on_hand);
    } else if (code == 'u') {
      printf("Enter part number: ");
      scanf("%d", &number);
      i = find_part(number);
      if (i < 0)
        printf("Part not found.\n");
      else {
        printf("Enter change in quantity on hand: ");
        scanf("%d", &change);
        inventory[i].on_hand += change;
      }
    } else if (code == 'p') {
      qsort(inventory, num_parts, sizeof(inventory[0]), compare_parts);
      printf("Part Number   Part Name                 Quantity on Hand\n");
      for (i = 0; i < num_parts; i++)
        printf("%7d       %-25s%11d\n", inventory[i].number,
               inventory[i].name, inventory[i].on_hand);
    } else
      printf("Illegal code\n");
    putchar('\n');
  }
}

int compare_parts(const void *p, const void *q) {
  const struct part *left = p, *right = q;
  return (left->number > right->number) -
         (left->number < right->number);
}

int find_part(int number) {
  int i;
  for (i = 0; i < num_parts; i++)
    if (inventory[i].number == number)
      return i;
  return -1;
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
