#include <stdio.h>

#define NUM_RATES 5
#define INITIAL_BALANCE 100.0

int main(void) {
  int low_rate, years;
  double balances[NUM_RATES];

  printf("Enter interest rate: ");
  scanf("%d", &low_rate);
  printf("Enter number of years: ");
  scanf("%d", &years);

  printf("\nYears");
  for (int i = 0; i < NUM_RATES; i++) {
    printf("%7d%%", low_rate + i);
    balances[i] = INITIAL_BALANCE;
  }
  printf("\n");

  for (int year = 1; year <= years; year++) {
    printf("%3d  ", year);
    for (int i = 0; i < NUM_RATES; i++) {
      double monthly_rate = (low_rate + i) / 1200.0;
      for (int month = 0; month < 12; month++)
        balances[i] += balances[i] * monthly_rate;
      printf("%8.2f", balances[i]);
    }
    printf("\n");
  }

  return 0;
}
