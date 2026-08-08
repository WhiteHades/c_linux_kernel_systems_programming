#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define NAME_LEN 25

struct part {
  int number;
  char name[NAME_LEN + 1];
  int on_hand;
};

int find_part(const struct part inventory[], int num_parts, int number);
int read_line(char str[], int n);

int main(void) {
  int capacity = 10, num_parts = 0;
  struct part *inventory = malloc(capacity * sizeof(*inventory));
  char code;

  if (inventory == NULL) {
    printf("Unable to allocate inventory.\n");
    return 1;
  }
  for (;;) {
    int number, i, change;
    printf("Enter operation code: ");
    scanf(" %c", &code);
    if (code == 'q')
      break;
    switch (code) {
      case 'i':
        printf("Enter part number: ");
        scanf("%d", &number);
        if (find_part(inventory, num_parts, number) >= 0) {
          printf("Part already exists.\n");
          break;
        }
        if (num_parts == capacity) {
          struct part *larger;
          capacity *= 2;
          larger = realloc(inventory, capacity * sizeof(*inventory));
          if (larger == NULL) {
            printf("Database is full.\n");
            free(inventory);
            return 1;
          }
          inventory = larger;
        }
        inventory[num_parts].number = number;
        printf("Enter part name: ");
        read_line(inventory[num_parts].name, NAME_LEN);
        printf("Enter quantity on hand: ");
        scanf("%d", &inventory[num_parts].on_hand);
        num_parts++;
        break;
      case 's':
        printf("Enter part number: ");
        scanf("%d", &number);
        i = find_part(inventory, num_parts, number);
        if (i < 0)
          printf("Part not found.\n");
        else
          printf("Part name: %s\nQuantity on hand: %d\n",
                 inventory[i].name, inventory[i].on_hand);
        break;
      case 'u':
        printf("Enter part number: ");
        scanf("%d", &number);
        i = find_part(inventory, num_parts, number);
        if (i < 0)
          printf("Part not found.\n");
        else {
          printf("Enter change in quantity on hand: ");
          scanf("%d", &change);
          inventory[i].on_hand += change;
        }
        break;
      case 'p':
        printf("Part Number   Part Name                 Quantity on Hand\n");
        for (i = 0; i < num_parts; i++)
          printf("%7d       %-25s%11d\n", inventory[i].number,
                 inventory[i].name, inventory[i].on_hand);
        break;
      default: printf("Illegal code\n");
    }
    putchar('\n');
  }
  free(inventory);
  return 0;
}

int find_part(const struct part inventory[], int num_parts, int number) {
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
