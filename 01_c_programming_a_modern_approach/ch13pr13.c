#include <stdio.h>
#include <string.h>

void encrypt(char *message, int shift);

int main(void) {
  char message[81];
  int shift;

  printf("Enter message to be encrypted: ");
  fgets(message, sizeof(message), stdin);
  message[strcspn(message, "\n")] = '\0';
  printf("Enter shift amount (1-25): ");
  scanf("%d", &shift);
  encrypt(message, shift);
  printf("Encrypted message: %s\n", message);
  return 0;
}

void encrypt(char *message, int shift) {
  shift %= 26;
  while (*message) {
    if (*message >= 'A' && *message <= 'Z')
      *message = (char) ((*message - 'A' + shift) % 26 + 'A');
    else if (*message >= 'a' && *message <= 'z')
      *message = (char) ((*message - 'a' + shift) % 26 + 'a');
    message++;
  }
}
