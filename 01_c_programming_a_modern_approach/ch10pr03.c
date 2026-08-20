#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_RANKS 13
#define NUM_SUITS 4
#define NUM_CARDS 5

bool straight, flush, four, three;
int pairs;

void read_cards(int hand[NUM_CARDS][2]);
void analyze_hand(int hand[NUM_CARDS][2]);
void print_result(void);
int rank_value(int ch);
int suit_value(int ch);

int main(void) {
  int hand[NUM_CARDS][2];

  for (;;) {
    read_cards(hand);
    analyze_hand(hand);
    print_result();
  }
}

void read_cards(int hand[NUM_CARDS][2]) {
  char input[20];
  int cards_read = 0;

  while (cards_read < NUM_CARDS) {
    printf("Enter a card: ");
    if (fgets(input, sizeof(input), stdin) == NULL || input[0] == '0')
      exit(EXIT_SUCCESS);

    int rank = rank_value(input[0]);
    int suit = suit_value(input[1]);
    bool duplicate = false;
    for (int i = 0; i < cards_read; i++)
      if (hand[i][0] == rank && hand[i][1] == suit)
        duplicate = true;

    if (rank < 0 || suit < 0)
      printf("Bad card; ignored.\n");
    else if (duplicate)
      printf("Duplicate card; ignored.\n");
    else {
      hand[cards_read][0] = rank;
      hand[cards_read][1] = suit;
      cards_read++;
    }
  }
}

void analyze_hand(int hand[NUM_CARDS][2]) {
  int rank_counts[NUM_RANKS] = {0};
  int suit_counts[NUM_SUITS] = {0};
  straight = flush = four = three = false;
  pairs = 0;

  for (int i = 0; i < NUM_CARDS; i++) {
    rank_counts[hand[i][0]]++;
    suit_counts[hand[i][1]]++;
  }
  for (int suit = 0; suit < NUM_SUITS; suit++)
    if (suit_counts[suit] == NUM_CARDS)
      flush = true;

  int rank = 0;
  while (rank < NUM_RANKS && rank_counts[rank] == 0)
    rank++;
  int consecutive = 0;
  while (rank < NUM_RANKS && rank_counts[rank] > 0) {
    consecutive++;
    rank++;
  }
  straight = consecutive == NUM_CARDS;

  for (rank = 0; rank < NUM_RANKS; rank++) {
    if (rank_counts[rank] == 4)
      four = true;
    else if (rank_counts[rank] == 3)
      three = true;
    else if (rank_counts[rank] == 2)
      pairs++;
  }
}

void print_result(void) {
  if (straight && flush) printf("Straight flush\n\n");
  else if (four) printf("Four of a kind\n\n");
  else if (three && pairs == 1) printf("Full house\n\n");
  else if (flush) printf("Flush\n\n");
  else if (straight) printf("Straight\n\n");
  else if (three) printf("Three of a kind\n\n");
  else if (pairs == 2) printf("Two pairs\n\n");
  else if (pairs == 1) printf("Pair\n\n");
  else printf("High card\n\n");
}

int rank_value(int ch) {
  if (ch >= '2' && ch <= '9') return ch - '2';
  switch (ch) {
  case 't': case 'T': return 8;
  case 'j': case 'J': return 9;
  case 'q': case 'Q': return 10;
  case 'k': case 'K': return 11;
  case 'a': case 'A': return 12;
  default: return -1;
  }
}

int suit_value(int ch) {
  switch (ch) {
  case 'c': case 'C': return 0;
  case 'd': case 'D': return 1;
  case 'h': case 'H': return 2;
  case 's': case 'S': return 3;
  default: return -1;
  }
}
