#include <ctype.h>
#include <stdio.h>

#define MAX_MESSAGE 80

int main(void) {
  char message[MAX_MESSAGE];
  int length = 0, ch;

  printf("Enter message: ");
  while (length < MAX_MESSAGE && (ch = getchar()) != '\n' && ch != EOF)
    message[length++] = (char)ch;

  printf("In B1FF-speak: ");
  for (int i = 0; i < length; i++) {
    ch = toupper((unsigned char)message[i]);
    switch (ch) {
    case 'A': ch = '4'; break;
    case 'B': ch = '8'; break;
    case 'E': ch = '3'; break;
    case 'I': ch = '1'; break;
    case 'O': ch = '0'; break;
    case 'S': ch = '5'; break;
    }
    putchar(ch);
  }
  printf("!!!!!!!!!!\n");

  return 0;
}
