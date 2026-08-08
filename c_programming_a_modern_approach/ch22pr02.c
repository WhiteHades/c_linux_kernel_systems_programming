#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  FILE *fp;
  int ch;

  if (argc != 2) {
    fprintf(stderr, "usage: %s filename\n", argv[0]);
    return EXIT_FAILURE;
  }
  fp = fopen(argv[1], "rb");
  if (fp == NULL) {
    fprintf(stderr, "Can't open %s\n", argv[1]);
    return EXIT_FAILURE;
  }

  while ((ch = getc(fp)) != EOF)
    putchar(toupper((unsigned char)ch));

  if (ferror(fp) || ferror(stdout)) {
    fprintf(stderr, "File input/output error\n");
    fclose(fp);
    return EXIT_FAILURE;
  }
  fclose(fp);
  return EXIT_SUCCESS;
}
