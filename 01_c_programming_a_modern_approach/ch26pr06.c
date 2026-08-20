#include <stdio.h>
#include <time.h>

int main(void) {
  time_t current = time(NULL);
  struct tm *date = localtime(&current);
  char text[80];
  char time_text[20];
  int hour;

  if (date == NULL)
    return 1;

  strftime(text, sizeof(text), "%A, %B", date);
  strftime(time_text, sizeof(time_text), "%I:%M", date);
  printf("%s %d, %d %s%c\n", text, date->tm_mday, date->tm_year + 1900,
         time_text, date->tm_hour < 12 ? 'a' : 'p');

  strftime(text, sizeof(text), "%a", date);
  strftime(time_text, sizeof(time_text), "%b %y %H:%M", date);
  printf("%s, %d %s\n", text, date->tm_mday, time_text);

  hour = date->tm_hour % 12;
  if (hour == 0)
    hour = 12;
  strftime(text, sizeof(text), ":%M:%S %p", date);
  printf("%02d/%02d/%02d %d%s\n", date->tm_mon + 1, date->tm_mday,
         (date->tm_year + 1900) % 100, hour, text);

  return 0;
}
