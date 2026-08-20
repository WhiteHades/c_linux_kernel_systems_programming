#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN 60
#define MAX_WORD_LEN 20

static FILE *input_file;
static FILE *output_file;
static char line[MAX_LINE_LEN + 1];
static int line_len;
static int num_words;

static void clear_line(void) {
  line[0] = '\0';
  line_len = 0;
  num_words = 0;
}

static void add_word(const char *word) {
  if (num_words > 0) {
    line[line_len++] = ' ';
    line[line_len] = '\0';
  }
  strcat(line, word);
  line_len += (int)strlen(word);
  num_words++;
}

static int space_remaining(void) { return MAX_LINE_LEN - line_len; }

static void write_line(void) {
  int extra_spaces = MAX_LINE_LEN - line_len;
  int words_left = num_words;

  for (int i = 0; i < line_len; i++) {
    if (line[i] != ' ') {
      putc(line[i], output_file);
    } else {
      int spaces = extra_spaces / (words_left - 1);

      for (int j = 0; j <= spaces; j++)
        putc(' ', output_file);
      extra_spaces -= spaces;
      words_left--;
    }
  }
  putc('\n', output_file);
}

static void flush_line(void) {
  if (line_len > 0)
    fprintf(output_file, "%s\n", line);
}

static void read_word(char *word, int limit) {
  int ch, pos = 0;

  do {
    ch = getc(input_file);
  } while (ch != EOF && isspace((unsigned char)ch));
  while (ch != EOF && !isspace((unsigned char)ch)) {
    if (pos < limit)
      word[pos++] = (char)ch;
    ch = getc(input_file);
  }
  word[pos] = '\0';
}

int main(int argc, char *argv[]) {
  char word[MAX_WORD_LEN + 2];

  if (argc != 3) {
    fprintf(stderr, "usage: %s input-file output-file\n", argv[0]);
    return EXIT_FAILURE;
  }
  input_file = fopen(argv[1], "r");
  output_file = fopen(argv[2], "w");
  if (input_file == NULL || output_file == NULL) {
    fprintf(stderr, "Can't open input or output file\n");
    if (input_file != NULL)
      fclose(input_file);
    if (output_file != NULL)
      fclose(output_file);
    return EXIT_FAILURE;
  }

  clear_line();
  for (;;) {
    int word_len;

    read_word(word, MAX_WORD_LEN + 1);
    word_len = (int)strlen(word);
    if (word_len == 0)
      break;
    if (word_len > MAX_WORD_LEN)
      word[MAX_WORD_LEN] = '*';
    if (word_len + 1 > space_remaining()) {
      write_line();
      clear_line();
    }
    add_word(word);
  }
  flush_line();

  if (ferror(input_file) || ferror(output_file) || fclose(output_file) == EOF) {
    fprintf(stderr, "File input/output error\n");
    fclose(input_file);
    return EXIT_FAILURE;
  }
  fclose(input_file);
  return EXIT_SUCCESS;
}
