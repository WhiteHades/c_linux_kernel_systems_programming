#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  FILE *fp;
  char line[256];

  if (argc != 2) {
    fprintf(stderr, "usage: %s filename\n", argv[0]);
    return EXIT_FAILURE;
  }
  fp = fopen(argv[1], "r");
  if (fp == NULL) {
    fprintf(stderr, "Can't open %s\n", argv[1]);
    return EXIT_FAILURE;
  }

  while (fgets(line, sizeof(line), fp) != NULL) {
    char digits[11];
    int count = 0;

    for (int i = 0; line[i] != '\0'; i++)
      if (isdigit((unsigned char)line[i]) && count < 10)
        digits[count++] = line[i];
    if (count == 10) {
      digits[10] = '\0';
      printf("(%c%c%c) %c%c%c-%c%c%c%c\n", digits[0], digits[1], digits[2],
             digits[3], digits[4], digits[5], digits[6], digits[7], digits[8],
             digits[9]);
    } else {
      fprintf(stderr, "Skipping line without 10 digits: %s", line);
    }
  }

  if (ferror(fp)) {
    fprintf(stderr, "Error reading %s\n", argv[1]);
    fclose(fp);
    return EXIT_FAILURE;
  }
  fclose(fp);
  return EXIT_SUCCESS;
}
