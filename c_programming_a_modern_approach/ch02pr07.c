#include <stdio.h>

int main(void)
{
  int amount, number_20, number_10, number_5, number_1;

  printf("enter dollar amount: ");
  scanf("%d", &amount);
  
  number_20 = amount / 20;
  number_10 = (amount - (number_20*20))/ 10;
  number_5 = (amount - (number_20*20) - (number_10*10))/ 5;
  number_1 = (amount - (number_20*20) - (number_10*10) - (number_5*5))/ 1;

  printf("$20 bills: %d\n", number_20);
  printf("$10 bills: %d\n", number_10);
  printf("$5 bills : %d\n", number_5);
  printf("$1 bills : %d\n", number_1);

  return 0;
}
