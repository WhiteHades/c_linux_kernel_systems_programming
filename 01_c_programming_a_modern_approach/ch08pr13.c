#include <stdio.h>

#define MAX_LAST_NAME 20

int main(void) {
  char initial, last_name[MAX_LAST_NAME + 1];
  int length = 0, ch;

  printf("Enter a first and last name: ");
  do {
    ch = getchar();
  } while (ch == ' ' || ch == '\t');
  initial = (char)ch;

  while ((ch = getchar()) != ' ' && ch != '\t' && ch != '\n' && ch != EOF)
    ;
  while (ch == ' ' || ch == '\t')
    ch = getchar();
  while (ch != '\n' && ch != EOF && length < MAX_LAST_NAME) {
    last_name[length++] = (char)ch;
    ch = getchar();
  }
  last_name[length] = '\0';

  printf("You entered the name: %s, %c.\n", last_name, initial);
  return 0;
}
