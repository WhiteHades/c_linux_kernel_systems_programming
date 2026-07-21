/* Calculates a broker's commission */
#include <stdio.h>

int main(void) {
  int number_of_shares;
  float price_per_trade, commission;

  printf("Enter number of shares: ");
  scanf("%d", &number_of_shares);

  printf("enter price per share: ");
  scanf("%f", &price_per_trade);

  if (number_of_shares >= 2000)
    commission = 33.00f + .003f * number_of_shares;
  else
    commission = 33.00f + .002f * number_of_shares;

  printf("Commission: $%.2f\n", commission);

  return 0;
}
