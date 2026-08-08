#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 512

int main(int argc, char *argv[]) {
  FILE *source, *destination;
  unsigned char block[BLOCK_SIZE];
  size_t count;
  int status = EXIT_SUCCESS;

  if (argc != 3) {
    fprintf(stderr, "usage: %s source destination\n", argv[0]);
    return EXIT_FAILURE;
  }
  source = fopen(argv[1], "rb");
  if (source == NULL) {
    fprintf(stderr, "Can't open %s\n", argv[1]);
    return EXIT_FAILURE;
  }
  destination = fopen(argv[2], "wb");
  if (destination == NULL) {
    fprintf(stderr, "Can't open %s\n", argv[2]);
    fclose(source);
    return EXIT_FAILURE;
  }

  while ((count = fread(block, 1, sizeof(block), source)) > 0)
    if (fwrite(block, 1, count, destination) != count) {
      fprintf(stderr, "Error writing %s\n", argv[2]);
      status = EXIT_FAILURE;
      break;
    }
  if (ferror(source)) {
    fprintf(stderr, "Error reading %s\n", argv[1]);
    status = EXIT_FAILURE;
  }
  if (fclose(destination) == EOF)
    status = EXIT_FAILURE;
  fclose(source);
  return status;
}
