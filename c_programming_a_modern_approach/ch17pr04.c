#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN 60
#define MAX_WORD_LEN 20

struct word_node {
  char word[MAX_WORD_LEN + 2];
  struct word_node *next;
};

struct word_node *line;
int line_len, num_words;

void clear_line(void);
void add_word(const char *word);
int space_remaining(void);
void write_line(void);
void flush_line(void);
void read_word(char *word, int len);

int main(void) {
  char word[MAX_WORD_LEN + 2];
  int length;

  for (;;) {
    read_word(word, MAX_WORD_LEN + 1);
    length = strlen(word);
    if (length == 0) {
      flush_line();
      return 0;
    }
    if (length > MAX_WORD_LEN)
      word[MAX_WORD_LEN] = '*';
    if (length + 1 > space_remaining()) {
      write_line();
      clear_line();
    }
    add_word(word);
  }
}

void clear_line(void) {
  while (line != NULL) {
    struct word_node *next = line->next;
    free(line);
    line = next;
  }
  line_len = 0;
  num_words = 0;
}

void add_word(const char *word) {
  struct word_node *node = malloc(sizeof(*node)), **p = &line;
  if (node == NULL) {
    printf("Unable to allocate line.\n");
    exit(EXIT_FAILURE);
  }
  strcpy(node->word, word);
  node->next = NULL;
  while (*p != NULL)
    p = &(*p)->next;
  *p = node;
  line_len += strlen(word) + (num_words > 0);
  num_words++;
}

int space_remaining(void) {
  return MAX_LINE_LEN - line_len;
}

void write_line(void) {
  struct word_node *p;
  int extra = MAX_LINE_LEN - line_len, words = num_words;

  for (p = line; p != NULL; p = p->next) {
    fputs(p->word, stdout);
    if (p->next != NULL) {
      int spaces = 1 + extra / (words - 1), i;
      for (i = 0; i < spaces; i++)
        putchar(' ');
      extra -= spaces - 1;
      words--;
    }
  }
  putchar('\n');
}

void flush_line(void) {
  struct word_node *p;
  for (p = line; p != NULL; p = p->next)
    printf("%s%s", p->word, p->next == NULL ? "\n" : " ");
  clear_line();
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
