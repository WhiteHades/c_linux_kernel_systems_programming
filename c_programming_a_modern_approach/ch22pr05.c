#include <stdio.h>
#include <stdlib.h>

#define KEY '&'

int main(int argc, char *argv[]) {
  FILE *input, *output;
  int ch;

  if (argc != 3) {
    fprintf(stderr, "usage: %s input-file output-file\n", argv[0]);
    return EXIT_FAILURE;
  }
  input = fopen(argv[1], "rb");
  if (input == NULL) {
    fprintf(stderr, "Can't open %s\n", argv[1]);
    return EXIT_FAILURE;
  }
  output = fopen(argv[2], "wb");
  if (output == NULL) {
    fprintf(stderr, "Can't open %s\n", argv[2]);
    fclose(input);
    return EXIT_FAILURE;
  }

  while ((ch = getc(input)) != EOF)
    if (putc(ch ^ KEY, output) == EOF)
      break;

  if (ferror(input) || ferror(output) || fclose(output) == EOF) {
    fprintf(stderr, "File input/output error\n");
    fclose(input);
    return EXIT_FAILURE;
  }
  fclose(input);
  return EXIT_SUCCESS;
}
