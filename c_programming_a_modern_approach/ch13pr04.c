#include <stdio.h>

int main(int argc, char *argv[]) {
  int i;

  for (i = argc - 1; i >= 1; i--)
    printf("%s%s", argv[i], i == 1 ? "\n" : " ");
  return 0;
}
