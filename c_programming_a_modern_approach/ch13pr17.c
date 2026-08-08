#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

bool is_palindrome(const char *message);

int main(void) {
  char message[201];

  printf("Enter a message: ");
  fgets(message, sizeof(message), stdin);
  message[strcspn(message, "\n")] = '\0';
  puts(is_palindrome(message) ? "Palindrome" : "Not a palindrome");
  return 0;
}

bool is_palindrome(const char *message) {
  const char *end = message + strlen(message);

  if (end == message)
    return true;
  end--;
  while (message < end) {
    while (message < end && !isalpha((unsigned char) *message))
      message++;
    while (message < end && !isalpha((unsigned char) *end))
      end--;
    if (tolower((unsigned char) *message) !=
        tolower((unsigned char) *end))
      return false;
    message++;
    end--;
  }
  return true;
}
