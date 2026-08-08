#include <stdio.h>
#include <string.h>

#define MAX_REMINDERS 50
#define REMINDER_LEN 80

int read_line(char str[], int n);

int main(void) {
  char reminders[MAX_REMINDERS][REMINDER_LEN + 13];
  char message[REMINDER_LEN + 1], entry[REMINDER_LEN + 13];
  int month, day, hour, minute, i, j, count = 0;

  for (;;) {
    printf("Enter date, time, and reminder (mm/dd hh:mm): ");
    if (scanf("%d/%d", &month, &day) != 2)
      break;
    if (month == 0 && day == 0)
      break;
    if (scanf(" %d:%d", &hour, &minute) != 2)
      break;
    read_line(message, REMINDER_LEN);

    if (month < 1 || month > 12 || day < 1 || day > 31 ||
        hour < 0 || hour > 23 || minute < 0 || minute > 59) {
      printf("Invalid date or time.\n");
      continue;
    }
    if (count == MAX_REMINDERS) {
      printf("-- No space left --\n");
      break;
    }

    snprintf(entry, sizeof(entry), "%02d/%02d %02d:%02d%s", month, day,
             hour, minute, message);
    for (i = 0; i < count && strcmp(reminders[i], entry) <= 0; i++)
      ;
    for (j = count; j > i; j--)
      strcpy(reminders[j], reminders[j - 1]);
    strcpy(reminders[i], entry);
    count++;
  }

  printf("\nDate  Time  Reminder\n");
  for (i = 0; i < count; i++)
    puts(reminders[i]);
  return 0;
}

int read_line(char str[], int n) {
  int ch, i = 0;

  while ((ch = getchar()) != '\n' && ch != EOF)
    if (i < n)
      str[i++] = (char) ch;
  str[i] = '\0';
  return i;
}
