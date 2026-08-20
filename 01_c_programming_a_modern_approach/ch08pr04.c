#include <stdio.h>

int main(void) {
  int numbers[10];
#define LENGTH ((int)(sizeof(numbers) / sizeof(numbers[0])))

  printf("Enter %d numbers: ", LENGTH);
  for (int i = 0; i < LENGTH; i++)
    scanf("%d", &numbers[i]);

  printf("In reverse order:");
  for (int i = LENGTH - 1; i >= 0; i--)
    printf(" %d", numbers[i]);
  printf("\n");

  return 0;
}
