#include <stdio.h>
#include <stdlib.h>

#define FLIGHTS 8

int main(void) {
  const int departures[FLIGHTS] = {480, 583, 679, 767, 840, 945, 1140, 1305};
  const int arrivals[FLIGHTS] = {616, 712, 811, 900, 968, 1075, 1280, 1438};
  int hour, minute, desired, closest = 0;

  printf("Enter a 24-hour time: ");
  scanf("%d:%d", &hour, &minute);
  desired = hour * 60 + minute;

  for (int i = 1; i < FLIGHTS; i++)
    if (abs(desired - departures[i]) < abs(desired - departures[closest]))
      closest = i;

  int departure_hour = departures[closest] / 60;
  int arrival_hour = arrivals[closest] / 60;
  printf("Closest departure time is %d:%02d %s, arriving at %d:%02d %s.\n",
         departure_hour % 12 == 0 ? 12 : departure_hour % 12,
         departures[closest] % 60, departure_hour < 12 ? "a.m." : "p.m.",
         arrival_hour % 12 == 0 ? 12 : arrival_hour % 12,
         arrivals[closest] % 60, arrival_hour < 12 ? "a.m." : "p.m.");

  return 0;
}
