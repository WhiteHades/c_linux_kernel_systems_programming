#include <stdio.h>
#include <stdlib.h>

static void print_folks(void) {
  printf("folks!\n");
}

static void print_thats_all(void) {
  printf("That's all, ");
}

int main(void) {
  if (atexit(print_folks) != 0 || atexit(print_thats_all) != 0) {
    printf("Unable to register exit function\n");
    return 1;
  }

  return 0;
}
