#include <ctype.h>
#include <stdio.h>

int main(void) {
  int ch;

  while ((ch = getchar()) != EOF) {
    if (ch != '\n' && iscntrl((unsigned char) ch))
      putchar('?');
    else
      putchar(ch);
  }

  return 0;
}
