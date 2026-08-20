#include <stdio.h>
#include <string.h>

void reverse(char *message);

int main(void) {
  char message[201];

  printf("Enter a message: ");
  fgets(message, sizeof(message), stdin);
  message[strcspn(message, "\n")] = '\0';
  reverse(message);
  printf("Reversal is: %s\n", message);
  return 0;
}

void reverse(char *message) {
  char *end = message + strlen(message), temp;

  if (end == message)
    return;
  end--;
  while (message < end) {
    temp = *message;
    *message++ = *end;
    *end-- = temp;
  }
}
