#include <stdio.h>

#define MAX_MESSAGE 80

int main(void) {
  char message[MAX_MESSAGE];
  int length = 0, ch, shift;

  printf("Enter message to be encrypted: ");
  while (length < MAX_MESSAGE && (ch = getchar()) != '\n' && ch != EOF)
    message[length++] = (char)ch;
  printf("Enter shift amount (1-25): ");
  scanf("%d", &shift);

  printf("Encrypted message: ");
  for (int i = 0; i < length; i++) {
    ch = message[i];
    if (ch >= 'A' && ch <= 'Z')
      ch = (ch - 'A' + shift) % 26 + 'A';
    else if (ch >= 'a' && ch <= 'z')
      ch = (ch - 'a' + shift) % 26 + 'a';
    putchar(ch);
  }
  putchar('\n');

  return 0;
}
