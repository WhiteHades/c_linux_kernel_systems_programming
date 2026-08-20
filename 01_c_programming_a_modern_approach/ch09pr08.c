#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int roll_dice(void);
bool play_game(void);

int main(void) {
  int wins = 0, losses = 0;
  char again;

  srand((unsigned)time(NULL));
  do {
    if (play_game()) {
      printf("You win!\n");
      wins++;
    } else {
      printf("You lose!\n");
      losses++;
    }
    printf("Play again? ");
    scanf(" %c", &again);
  } while (again == 'y' || again == 'Y');

  printf("Wins: %d  Losses: %d\n", wins, losses);
  return 0;
}

int roll_dice(void) { return rand() % 6 + 1 + rand() % 6 + 1; }

bool play_game(void) {
  int roll = roll_dice();
  printf("You rolled: %d\n", roll);
  if (roll == 7 || roll == 11)
    return true;
  if (roll == 2 || roll == 3 || roll == 12)
    return false;

  int point = roll;
  printf("Your point is %d\n", point);
  for (;;) {
    roll = roll_dice();
    printf("You rolled: %d\n", roll);
    if (roll == point)
      return true;
    if (roll == 7)
      return false;
  }
}
