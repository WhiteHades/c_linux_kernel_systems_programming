#include <ctype.h>
#include <stdio.h>

#define NUM_PLANETS 9

int strings_equal_ignore_case(const char *s1, const char *s2);

int main(int argc, char *argv[]) {
  const char *planets[NUM_PLANETS] = {"Mercury", "Venus", "Earth", "Mars",
    "Jupiter", "Saturn", "Uranus", "Neptune", "Pluto"};
  int i, j;

  for (i = 1; i < argc; i++) {
    for (j = 0; j < NUM_PLANETS; j++)
      if (strings_equal_ignore_case(argv[i], planets[j]))
        break;
    if (j < NUM_PLANETS)
      printf("%s is planet %d\n", argv[i], j + 1);
    else
      printf("%s is not a planet\n", argv[i]);
  }
  return 0;
}

int strings_equal_ignore_case(const char *s1, const char *s2) {
  while (*s1 && *s2) {
    if (toupper((unsigned char) *s1) != toupper((unsigned char) *s2))
      return 0;
    s1++;
    s2++;
  }
  return *s1 == *s2;
}
