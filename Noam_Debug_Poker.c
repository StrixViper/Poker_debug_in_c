#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_RANKS 13
#define NUM_SUITS 4
#define NUM_CARDS_IN_DECK (NUM_RANKS * NUM_SUITS)

typedef enum {
    TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE
} Rank;

typedef enum {
    HEARTS, DIAMONDS, CLUBS, SPADES
} Suit;

typedef struct {
    Rank rank;
    Suit suit;
} Card;

typedef struct {
    Card cards[NUM_CARDS_IN_DECK];
    int num_cards;
} Deck;

char suitSymbol(Suit suit) {
    switch (suit) {
        case HEARTS: return 'H';
        case DIAMONDS: return 'D';
        case CLUBS: return 'C';
        case SPADES: return 'S';
        default: return '?';
    }
}


void InitializeDeck(Deck* deck) {
    int index = 0;
    for (int rank = TWO; rank <= ACE; rank++) {
        for (int suit = HEARTS; suit <= SPADES; suit++) {
            deck->cards[index].rank = (Rank)rank;
            deck->cards[index].suit = (Suit)suit;
            index++;
        }
    }
    deck->num_cards = NUM_CARDS_IN_DECK; // Set the total number of cards in the deck (52)
}

void ShuffleDeck(Deck* deck) {
    // Seed the random number generator
    srand(time(NULL));

    // Start from the last card and swap it with a randomly selected card before it
    for (int i = deck->num_cards - 1; i > 0; i--) {
        // Generate a random index between 0 and i (inclusive)
        int j = rand() % (i + 1);

        // Swap the current card with the randomly selected card
        Card temp = deck->cards[i];
        deck->cards[i] = deck->cards[j];
        deck->cards[j] = temp;
    }
}

void DisplayFirstCard(const Deck* deck) {
    if (deck->num_cards > 0) {
        printf("First card in the deck:\n");
        printf("Rank: %d, Suit: %c\n", deck->cards[0].rank, suitSymbol(deck->cards[0].suit));
    } else {
        printf("The deck is empty.\n");
    }
}

int main() {
    // Initialize a deck
    Deck deck;
    InitializeDeck(&deck);

    // Shuffle the deck
    ShuffleDeck(&deck);

    // Display the first card in the deck
    DisplayFirstCard(&deck);

    return 0;
}
