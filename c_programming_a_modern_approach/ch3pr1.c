#include <stdio.h>

int main(void)
{
  int month, date, year;

  printf("enter a date (mm/dd/yyyy): ");
  scanf("%d/%2d/%4d", &month, &date, &year);
  printf("you entered the date %04d%02d%02d\n", year, month, date);

  return 0;
}
