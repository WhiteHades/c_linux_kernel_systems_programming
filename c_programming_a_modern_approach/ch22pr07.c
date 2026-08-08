#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool has_rle_extension(const char *name) {
  size_t length = strlen(name);

  return length >= 4 && strcmp(name + length - 4, ".rle") == 0;
}

static const char *base_name(const char *path) {
  const char *slash = strrchr(path, '/');

  return slash == NULL ? path : slash + 1;
}

static int compress_file(const char *input_name) {
  size_t length = strlen(input_name);
  char *output_name = malloc(length + 5);
  FILE *input, *output;
  int current, next;

  if (output_name == NULL)
    return EXIT_FAILURE;
  sprintf(output_name, "%s.rle", input_name);
  input = fopen(input_name, "rb");
  if (input == NULL) {
    fprintf(stderr, "Can't open %s\n", input_name);
    free(output_name);
    return EXIT_FAILURE;
  }
  output = fopen(output_name, "wb");
  if (output == NULL) {
    fprintf(stderr, "Can't open %s\n", output_name);
    fclose(input);
    free(output_name);
    return EXIT_FAILURE;
  }

  current = getc(input);
  while (current != EOF) {
    unsigned int count = 1;

    while (count < UCHAR_MAX && (next = getc(input)) == current)
      count++;
    if (putc((int)count, output) == EOF || putc(current, output) == EOF)
      break;
    if (count == UCHAR_MAX)
      next = getc(input);
    current = next;
  }

  if (ferror(input) || ferror(output) || fclose(output) == EOF) {
    fprintf(stderr, "File input/output error\n");
    fclose(input);
    free(output_name);
    return EXIT_FAILURE;
  }
  fclose(input);
  printf("Compressed file: %s\n", output_name);
  free(output_name);
  return EXIT_SUCCESS;
}

static int uncompress_file(const char *input_name) {
  size_t length = strlen(input_name);
  char *output_name;
  FILE *input, *output;
  int count, byte;

  if (!has_rle_extension(input_name)) {
    fprintf(stderr, "Compressed file must have a .rle extension\n");
    return EXIT_FAILURE;
  }
  output_name = malloc(length - 3);
  if (output_name == NULL)
    return EXIT_FAILURE;
  memcpy(output_name, input_name, length - 4);
  output_name[length - 4] = '\0';
  input = fopen(input_name, "rb");
  if (input == NULL) {
    fprintf(stderr, "Can't open %s\n", input_name);
    free(output_name);
    return EXIT_FAILURE;
  }
  output = fopen(output_name, "wb");
  if (output == NULL) {
    fprintf(stderr, "Can't open %s\n", output_name);
    fclose(input);
    free(output_name);
    return EXIT_FAILURE;
  }

  while ((count = getc(input)) != EOF) {
    byte = getc(input);
    if (byte == EOF || count == 0) {
      fprintf(stderr, "Malformed compressed file\n");
      fclose(input);
      fclose(output);
      free(output_name);
      return EXIT_FAILURE;
    }
    for (int i = 0; i < count; i++)
      if (putc(byte, output) == EOF)
        break;
  }

  if (ferror(input) || ferror(output) || fclose(output) == EOF) {
    fprintf(stderr, "File input/output error\n");
    fclose(input);
    free(output_name);
    return EXIT_FAILURE;
  }
  fclose(input);
  printf("Uncompressed file: %s\n", output_name);
  free(output_name);
  return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
  bool uncompress;

  if (argc != 2) {
    fprintf(stderr, "usage: %s file\n", argv[0]);
    return EXIT_FAILURE;
  }
  uncompress = strcmp(base_name(argv[0]), "uncompress_file") == 0 ||
               (strcmp(base_name(argv[0]), "compress_file") != 0 &&
                has_rle_extension(argv[1]));
  return uncompress ? uncompress_file(argv[1]) : compress_file(argv[1]);
}
