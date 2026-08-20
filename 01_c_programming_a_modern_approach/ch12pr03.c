#include <stdio.h>

#define MAX_MESSAGE 100

int main(void) {
  char message[MAX_MESSAGE], *position = message;
  int ch;

  printf("Enter a message: ");
  while (position < message + MAX_MESSAGE && (ch = getchar()) != '\n' &&
         ch != EOF)
    *position++ = (char)ch;

  printf("Reversal is: ");
  while (position > message)
    putchar(*--position);
  putchar('\n');
  return 0;
}
