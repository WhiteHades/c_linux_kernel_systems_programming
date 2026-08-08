#include <stdio.h>

#define N 10

void max_min(int a[], int n, int *max, int *min);

int main(void) {
  int numbers[N], largest, smallest;

  printf("Enter %d numbers: ", N);
  for (int *p = numbers; p < numbers + N; p++)
    scanf("%d", p);
  max_min(numbers, N, &largest, &smallest);
  printf("Largest: %d\nSmallest: %d\n", largest, smallest);
  return 0;
}

void max_min(int a[], int n, int *max, int *min) {
  *max = *min = *a;
  for (int *p = a + 1; p < a + n; p++) {
    if (*p > *max)
      *max = *p;
    else if (*p < *min)
      *min = *p;
  }
}
