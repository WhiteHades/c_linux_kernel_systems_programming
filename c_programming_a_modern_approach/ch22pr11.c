#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  static const char *months[] = {
      "January", "February", "March",     "April",   "May",      "June",
      "July",    "August",   "September", "October", "November", "December"};
  int month, day, year, consumed = 0;
  size_t length;

  if (argc != 2) {
    fprintf(stderr, "usage: %s date\n", argv[0]);
    return EXIT_FAILURE;
  }
  length = strlen(argv[1]);
  if ((sscanf(argv[1], "%d-%d-%d%n", &month, &day, &year, &consumed) != 3 ||
       (size_t)consumed != length) &&
      (sscanf(argv[1], "%d/%d/%d%n", &month, &day, &year, &consumed) != 3 ||
       (size_t)consumed != length)) {
    fprintf(stderr, "Date must have the form m-d-y or m/d/y\n");
    return EXIT_FAILURE;
  }
  if (month < 1 || month > 12 || day < 1 || day > 31) {
    fprintf(stderr, "Date contains an invalid month or day\n");
    return EXIT_FAILURE;
  }
  printf("%s %d, %d\n", months[month - 1], day, year);
  return EXIT_SUCCESS;
}
