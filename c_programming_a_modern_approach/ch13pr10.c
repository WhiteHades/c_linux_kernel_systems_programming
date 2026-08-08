#include <ctype.h>
#include <stdio.h>
#include <string.h>

void reverse_name(char *name);

int main(void) {
  char name[101];

  printf("Enter a first and last name: ");
  fgets(name, sizeof(name), stdin);
  name[strcspn(name, "\n")] = '\0';
  reverse_name(name);
  printf("You entered the name: %s\n", name);
  return 0;
}

void reverse_name(char *name) {
  char first_initial = '\0', last[96];
  char *p = name;
  int i = 0;

  while (isspace((unsigned char) *p))
    p++;
  first_initial = *p;
  while (*p && !isspace((unsigned char) *p))
    p++;
  while (isspace((unsigned char) *p))
    p++;
  while (*p && !isspace((unsigned char) *p) && i < 95)
    last[i++] = *p++;
  last[i] = '\0';
  snprintf(name, 101, "%s, %c.", last, first_initial);
}
