#include <stdio.h>

int main(void) {
  const char *months[] = {"", "January", "February", "March", "April",
    "May", "June", "July", "August", "September", "October", "November",
    "December"};
  int month, day, year;

  printf("Enter a date (mm/dd/yyyy): ");
  scanf("%d/%d/%d", &month, &day, &year);
  if (month < 1 || month > 12) {
    printf("Invalid month.\n");
    return 1;
  }
  printf("You entered the date %s %d, %d\n", months[month], day, year);
  return 0;
}
