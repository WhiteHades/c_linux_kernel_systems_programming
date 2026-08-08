#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LEN 25

struct part {
  int number;
  char name[NAME_LEN + 1];
  int on_hand;
};

static int read_part(FILE *fp, struct part *part) {
  size_t count = fread(part, sizeof(*part), 1, fp);

  if (count == 1)
    return 1;
  if (ferror(fp))
    return -1;
  return 0;
}

static int write_part(FILE *fp, const struct part *part) {
  return fwrite(part, sizeof(*part), 1, fp) == 1;
}

int main(int argc, char *argv[]) {
  FILE *first_file, *second_file, *output_file;
  struct part first, second;
  int have_first, have_second;
  int status = EXIT_SUCCESS;

  if (argc != 4) {
    fprintf(stderr, "usage: %s input1 input2 output\n", argv[0]);
    return EXIT_FAILURE;
  }
  first_file = fopen(argv[1], "rb");
  second_file = fopen(argv[2], "rb");
  output_file = fopen(argv[3], "wb");
  if (first_file == NULL || second_file == NULL || output_file == NULL) {
    fprintf(stderr, "Can't open one or more files\n");
    if (first_file != NULL)
      fclose(first_file);
    if (second_file != NULL)
      fclose(second_file);
    if (output_file != NULL)
      fclose(output_file);
    return EXIT_FAILURE;
  }

  have_first = read_part(first_file, &first);
  have_second = read_part(second_file, &second);
  while (have_first == 1 || have_second == 1) {
    struct part merged;

    if (have_second != 1 ||
        (have_first == 1 && first.number < second.number)) {
      merged = first;
      have_first = read_part(first_file, &first);
    } else if (have_first != 1 || second.number < first.number) {
      merged = second;
      have_second = read_part(second_file, &second);
    } else {
      if (strcmp(first.name, second.name) != 0) {
        fprintf(stderr, "Part %d has inconsistent names: %s and %s\n",
                first.number, first.name, second.name);
        status = EXIT_FAILURE;
        break;
      }
      merged = first;
      merged.on_hand += second.on_hand;
      have_first = read_part(first_file, &first);
      have_second = read_part(second_file, &second);
    }
    if (!write_part(output_file, &merged)) {
      fprintf(stderr, "Error writing %s\n", argv[3]);
      status = EXIT_FAILURE;
      break;
    }
  }
  if (have_first < 0 || have_second < 0) {
    fprintf(stderr, "Error reading an input file\n");
    status = EXIT_FAILURE;
  }
  if (fclose(output_file) == EOF)
    status = EXIT_FAILURE;
  fclose(first_file);
  fclose(second_file);
  return status;
}
