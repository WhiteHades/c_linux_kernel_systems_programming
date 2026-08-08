#include <stdio.h>
#include <stdlib.h>

#define MAX_NUMBERS 10000

static int compare_ints(const void *left, const void *right) {
  int a = *(const int *)left;
  int b = *(const int *)right;

  return (a > b) - (a < b);
}

int main(int argc, char *argv[]) {
  FILE *fp;
  int numbers[MAX_NUMBERS];
  int count = 0;
  long median;

  if (argc != 2) {
    fprintf(stderr, "usage: %s filename\n", argv[0]);
    return EXIT_FAILURE;
  }
  fp = fopen(argv[1], "r");
  if (fp == NULL) {
    fprintf(stderr, "Can't open %s\n", argv[1]);
    return EXIT_FAILURE;
  }
  while (count < MAX_NUMBERS && fscanf(fp, "%d", &numbers[count]) == 1)
    count++;
  if (ferror(fp)) {
    fprintf(stderr, "Error reading %s\n", argv[1]);
    fclose(fp);
    return EXIT_FAILURE;
  }
  fclose(fp);
  if (count == 0) {
    fprintf(stderr, "The file contains no integers\n");
    return EXIT_FAILURE;
  }

  qsort(numbers, (size_t)count, sizeof(numbers[0]), compare_ints);
  if (count % 2 == 1) {
    median = numbers[count / 2];
  } else {
    long sum = (long)numbers[count / 2 - 1] + numbers[count / 2];

    median = sum / 2;
    if (sum < 0 && sum % 2 != 0)
      median--;
  }
  printf("Largest: %d\nSmallest: %d\nMedian: %ld\n", numbers[count - 1],
         numbers[0], median);
  return EXIT_SUCCESS;
}
