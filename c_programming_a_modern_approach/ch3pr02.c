#include <stdio.h>

int main(void) {
  int number, month, date, year;
  float price;

  printf("enter item number: ");
  scanf("%d", &number);

  printf("enter unit price: ");
  scanf("%f", &price);

  printf("enter purchase date (mm/dd/yyyy): ");
  scanf("%02d/%02d/%04d", &month, &date, &year);

  printf("Item\t\tUnit\t\tPurchase\n");
  printf("    \t\tPrice\t\tDate\n");
  printf("%-d\t\t$%7.2f\t%02d/%02d/%04d\n", number, price, month, date, year);

  return 0;
}
