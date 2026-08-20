#include <ctype.h>
#include <stdio.h>

int main(void) {
  int ch;
  int need_capital = 1;

  while ((ch = getchar()) != EOF) {
    if (isspace((unsigned char) ch)) {
      need_capital = 1;
    } else if (need_capital && isalpha((unsigned char) ch)) {
      ch = toupper((unsigned char) ch);
      need_capital = 0;
    }

    putchar(ch);
  }

  return 0;
}
