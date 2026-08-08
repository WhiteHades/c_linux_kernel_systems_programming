#include <stdio.h>
#include <string.h>

#define MAX_LINE_LEN 60
#define MAX_WORD_LEN 20

char line[MAX_LINE_LEN + 1];
int line_len, num_words;

void clear_line(void);
void add_word(const char *word);
int space_remaining(void);
void write_line(void);
void flush_line(void);
int read_word(char *word, int len);

int main(void) {
  char word[MAX_WORD_LEN + 2];
  int word_len;

  clear_line();
  for (;;) {
    word_len = read_word(word, MAX_WORD_LEN + 1);
    if (word_len == 0) {
      flush_line();
      return 0;
    }
    if (word_len + 1 > space_remaining()) {
      write_line();
      clear_line();
    }
    add_word(word);
  }
}

void clear_line(void) {
  line[0] = '\0';
  line_len = 0;
  num_words = 0;
}

void add_word(const char *word) {
  if (num_words > 0) {
    strcat(line, " ");
    line_len++;
  }
  strcat(line, word);
  line_len += strlen(word);
  num_words++;
}

int space_remaining(void) {
  return MAX_LINE_LEN - line_len;
}

void write_line(void) {
  int extra = MAX_LINE_LEN - line_len, words = num_words, i, j, spaces;

  for (i = 0; i < line_len; i++) {
    if (line[i] != ' ')
      putchar(line[i]);
    else {
      spaces = extra / (words - 1);
      for (j = 0; j <= spaces; j++)
        putchar(' ');
      extra -= spaces;
      words--;
    }
  }
  putchar('\n');
}

void flush_line(void) {
  if (line_len > 0)
    puts(line);
}

int read_word(char *word, int len) {
  int ch, pos = 0, truncated = 0;

  while ((ch = getchar()) == ' ' || ch == '\n' || ch == '\t')
    ;
  while (ch != ' ' && ch != '\n' && ch != '\t' && ch != EOF) {
    if (pos < len)
      word[pos++] = (char) ch;
    else
      truncated = 1;
    ch = getchar();
  }
  if (truncated || pos > MAX_WORD_LEN) {
    pos = MAX_WORD_LEN + 1;
    word[MAX_WORD_LEN] = '*';
  }
  word[pos] = '\0';
  return pos;
}
