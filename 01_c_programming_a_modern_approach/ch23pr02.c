#include <ctype.h>
#include <stdio.h>

int main(void) {
  int ch;
  int at_line_start = 1;

  while ((ch = getchar()) != EOF) {
    if (at_line_start) {
      if (isspace((unsigned char) ch))
        continue;
      at_line_start = 0;
    }

    putchar(ch);
    if (ch == '\n')
      at_line_start = 1;
  }

  return 0;
}
