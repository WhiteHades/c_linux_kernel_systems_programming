#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_RANKS 13
#define NUM_SUITS 4
#define NUM_CARDS 5

int num_in_rank[NUM_RANKS], num_in_suit[NUM_SUITS];
bool royal, straight, flush, four, three;
int pairs;

void read_cards(void);
void analyze_hand(void);
void print_result(void);
int rank_value(int ch);
int suit_value(int ch);

int main(void) {
  for (;;) {
    read_cards();
    analyze_hand();
    print_result();
  }
}

void read_cards(void) {
  bool card_exists[NUM_RANKS][NUM_SUITS] = {{false}};
  char input[20];
  int cards_read = 0;

  for (int rank = 0; rank < NUM_RANKS; rank++)
    num_in_rank[rank] = 0;
  for (int suit = 0; suit < NUM_SUITS; suit++)
    num_in_suit[suit] = 0;

  while (cards_read < NUM_CARDS) {
    printf("Enter a card: ");
    if (fgets(input, sizeof(input), stdin) == NULL || input[0] == '0')
      exit(EXIT_SUCCESS);
    int rank = rank_value(input[0]);
    int suit = suit_value(input[1]);
    if (rank < 0 || suit < 0)
      printf("Bad card; ignored.\n");
    else if (card_exists[rank][suit])
      printf("Duplicate card; ignored.\n");
    else {
      card_exists[rank][suit] = true;
      num_in_rank[rank]++;
      num_in_suit[suit]++;
      cards_read++;
    }
  }
}

void analyze_hand(void) {
  royal = straight = flush = four = three = false;
  pairs = 0;
  for (int suit = 0; suit < NUM_SUITS; suit++)
    if (num_in_suit[suit] == NUM_CARDS)
      flush = true;

  int rank = 0;
  while (rank < NUM_RANKS && num_in_rank[rank] == 0)
    rank++;
  int consecutive = 0;
  while (rank < NUM_RANKS && num_in_rank[rank] > 0) {
    consecutive++;
    rank++;
  }
  straight = consecutive == NUM_CARDS;
  royal = flush;
  for (rank = 8; rank < NUM_RANKS; rank++)
    if (num_in_rank[rank] != 1)
      royal = false;

  for (rank = 0; rank < NUM_RANKS; rank++) {
    if (num_in_rank[rank] == 4) four = true;
    else if (num_in_rank[rank] == 3) three = true;
    else if (num_in_rank[rank] == 2) pairs++;
  }
}

void print_result(void) {
  if (royal) printf("Royal flush\n\n");
  else if (straight && flush) printf("Straight flush\n\n");
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
