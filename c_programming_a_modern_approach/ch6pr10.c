#include <stdio.h>

int main(void) {
  int day, earliest_day, earliest_month, earliest_year, has_date, month, year;

  has_date = 0;

  while (1) {
    printf("Enter a date (mm/dd/yy): ");
    scanf("%d/%d/%d", &month, &day, &year);

    if (month == 0 && day == 0 && year == 0)
      break;

    if (!has_date || year < earliest_year || (year == earliest_year && month < earliest_month) ||
        (year == earliest_year && month == earliest_month && day < earliest_day)) {
      earliest_month = month;
      earliest_day = day;
      earliest_year = year;
      has_date = 1;
    }
  }

  if (has_date)
    printf("%d/%d/%.2d is the earliest date\n", earliest_month, earliest_day, earliest_year);

  return 0;
}
