#include <stdio.h>
#include <stdbool.h>

#define NUM_CARDS_IN_HAND 2
#define NUM_CARDS_IN_COMMUNITY 5

// Define structures and constants
typedef enum {
    HEARTS,
    DIAMONDS,
    CLUBS,
    SPADES
} Suit;

typedef struct {
    int rank;
    Suit suit;
} Card;

typedef struct {
    Card cards[NUM_CARDS_IN_HAND];
} Hand;

typedef struct {
    Card cards[NUM_CARDS_IN_COMMUNITY];
    int num_cards;
} CommunityCards;

typedef struct {
    Card cards[52];
    int num_cards;
} Deck;

// Function prototypes
void InitializeDeck(Deck* deck);
void ShuffleDeck(Deck* deck);
void DealCards(Hand* player1Hand, Hand* player2Hand, CommunityCards* communityCards, Deck* deck);

// Function to check if there is a pair in the hand and community cards
bool hasPair(Hand hand&){
    // First, deal cards to players and community
    Hand player1Hand, player2Hand;
    DealCards(&player1Hand, &player2Hand, &communityCards, &deck);

    // Check if there is a pair in the hand
    for (int i = 0; i < NUM_CARDS_IN_HAND - 1; i++) {
        for (int j = i + 1; j < NUM_CARDS_IN_HAND; j++) {
            if (hand.cards[i].rank == hand.cards[j].rank) {
                return true;
            }
        }
    }

    // Check if there is a pair with the community cards
    for (int i = 0; i < NUM_CARDS_IN_HAND; i++) {
        for (int j = 0; j < communityCards.num_cards; j++) {
            if (hand.cards[i].rank == communityCards.cards[j].rank) {
                return true;
            }
        }
    }

    // Check if there is a pair within the community cards
    for (int i = 0; i < communityCards.num_cards - 1; i++) {
        for (int j = i + 1; j < communityCards.num_cards; j++) {
            if (communityCards.cards[i].rank == communityCards.cards[j].rank) {
                return true;
            }
        }
    }
    return false;
}

// Example main function
int main() {
    Deck deck;
    CommunityCards communityCards;
    Hand hand = {0};

    // Initialize the deck and shuffle it
    InitializeDeck(&deck);
    ShuffleDeck(&deck);

    // Call hasPair function
    bool hasPairResult = hasPair(hand, communityCards, deck);

    // Output the result
    if (hasPairResult) {
        printf("The player has a pair.\n");
    } else {
        printf("The player doesn't have a pair.\n");
    }

    return 0;
}

// Implementation of other functions (InitializeDeck, ShuffleDeck, DealCards) omitted for brevity
