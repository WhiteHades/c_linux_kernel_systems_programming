#include <stdio.h>

int main(void) {
  float taxable_income, tax_due;

  printf("Enter taxable income: ");
  scanf("%f", &taxable_income);

  if (taxable_income <= 750.0f)
    tax_due = taxable_income * .01f;
  else if (taxable_income <= 2250.0f)
    tax_due = 7.50f + (taxable_income - 750.0f) * .02f;
  else if (taxable_income <= 3750.0f)
    tax_due = 37.50f + (taxable_income - 2250.0f) * .03f;
  else if (taxable_income <= 5250.0f)
    tax_due = 82.50f + (taxable_income - 3750.0f) * .04f;
  else if (taxable_income <= 7000.0f)
    tax_due = 142.50f + (taxable_income - 5250.0f) * .05f;
  else
    tax_due = 230.00f + (taxable_income - 7000.0f) * .06f;

  printf("Tax due: $%.2f\n", tax_due);

  return 0;
}
