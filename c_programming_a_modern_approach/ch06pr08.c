#include <stdio.h>

int main(void) {
  int day, number_of_days, starting_day;

  printf("Enter number of days in month: ");
  scanf("%d", &number_of_days);

  printf("Enter starting day of the week (1=Sun, 7=Sat): ");
  scanf("%d", &starting_day);

  for (day = 1; day < starting_day; day++)
    printf("   ");

  for (day = 1; day <= number_of_days; day++) {
    printf("%2d ", day);

    if ((day + starting_day - 1) % 7 == 0)
      printf("\n");
  }

  if ((number_of_days + starting_day - 1) % 7 != 0)
    printf("\n");

  return 0;
}
