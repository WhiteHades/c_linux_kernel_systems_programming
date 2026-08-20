#include <ctype.h>
#include <stdio.h>

#define MAX_PHONE 15

int main(void) {
  char phone[MAX_PHONE];
  int length = 0, ch;

  printf("Enter phone number: ");
  while (length < MAX_PHONE && (ch = getchar()) != '\n' && ch != EOF) {
    ch = toupper((unsigned char)ch);
    if (ch >= 'A' && ch <= 'Z') {
      const char keypad[] = "2223334445556667Q77888999Z";
      ch = keypad[ch - 'A'];
    }
    phone[length++] = (char)ch;
  }

  printf("In numeric form: ");
  for (int i = 0; i < length; i++)
    putchar(phone[i]);
  putchar('\n');

  return 0;
}
