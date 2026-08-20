#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RANKS 13
#define SUITS 4

int main(void) {
  const char *ranks[RANKS] = {"Two", "Three", "Four", "Five", "Six",
    "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"};
  const char *suits[SUITS] = {"clubs", "diamonds", "hearts", "spades"};
  bool dealt[RANKS][SUITS] = {{false}};
  int cards, rank, suit, i;

  srand((unsigned) time(NULL));
  printf("Enter number of cards in hand: ");
  scanf("%d", &cards);
  if (cards < 1 || cards > RANKS * SUITS) {
    printf("Number of cards must be between 1 and 52.\n");
    return 1;
  }

  printf("Your hand:\n");
  for (i = 0; i < cards; i++) {
    do {
      rank = rand() % RANKS;
      suit = rand() % SUITS;
    } while (dealt[rank][suit]);
    dealt[rank][suit] = true;
    printf("%s of %s\n", ranks[rank], suits[suit]);
  }
  return 0;
}
