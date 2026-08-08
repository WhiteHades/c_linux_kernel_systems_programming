#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int failures = 0;

  if (argc < 2) {
    fprintf(stderr, "usage: canopen filename...\n");
    return EXIT_FAILURE;
  }

  for (int i = 1; i < argc; i++) {
    FILE *fp = fopen(argv[i], "r");

    if (fp == NULL) {
      printf("%s can't be opened\n", argv[i]);
      failures++;
    } else {
      printf("%s can be opened\n", argv[i]);
      fclose(fp);
    }
  }

  return failures == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
