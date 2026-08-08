#include <stdio.h>
#include <stdlib.h>

#define MAX_FLIGHTS 100

struct flight {
  int departure;
  int arrival;
};

static void print_time(int minutes) {
  int hour = minutes / 60;
  int minute = minutes % 60;
  const char *suffix = hour < 12 ? "a.m." : "p.m.";

  hour %= 12;
  if (hour == 0)
    hour = 12;
  printf("%d:%02d %s", hour, minute, suffix);
}

int main(void) {
  struct flight flights[MAX_FLIGHTS];
  FILE *fp = fopen("flights.dat", "r");
  int count = 0, dep_hour, dep_minute, arr_hour, arr_minute;
  int hour, minute, requested, closest = 0;

  if (fp == NULL) {
    fprintf(stderr, "Can't open flights.dat\n");
    return EXIT_FAILURE;
  }
  while (count < MAX_FLIGHTS &&
         fscanf(fp, "%d:%d %d:%d", &dep_hour, &dep_minute, &arr_hour,
                &arr_minute) == 4) {
    flights[count].departure = dep_hour * 60 + dep_minute;
    flights[count].arrival = arr_hour * 60 + arr_minute;
    count++;
  }
  if (ferror(fp) || count == 0) {
    fprintf(stderr, "No valid flights found\n");
    fclose(fp);
    return EXIT_FAILURE;
  }
  fclose(fp);

  printf("Enter a 24-hour time: ");
  if (scanf("%d:%d", &hour, &minute) != 2 || hour < 0 || hour > 23 ||
      minute < 0 || minute > 59) {
    fprintf(stderr, "Invalid time\n");
    return EXIT_FAILURE;
  }
  requested = hour * 60 + minute;
  for (int i = 1; i < count; i++)
    if (abs(flights[i].departure - requested) <
        abs(flights[closest].departure - requested))
      closest = i;

  printf("Closest departure time is ");
  print_time(flights[closest].departure);
  printf(", arriving at ");
  print_time(flights[closest].arrival);
  printf("\n");
  return EXIT_SUCCESS;
}
