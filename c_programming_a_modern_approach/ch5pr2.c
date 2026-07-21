#include <stdio.h>

int main(void) {
  int first, second;
  printf("enter 24 hour time (HH:MM): ");
  scanf("%d:%d", &first, &second);

  if (first > 12 && first <= 24)
    first = first - 12;

  printf("equivalent 12 hour time: %d:%d", first, second);
  if (first >= 12)
    printf(" PM\n");
  if (first < 12)
    printf(" AM\n");
}
