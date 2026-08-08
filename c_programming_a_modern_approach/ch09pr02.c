#include <stdio.h>

double calculate_tax(double income);

int main(void) {
  double income;

  printf("Enter taxable income: ");
  scanf("%lf", &income);
  printf("Tax due: $%.2f\n", calculate_tax(income));

  return 0;
}

double calculate_tax(double income) {
  if (income <= 750.0)
    return income * 0.01;
  if (income <= 2250.0)
    return 7.50 + (income - 750.0) * 0.02;
  if (income <= 3750.0)
    return 37.50 + (income - 2250.0) * 0.03;
  if (income <= 5250.0)
    return 82.50 + (income - 3750.0) * 0.04;
  if (income <= 7000.0)
    return 142.50 + (income - 5250.0) * 0.05;
  return 230.00 + (income - 7000.0) * 0.06;
}
