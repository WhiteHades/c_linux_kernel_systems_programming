#include <stdio.h>

#define N 10

void quicksort(int *low, int *high);
int *split(int *low, int *high);

int main(void) {
  int numbers[N];

  printf("Enter %d numbers to be sorted: ", N);
  for (int *p = numbers; p < numbers + N; p++)
    scanf("%d", p);

  quicksort(numbers, numbers + N - 1);
  printf("In sorted order:");
  for (int *p = numbers; p < numbers + N; p++)
    printf(" %d", *p);
  printf("\n");
  return 0;
}

void quicksort(int *low, int *high) {
  if (low >= high)
    return;
  int *middle = split(low, high);
  if (middle > low)
    quicksort(low, middle - 1);
  if (middle < high)
    quicksort(middle + 1, high);
}

int *split(int *low, int *high) {
  int partition = *low;

  for (;;) {
    while (low < high && partition <= *high)
      high--;
    if (low >= high)
      break;
    *low++ = *high;

    while (low < high && *low <= partition)
      low++;
    if (low >= high)
      break;
    *high-- = *low;
  }
  *high = partition;
  return high;
}
