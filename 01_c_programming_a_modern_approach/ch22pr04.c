#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  FILE *fp;
  int ch, last = '\n';
  unsigned long characters = 0, words = 0, lines = 0;
  bool in_word = false;

  if (argc != 2) {
    fprintf(stderr, "usage: %s filename\n", argv[0]);
    return EXIT_FAILURE;
  }
  fp = fopen(argv[1], "r");
  if (fp == NULL) {
    fprintf(stderr, "Can't open %s\n", argv[1]);
    return EXIT_FAILURE;
  }

  while ((ch = getc(fp)) != EOF) {
    characters++;
    if (ch == '\n')
      lines++;
    if (isspace((unsigned char)ch)) {
      in_word = false;
    } else if (!in_word) {
      words++;
      in_word = true;
    }
    last = ch;
  }
  if (characters > 0 && last != '\n')
    lines++;

  if (ferror(fp)) {
    fprintf(stderr, "Can't read %s\n", argv[1]);
    fclose(fp);
    return EXIT_FAILURE;
  }
  fclose(fp);
  printf("Characters: %lu\nWords: %lu\nLines: %lu\n", characters, words,
         lines);
  return EXIT_SUCCESS;
}
