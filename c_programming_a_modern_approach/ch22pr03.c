#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int failed = 0;

  if (argc < 2) {
    fprintf(stderr, "usage: fcat filename...\n");
    return EXIT_FAILURE;
  }

  for (int i = 1; i < argc; i++) {
    FILE *fp = fopen(argv[i], "rb");
    int ch;

    if (fp == NULL) {
      fprintf(stderr, "Can't open %s\n", argv[i]);
      failed = 1;
      continue;
    }
    while ((ch = getc(fp)) != EOF)
      if (putchar(ch) == EOF)
        failed = 1;
    if (ferror(fp)) {
      fprintf(stderr, "Can't read %s\n", argv[i]);
      failed = 1;
    }
    fclose(fp);
  }

  return failed ? EXIT_FAILURE : EXIT_SUCCESS;
}
