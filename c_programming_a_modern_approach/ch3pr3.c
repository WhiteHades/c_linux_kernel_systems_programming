#include <stdio.h>

int main(void) {
  int isbn1, isbn2, isbn3, isbn4, isbn5;

  printf("enter isbn: ");
  scanf("%d-%d-%d-%d-%d", &isbn1, &isbn2, &isbn3, &isbn4, &isbn5);

  printf("gs1 prefix      : %d\n", isbn1);
  printf("group identifier: %d\n", isbn2);
  printf("publisher code  : %d\n", isbn3);
  printf("item number     : %d\n", isbn4);
  printf("check digit     : %d\n", isbn5);
}
