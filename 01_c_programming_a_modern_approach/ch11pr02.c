#include <stdio.h>
#include <stdlib.h>

#define FLIGHTS 8

void find_closest_flight(int desired_time, int *departure_time,
                         int *arrival_time);
void print_time(int time);

int main(void) {
  int hour, minute, departure, arrival;

  printf("Enter a 24-hour time: ");
  scanf("%d:%d", &hour, &minute);
  find_closest_flight(hour * 60 + minute, &departure, &arrival);

  printf("Closest departure time is ");
  print_time(departure);
  printf(", arriving at ");
  print_time(arrival);
  printf(".\n");
  return 0;
}

void find_closest_flight(int desired_time, int *departure_time,
                         int *arrival_time) {
  const int departures[FLIGHTS] = {480, 583, 679, 767, 840, 945, 1140, 1305};
  const int arrivals[FLIGHTS] = {616, 712, 811, 900, 968, 1075, 1280, 1438};
  int closest = 0;

  for (int i = 1; i < FLIGHTS; i++)
    if (abs(desired_time - departures[i]) <
        abs(desired_time - departures[closest]))
      closest = i;
  *departure_time = departures[closest];
  *arrival_time = arrivals[closest];
}

void print_time(int time) {
  int hour = time / 60;
  printf("%d:%02d %s", hour % 12 == 0 ? 12 : hour % 12, time % 60,
         hour < 12 ? "a.m." : "p.m.");
}
