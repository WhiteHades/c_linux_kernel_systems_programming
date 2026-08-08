#include <stdio.h>

struct date {
  int month;
  int day;
  int year;
};

int compare_dates(struct date d1, struct date d2);

int main(void) {
  struct date first, second;

  printf("Enter first date (mm/dd/yy): ");
  scanf("%d/%d/%d", &first.month, &first.day, &first.year);
  printf("Enter second date (mm/dd/yy): ");
  scanf("%d/%d/%d", &second.month, &second.day, &second.year);

  if (compare_dates(first, second) < 0)
    printf("%d/%d/%02d is earlier than %d/%d/%02d\n", first.month,
           first.day, first.year, second.month, second.day, second.year);
  else if (compare_dates(first, second) > 0)
    printf("%d/%d/%02d is earlier than %d/%d/%02d\n", second.month,
           second.day, second.year, first.month, first.day, first.year);
  else
    printf("The dates are the same.\n");
  return 0;
}

int compare_dates(struct date d1, struct date d2) {
  if (d1.year != d2.year)
    return d1.year < d2.year ? -1 : 1;
  if (d1.month != d2.month)
    return d1.month < d2.month ? -1 : 1;
  if (d1.day != d2.day)
    return d1.day < d2.day ? -1 : 1;
  return 0;
}
