#include <stdio.h>

int main(void) {
  int ch, initial;

  printf("Enter a first and last name: ");

  while ((ch = getchar()) == ' ')
    ;
  initial = ch;

  while (ch != ' ' && ch != '\n' && ch != EOF)
    ch = getchar();
  while (ch == ' ')
    ch = getchar();

  while (ch != ' ' && ch != '\n' && ch != EOF) {
    putchar(ch);
    ch = getchar();
  }

  printf(", %c.\n", initial);

  return 0;
}
