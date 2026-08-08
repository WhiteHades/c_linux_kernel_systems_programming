#include <stdio.h>

struct flight {
  int departure;
  int arrival;
};

void print_time(int minutes);

int main(void) {
  const struct flight flights[] = {
    {480, 616}, {583, 712}, {679, 811}, {767, 900},
    {840, 968}, {945, 1075}, {1140, 1280}, {1305, 1438}
  };
  int hour, minute, desired, closest = 0, i;
  int count = sizeof(flights) / sizeof(flights[0]);

  printf("Enter a 24-hour time: ");
  scanf("%d:%d", &hour, &minute);
  desired = hour * 60 + minute;
  for (i = 1; i < count; i++)
    if ((flights[i].departure > desired ? flights[i].departure - desired :
         desired - flights[i].departure) <
        (flights[closest].departure > desired ?
         flights[closest].departure - desired :
         desired - flights[closest].departure))
      closest = i;

  printf("Closest departure time is ");
  print_time(flights[closest].departure);
  printf(", arriving at ");
  print_time(flights[closest].arrival);
  putchar('\n');
  return 0;
}

void print_time(int minutes) {
  int hour = minutes / 60;
  printf("%d:%02d %s", hour % 12 == 0 ? 12 : hour % 12,
         minutes % 60, hour < 12 ? "a.m." : "p.m.");
}
