#include <ctype.h>
#include <stdio.h>

#define MAX_MESSAGE 100

int main(void) {
  char message[MAX_MESSAGE], *end = &message[0];
  int ch;

  printf("Enter a message: ");
  while (end < &message[MAX_MESSAGE] && (ch = getchar()) != '\n' && ch != EOF)
    if (isalpha((unsigned char)ch))
      *end++ = (char)tolower((unsigned char)ch);

  char *left = &message[0];
  char *right = end;
  while (left < right && *left == *--right)
    left++;

  printf(left >= right ? "Palindrome\n" : "Not a palindrome\n");
  return 0;
}
