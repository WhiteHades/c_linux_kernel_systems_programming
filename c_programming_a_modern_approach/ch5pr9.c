#include <stdio.h>

int main(void) {
  int first_month, first_day, first_year;
  int second_month, second_day, second_year;

  printf("Enter first date (mm/dd/yy): ");
  scanf("%d/%d/%d", &first_month, &first_day, &first_year);

  printf("Enter second date (mm/dd/yy): ");
  scanf("%d/%d/%d", &second_month, &second_day, &second_year);

  if (first_year < second_year ||
      (first_year == second_year && first_month < second_month) ||
      (first_year == second_year && first_month == second_month && first_day < second_day))
    printf("%d/%d/%.2d is earlier than %d/%d/%.2d\n", first_month, first_day, first_year,
           second_month, second_day, second_year);
  else if (second_year < first_year ||
           (second_year == first_year && second_month < first_month) ||
           (second_year == first_year && second_month == first_month && second_day < first_day))
    printf("%d/%d/%.2d is earlier than %d/%d/%.2d\n", second_month, second_day, second_year,
           first_month, first_day, first_year);
  else
    printf("The dates are the same\n");

  return 0;
}
