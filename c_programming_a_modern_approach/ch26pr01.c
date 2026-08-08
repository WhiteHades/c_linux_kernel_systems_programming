#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int i;

  for (i = 0; i < 1000; i++) {
    putchar('0' + rand() % 2);
    if ((i + 1) % 80 == 0 || i == 999)
      putchar('\n');
  }

  return 0;
}
