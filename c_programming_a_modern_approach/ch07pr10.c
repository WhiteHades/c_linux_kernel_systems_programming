#include <ctype.h>
#include <stdio.h>

int main(void) {
  int ch, vowel_count = 0;

  printf("Enter a sentence: ");

  while ((ch = getchar()) != '\n' && ch != EOF) {
    switch (toupper(ch)) {
    case 'A':
    case 'E':
    case 'I':
    case 'O':
    case 'U':
      vowel_count++;
      break;
    default:
      break;
    }
  }

  printf("Your sentence contains %d vowels.\n", vowel_count);

  return 0;
}
