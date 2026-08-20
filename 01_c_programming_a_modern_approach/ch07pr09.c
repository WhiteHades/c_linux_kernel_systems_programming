#include <ctype.h>
#include <stdio.h>

int main(void) {
  int hour, minute;
  char period;

  printf("Enter a 12-hour time: ");
  scanf("%d:%d %c", &hour, &minute, &period);

  period = toupper(period);
  if (period == 'A') {
    if (hour == 12)
      hour = 0;
  } else if (hour != 12) {
    hour += 12;
  }

  printf("Equivalent 24-hour time: %02d:%02d\n", hour, minute);

  return 0;
}
