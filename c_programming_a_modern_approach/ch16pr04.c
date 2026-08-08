#include <ctype.h>
#include <stdio.h>

#define MAX_PARTS 100
#define NAME_LEN 25

struct part {
  int number;
  char name[NAME_LEN + 1];
  int on_hand;
  double price;
};

struct part inventory[MAX_PARTS];
int num_parts;

int find_part(int number);
int read_line(char str[], int n);
void insert(void);
void search_part(void);
void update_quantity(void);
void change_price(void);
void print_parts(void);

int main(void) {
  char code;
  for (;;) {
    printf("Enter operation code: ");
    scanf(" %c", &code);
    switch (code) {
      case 'i': insert(); break;
      case 's': search_part(); break;
      case 'u': update_quantity(); break;
      case 'c': change_price(); break;
      case 'p': print_parts(); break;
      case 'q': return 0;
      default: printf("Illegal code\n");
    }
    putchar('\n');
  }
}

int find_part(int number) {
  int i;
  for (i = 0; i < num_parts; i++)
    if (inventory[i].number == number)
      return i;
  return -1;
}

void insert(void) {
  int number;
  if (num_parts == MAX_PARTS) {
    printf("Database is full.\n");
    return;
  }
  printf("Enter part number: ");
  scanf("%d", &number);
  if (find_part(number) >= 0) {
    printf("Part already exists.\n");
    return;
  }
  inventory[num_parts].number = number;
  printf("Enter part name: ");
  read_line(inventory[num_parts].name, NAME_LEN);
  printf("Enter quantity on hand: ");
  scanf("%d", &inventory[num_parts].on_hand);
  printf("Enter price: ");
  scanf("%lf", &inventory[num_parts].price);
  num_parts++;
}

void search_part(void) {
  int number, i;
  printf("Enter part number: ");
  scanf("%d", &number);
  i = find_part(number);
  if (i < 0)
    printf("Part not found.\n");
  else
    printf("Part name: %s\nQuantity on hand: %d\nPrice: $%.2f\n",
           inventory[i].name, inventory[i].on_hand, inventory[i].price);
}

void update_quantity(void) {
  int number, i, change;
  printf("Enter part number: ");
  scanf("%d", &number);
  i = find_part(number);
  if (i < 0) {
    printf("Part not found.\n");
    return;
  }
  printf("Enter change in quantity on hand: ");
  scanf("%d", &change);
  inventory[i].on_hand += change;
}

void change_price(void) {
  int number, i;
  printf("Enter part number: ");
  scanf("%d", &number);
  i = find_part(number);
  if (i < 0) {
    printf("Part not found.\n");
    return;
  }
  printf("Enter new price: ");
  scanf("%lf", &inventory[i].price);
}

void print_parts(void) {
  int i;
  printf("Part Number   Part Name                 Quantity   Price\n");
  for (i = 0; i < num_parts; i++)
    printf("%7d       %-25s%8d $%7.2f\n", inventory[i].number,
           inventory[i].name, inventory[i].on_hand, inventory[i].price);
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
