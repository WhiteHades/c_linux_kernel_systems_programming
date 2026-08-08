#include <locale.h>
#include <stdio.h>
#include <string.h>

int main(void) {
  char native_locale[256];
  const char *locale_name;

  locale_name = setlocale(LC_ALL, "");
  if (locale_name == NULL) {
    printf("The native locale is not available.\n");
    return 1;
  }
  if (strlen(locale_name) >= sizeof(native_locale)) {
    printf("The native locale name is too long.\n");
    return 1;
  }
  strcpy(native_locale, locale_name);

  locale_name = setlocale(LC_ALL, "C");
  if (locale_name == NULL) {
    printf("The C locale is not available.\n");
    return 1;
  }

  if (strcmp(native_locale, locale_name) == 0)
    printf("The native locale and the C locale are the same.\n");
  else
    printf("The native locale (%s) and the C locale (%s) differ.\n",
           native_locale, locale_name);

  return 0;
}
