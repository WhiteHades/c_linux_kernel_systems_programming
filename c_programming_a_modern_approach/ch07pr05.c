#include <ctype.h>
#include <stdio.h>

int main(void) {
  int ch, score = 0;

  printf("enter a word: ");

  while ((ch = getchar()) != '\n') {
    ch = toupper(ch);
    switch (ch) {
    case 'A':
    case 'E':
    case 'I':
    case 'L':
    case 'N':
    case 'O':
    case 'R':
    case 'S':
    case 'T':
    case 'U':
      score += 1;
      break;
    case 'D':
    case 'G':
      score += 2;
      break;
    case 'B':
    case 'C':
    case 'M':
    case 'P':
      score += 3;
      break;
    case 'F':
    case 'H':
    case 'V':
    case 'W':
    case 'Y':
      score += 4;
      break;
    case 'K':
      score += 5;
      break;
    case 'J':
    case 'X':
      score += 8;
      break;
    case 'Q':
    case 'Z':
      score += 10;
      break;
    default:
      break;
    }
  }
  printf("scrabble value: %d\n", score);

  return 0;
}
