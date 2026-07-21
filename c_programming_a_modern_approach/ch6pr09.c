#include <stdio.h>

int main(void) {
  float balance, interest_rate, monthly_payment;
  int number_of_payments, payment_number;

  printf("Enter amount of loan: ");
  scanf("%f", &balance);

  printf("Enter interest rate: ");
  scanf("%f", &interest_rate);

  printf("Enter monthly payment: ");
  scanf("%f", &monthly_payment);

  printf("Enter number of payments: ");
  scanf("%d", &number_of_payments);

  for (payment_number = 1; payment_number <= number_of_payments; payment_number++) {
    balance = balance - monthly_payment + balance * interest_rate / 1200.0f;
    printf("Balance remaining after payment %d: %.2f\n", payment_number, balance);
  }

  return 0;
}
