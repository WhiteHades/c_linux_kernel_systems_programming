#include <math.h>
#include <stdio.h>

int main(void) {
  double principal, rate, years, amount;

  printf("Enter original amount: ");
  if (scanf("%lf", &principal) != 1)
    return 1;
  printf("Enter annual interest rate (percent): ");
  if (scanf("%lf", &rate) != 1)
    return 1;
  printf("Enter number of years: ");
  if (scanf("%lf", &years) != 1)
    return 1;

  amount = principal * exp((rate / 100.0) * years);
  printf("Final value: $%.2f\n", amount);

  return 0;
}
