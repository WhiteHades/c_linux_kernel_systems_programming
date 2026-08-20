#include <stdio.h>

int main(void) 
{
  float loan, rate, payment, first_balance, second_balance, third_balance, temp, monthly_rate;

  printf("enter amount of loan : ");
  scanf("%f", &loan);

  printf("enter interest rate  : ");
  scanf("%f", &rate);

  printf("enter monthly payment: ");
  scanf("%f", &payment);

  monthly_rate = rate/1200.00f;

  temp = loan - payment;
  first_balance = temp + (loan * monthly_rate);

  temp = first_balance - payment;
  second_balance = temp + (first_balance * monthly_rate);

  temp = second_balance - payment;
  third_balance = temp + (second_balance * monthly_rate);

  printf("balance remaining after 1st payment: %.2f\n", first_balance);
  printf("balance remaining after 2nd payment: %.2f\n", second_balance);
  printf("balance remaining after 3rd payment: %.2f\n", third_balance);

  return 0;
}
