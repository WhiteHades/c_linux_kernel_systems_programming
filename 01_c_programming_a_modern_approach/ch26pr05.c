#include <stdio.h>
#include <time.h>

static time_t read_date(const char *prompt) {
  struct tm date = {0};
  int month, day, year;

  printf("%s", prompt);
  if (scanf("%d/%d/%d", &month, &day, &year) != 3)
    return (time_t) -1;

  date.tm_mon = month - 1;
  date.tm_mday = day;
  date.tm_year = year - 1900;
  date.tm_hour = 12;
  date.tm_isdst = -1;
  return mktime(&date);
}

int main(void) {
  time_t first = read_date("Enter first date (mm/dd/yyyy): ");
  time_t second;
  double days;
  long rounded_days;

  if (first == (time_t) -1)
    return 1;
  second = read_date("Enter second date (mm/dd/yyyy): ");
  if (second == (time_t) -1)
    return 1;

  days = difftime(second, first) / (60.0 * 60.0 * 24.0);
  rounded_days = (long) (days < 0.0 ? days - 0.5 : days + 0.5);
  if (rounded_days < 0)
    rounded_days = -rounded_days;

  printf("Difference: %ld days\n", rounded_days);
  return 0;
}
