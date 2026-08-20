#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_REMIND 50
#define MSG_LEN 60

struct vstring {
  int len;
  char chars[];
};

int compare_vstrings(const struct vstring *left, const struct vstring *right);
int read_line(char str[], int n);

int main(void) {
  struct vstring *reminders[MAX_REMIND];
  char day_text[3], message[MSG_LEN + 1];
  int day, count = 0, i, j;

  for (;;) {
    struct vstring *entry;
    int length;

    if (count == MAX_REMIND) {
      printf("-- No space left --\n");
      break;
    }
    printf("Enter day and reminder: ");
    scanf("%2d", &day);
    if (day == 0)
      break;
    snprintf(day_text, sizeof(day_text), "%2d", day);
    read_line(message, MSG_LEN);
    length = 2 + strlen(message);
    entry = malloc(sizeof(*entry) + length);
    if (entry == NULL) {
      printf("-- No space left --\n");
      break;
    }
    entry->len = length;
    memcpy(entry->chars, day_text, 2);
    memcpy(entry->chars + 2, message, strlen(message));

    for (i = 0; i < count && compare_vstrings(reminders[i], entry) <= 0; i++)
      ;
    for (j = count; j > i; j--)
      reminders[j] = reminders[j - 1];
    reminders[i] = entry;
    count++;
  }

  printf("\nDay Reminder\n");
  for (i = 0; i < count; i++) {
    printf(" %.*s\n", reminders[i]->len, reminders[i]->chars);
    free(reminders[i]);
  }
  return 0;
}

int compare_vstrings(const struct vstring *left, const struct vstring *right) {
  return memcmp(left->chars, right->chars, 2);
}

int read_line(char str[], int n) {
  int ch, i = 0;
  while ((ch = getchar()) != '\n' && ch != EOF)
    if (i < n)
      str[i++] = (char) ch;
  str[i] = '\0';
  return i;
}
