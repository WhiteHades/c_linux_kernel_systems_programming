#include <ctype.h>
#include <stdio.h>

int main(void) {
  int ch;
  int previous = 0;
  int sentences = 0;

  while ((ch = getchar()) != EOF) {
    if (isspace((unsigned char) ch) &&
        (previous == '.' || previous == '?' || previous == '!'))
      sentences++;
    previous = ch;
  }

  printf("Sentence count: %d\n", sentences);
  return 0;
}
