#include <stdio.h>

int main(void) {
  int first, second, third, fourth;
  int larger_pair_one, smaller_pair_one, larger_pair_two, smaller_pair_two;
  int largest, smallest;

  printf("Enter four integers: ");
  scanf("%d%d%d%d", &first, &second, &third, &fourth);

  if (first > second) {
    larger_pair_one = first;
    smaller_pair_one = second;
  } else {
    larger_pair_one = second;
    smaller_pair_one = first;
  }

  if (third > fourth) {
    larger_pair_two = third;
    smaller_pair_two = fourth;
  } else {
    larger_pair_two = fourth;
    smaller_pair_two = third;
  }

  if (larger_pair_one > larger_pair_two)
    largest = larger_pair_one;
  else
    largest = larger_pair_two;

  if (smaller_pair_one < smaller_pair_two)
    smallest = smaller_pair_one;
  else
    smallest = smaller_pair_two;

  printf("Largest: %d\n", largest);
  printf("Smallest: %d\n", smallest);

  return 0;
}
