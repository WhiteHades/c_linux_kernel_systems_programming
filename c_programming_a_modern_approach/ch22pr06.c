#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define BYTES_PER_LINE 10

int main(int argc, char *argv[]) {
  FILE *fp;
  unsigned long offset = 0;
  unsigned char bytes[BYTES_PER_LINE];
  size_t count;

  if (argc != 2) {
    fprintf(stderr, "usage: %s filename\n", argv[0]);
    return EXIT_FAILURE;
  }
  fp = fopen(argv[1], "rb");
  if (fp == NULL) {
    fprintf(stderr, "Can't open %s\n", argv[1]);
    return EXIT_FAILURE;
  }

  printf("Offset   Bytes                         Characters\n");
  printf("------   ----------------------------- ----------\n");
  while ((count = fread(bytes, 1, sizeof(bytes), fp)) > 0) {
    printf("%6lu   ", offset);
    for (size_t i = 0; i < sizeof(bytes); i++) {
      if (i < count)
        printf("%02X ", bytes[i]);
      else
        printf("   ");
    }
    putchar(' ');
    for (size_t i = 0; i < count; i++)
      putchar(isprint(bytes[i]) ? bytes[i] : '.');
    putchar('\n');
    offset += count;
  }

  if (ferror(fp)) {
    fprintf(stderr, "Can't read %s\n", argv[1]);
    fclose(fp);
    return EXIT_FAILURE;
  }
  fclose(fp);
  return EXIT_SUCCESS;
}
