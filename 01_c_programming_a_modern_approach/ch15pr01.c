#include <stdio.h>
#include <string.h>

#define MAX_LINE_LEN 60
#define MAX_WORD_LEN 20

char line[MAX_LINE_LEN + 1];
int line_len, num_words, wider_gaps_first;

void clear_line(void);
void add_word(const char *word);
int space_remaining(void);
void write_line(void);
void flush_line(void);
void read_word(char *word, int len);

int main(void) {
  char word[MAX_WORD_LEN + 2];
  int word_len;

  clear_line();
  for (;;) {
    read_word(word, MAX_WORD_LEN + 1);
    word_len = strlen(word);
    if (word_len == 0) {
      flush_line();
      return 0;
    }
    if (word_len > MAX_WORD_LEN)
      word[MAX_WORD_LEN] = '*';
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
  int gaps = num_words - 1, extra = MAX_LINE_LEN - line_len;
  int base = gaps > 0 ? extra / gaps : 0;
  int larger = gaps > 0 ? extra % gaps : 0;
  int gap = 0, i, j;

  for (i = 0; i < line_len; i++) {
    putchar(line[i]);
    if (line[i] == ' ') {
      int add_large = wider_gaps_first ? gap < larger : gap >= gaps - larger;
      for (j = 0; j < base + add_large; j++)
        putchar(' ');
      gap++;
    }
  }
  putchar('\n');
  wider_gaps_first = !wider_gaps_first;
}

void flush_line(void) {
  if (line_len > 0)
    puts(line);
}

void read_word(char *word, int len) {
  int ch, pos = 0;

  while ((ch = getchar()) == ' ' || ch == '\n' || ch == '\t')
    ;
  while (ch != ' ' && ch != '\n' && ch != '\t' && ch != EOF) {
    if (pos < len)
      word[pos++] = (char) ch;
    ch = getchar();
  }
  word[pos] = '\0';
}
