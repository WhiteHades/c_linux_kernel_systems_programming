#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum conversion { WINDOWS_TO_UNIX, UNIX_TO_WINDOWS };

static const char *base_name(const char *path) {
  const char *slash = strrchr(path, '/');

  return slash == NULL ? path : slash + 1;
}

static enum conversion detect_conversion(FILE *input) {
  int previous = EOF;
  int ch;

  while ((ch = getc(input)) != EOF) {
    if (previous == '\r' && ch == '\n') {
      rewind(input);
      return WINDOWS_TO_UNIX;
    }
    previous = ch;
  }
  rewind(input);
  return UNIX_TO_WINDOWS;
}

static int convert_windows_to_unix(FILE *input, FILE *output) {
  int ch;

  while ((ch = getc(input)) != EOF) {
    if (ch == '\r') {
      int next = getc(input);

      if (next == '\n')
        ch = '\n';
      else if (next != EOF)
        ungetc(next, input);
    }
    if (putc(ch, output) == EOF)
      return 0;
  }
  return !ferror(input);
}

static int convert_unix_to_windows(FILE *input, FILE *output) {
  int ch;

  while ((ch = getc(input)) != EOF) {
    if (ch == '\n' && putc('\r', output) == EOF)
      return 0;
    if (putc(ch, output) == EOF)
      return 0;
  }
  return !ferror(input);
}

int main(int argc, char *argv[]) {
  FILE *input, *output;
  enum conversion mode;
  const char *program = base_name(argv[0]);
  int success;

  if (argc != 3) {
    fprintf(stderr, "usage: %s input-file output-file\n", argv[0]);
    return EXIT_FAILURE;
  }
  input = fopen(argv[1], "rb");
  output = fopen(argv[2], "wb");
  if (input == NULL || output == NULL) {
    fprintf(stderr, "Can't open input or output file\n");
    if (input != NULL)
      fclose(input);
    if (output != NULL)
      fclose(output);
    return EXIT_FAILURE;
  }

  if (strcmp(program, "win2unix") == 0)
    mode = WINDOWS_TO_UNIX;
  else if (strcmp(program, "unix2win") == 0)
    mode = UNIX_TO_WINDOWS;
  else
    mode = detect_conversion(input);

  success = mode == WINDOWS_TO_UNIX
                ? convert_windows_to_unix(input, output)
                : convert_unix_to_windows(input, output);
  if (ferror(output) || fclose(output) == EOF)
    success = 0;
  fclose(input);
  if (!success) {
    fprintf(stderr, "File input/output error\n");
    return EXIT_FAILURE;
  }
  printf("Converted %s to %s line endings\n", argv[1],
         mode == WINDOWS_TO_UNIX ? "UNIX" : "Windows");
  return EXIT_SUCCESS;
}
