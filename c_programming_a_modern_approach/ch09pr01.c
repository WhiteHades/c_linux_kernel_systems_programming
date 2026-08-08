#include <stdio.h>

#define MAX_NUMBERS 100

void selection_sort(int numbers[], int length);

int main(void) {
  int numbers[MAX_NUMBERS], length;

  printf("How many integers? ");
  scanf("%d", &length);
  if (length < 1 || length > MAX_NUMBERS) {
    printf("Invalid count\n");
    return 1;
  }

  printf("Enter %d integers: ", length);
  for (int i = 0; i < length; i++)
    scanf("%d", &numbers[i]);

  selection_sort(numbers, length);
  printf("In sorted order:");
  for (int i = 0; i < length; i++)
    printf(" %d", numbers[i]);
  printf("\n");

  return 0;
}

void selection_sort(int numbers[], int length) {
  if (length <= 1)
    return;

  int largest = 0;
  for (int i = 1; i < length; i++)
    if (numbers[i] > numbers[largest])
      largest = i;

  int temp = numbers[length - 1];
  numbers[length - 1] = numbers[largest];
  numbers[largest] = temp;
  selection_sort(numbers, length - 1);
}
