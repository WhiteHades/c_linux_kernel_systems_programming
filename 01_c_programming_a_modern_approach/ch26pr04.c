#include <stdio.h>
#include <time.h>

int main(void) {
  struct tm date = {0};
  int month, day, year, days_later;

  printf("Enter a date (mm/dd/yyyy): ");
  if (scanf("%d/%d/%d", &month, &day, &year) != 3)
    return 1;
  printf("Enter number of days later: ");
  if (scanf("%d", &days_later) != 1)
    return 1;

  date.tm_mon = month - 1;
  date.tm_mday = day + days_later;
  date.tm_year = year - 1900;
  date.tm_isdst = -1;

  if (mktime(&date) == (time_t) -1) {
    printf("Date is outside the supported range\n");
    return 1;
  }

  printf("Date %d days later: %02d/%02d/%d\n", days_later,
         date.tm_mon + 1, date.tm_mday, date.tm_year + 1900);
  return 0;
}
