#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <time.h>


#define NUM_PLAYERS_MIN 2
#define NUM_PLAYERS_MAX 5//need to update this
#define NUM_CARDS_IN_HAND 2
#define NUM_COMMUNITY_CARDS 5
#define NUM_RANKS 13
#define NUM_SUITS 4
#define NUM_CARDS_IN_DECK (NUM_RANKS * NUM_SUITS)



//-------------------------------//basic structures for define the basic of my project

typedef enum
{
    HEARTS,
    DIAMONDS,
    CLUBS,
    SPADES
} Suit;


typedef enum
{
    TWO=2,THREE,FOUR,FIVE,SIX,SEVEN,EIGHT,NINE,TEN,JACK,QUEEN,KING,ACE
} Rank;


typedef struct
{
    Rank rank;
    Suit suit;
} Card;


typedef struct
{
        Card cards[NUM_CARDS_IN_HAND];
        int num_cards;
} Hand;

typedef struct
{
    Card cards[NUM_COMMUNITY_CARDS];
    int num_cards;

}CommunityCards;

typedef struct
{
    Hand hand;
    int chips;
    bool folded;

} Player;

typedef struct
{
    Card cards[NUM_CARDS_IN_DECK];
    int num_cards;
} Deck;


typedef enum
{
    HIGH_CARD,
    PAIR,
    TWO_PAIR,
    THREE_OF_KIND,
    STRAIGHT,
    FLUSH,
    FOUR_OF_KIND,
    FULL_HOUSE,
    STRAIGHT_FLUSH,
    ROYAL_FLUSH

} HandRank;

//------------------------------------------end of basic structs



//now this functions will check the stage of your card combination

bool FirsthasHighCard(Player* player1, Player* player2);

bool SecondhasHighCard(Player* player1, Player* player2);

bool hasPair(Hand* hand, CommunityCards* communityCards);

bool hasTwoPair(Hand* hand, CommunityCards* communityCards);

bool hasThreePair(Hand* hand, CommunityCards* communityCards); // meant three of kind

bool hasStraight(Hand* hand, CommunityCards* communityCards);

bool hasFlush(Hand* hand, CommunityCards* communityCards);

bool hasFourPair(Hand* hand, CommunityCards* communityCards);

bool hasFullHouse(Hand* hand, CommunityCards* communityCards);

bool hasStraightFlush(Hand* hand, CommunityCards* communityCards);

bool hasRoyalFlush(Hand* hand, CommunityCards* communityCards);


//--------------------------------------------------//

char suitSymbol(Suit suit);

//Game Flow Functions

int WhoIsWinner(Player playe1,Player player2);

void DisplayMenu()
{

    printf("\t\t\t\t\t\t\t*****************************\n");
    printf("\t\t\t\t\t\t\t*                           *\n");
    printf("\t\t\t\t\t\t\t* WELCOME TO THE POKER GAME *\n");
    printf("\t\t\t\t\t\t\t*                           *\n");
    printf("\t\t\t\t\t\t\t*****************************\n");


    printf("\t\t\t\t\t\t\t\t     MENU\n");
    printf("\t\t\t\t\t\t\t*****************************\n");
    printf("\t\t\t\t\t\t\t*\t   1:MODES\t    *\n");
    printf("\t\t\t\t\t\t\t*\t   2:RULES     \t    *\n");
    printf("\t\t\t\t\t\t\t*\t   3:TERMS    \t    *\n");
    printf("\t\t\t\t\t\t\t*\t   4:REGISTER \t    *\n");
    printf("\t\t\t\t\t\t\t*\t   5:LOGIN   \t    *\n");
    printf("\t\t\t\t\t\t\t*****************************\n");

    printf("\t\t\t\t\t\t\t\tSELECT CHOICE: ");

    int choice;
    scanf("%d",&choice);

    switch(choice)
    {
    case 1:
        DisplayModes();
        break;
    case 2:
        printRulesOfTheGame();
        break;
    case 3:
        printTermsOfUse();
        break;
    case 4:
        //DONT EXIST YET
        break;
    case 5:
        //DONT EXIST YET
        break;
    default:
        printf("INVALID INPUT,TRY AGAIN LATER");
        break;
    }
    }

void DisplayCards(Player* player1, Player* player2, CommunityCards* communityCards, Deck* deck) {
    // Deal cards to players
    DealCards(player1, player2, communityCards, deck);

    // Function to convert rank to string for face cards
    const char* rankToString(int rank) {
        switch (rank) {
            case 11: return "J";
            case 12: return "Q";
            case 13: return "K";
            case 14: return "A";
            default: return NULL; // For numerical cards
        }
    }

    // Display both players' cards
    printf("Player 1's Cards:                         Player 2's Cards:\n");

    // Display player 1's first card
    printf(" _________                                _________\n");
    printf("|         |                              |         |\n");
    if (player1->hand.cards[0].rank >= 11 && player1->hand.cards[0].rank <= 14) {
        printf("|  %s  %c   |", rankToString(player1->hand.cards[0].rank), suitSymbol(player1->hand.cards[0].suit));
    } else {
        printf("|  %d  %c   |", player1->hand.cards[0].rank, suitSymbol(player1->hand.cards[0].suit));
    }
    // Display player 2's first card
    printf("%19s", ""); // Adjust the spacing as needed
    if (player2->hand.cards[0].rank >= 11 && player2->hand.cards[0].rank <= 14) {
        printf("           |  %s  %c   |\n", rankToString(player2->hand.cards[0].rank), suitSymbol(player2->hand.cards[0].suit));
    } else {
        printf("           |  %d  %c   |\n", player2->hand.cards[0].rank, suitSymbol(player2->hand.cards[0].suit));
    }
    printf("|_________|                              |_________|\n");

    // Display player 1's second card
    printf(" _________                                _________\n");
    printf("|         |                              |         |\n");
    if (player1->hand.cards[1].rank >= 11 && player1->hand.cards[1].rank <= 14) {
        printf("|  %s  %c   |", rankToString(player1->hand.cards[1].rank), suitSymbol(player1->hand.cards[1].suit));
    } else {
        printf("|  %d  %c   |", player1->hand.cards[1].rank, suitSymbol(player1->hand.cards[1].suit));
    }
    // Display player 2's second card
    printf("%19s", ""); // Adjust the spacing as needed
    if (player2->hand.cards[1].rank >= 11 && player2->hand.cards[1].rank <= 14) {
        printf("           |  %s  %c   |\n", rankToString(player2->hand.cards[1].rank), suitSymbol(player2->hand.cards[1].suit));
    } else {
        printf("           |  %d  %c   |\n", player2->hand.cards[1].rank, suitSymbol(player2->hand.cards[1].suit));
    }
    printf("|_________|                              |_________|\n");


}


// Function to get suit symbol
// Function to get suit symbol
char suitSymbol(Suit suit) {
    switch (suit) {
        case HEARTS: return 'H';
        case DIAMONDS: return 'D';
        case CLUBS: return 'C';
        case SPADES: return 'S';
        default: return '?';
    }
}

//-------------//not done yet

void DisplayModes()
{
    printf("1: TEXAS HOLDEM\n");
    printf("2: BLACK JACK\n");

    int choice;
    scanf("%d",&choice);

    if(choice==1)
        printf("THE SERVIVE DONT WORK,TRY AGAIN LATER");
    else if(choice ==2)
        printf("THE SERVIVE DONT WORK,TRY AGAIN LATER");
    else
        printf("INVALID OPTION TRY AGAIN");
}

void InitializeDeck(Deck* deck);// Function to initialize the deck with cards

void ShuffleDeck(Deck* deck);// shuffel the Deck randomly

void DealCards(Player* player1, Player* player2, CommunityCards* communityCards, Deck* deck);

void BettingRound(Player* player1,Player* player2,CommunityCards* CommunityCards);

bool IsGameOver(Player* player1,Player* player2, CommunityCards* CommunityCards);

void StartGame(Player* player1,Player* player2,CommunityCards* CommunityCards,Deck* Deck);

//--------------------------------START_OF_THE_PROGRAM-----------------------------------//

int main() {
    // Initialize a deck

    Deck deck;
    Player player1,player2;
    CommunityCards CommunityCards;
    InitializeDeck(&deck);

    // Shuffle the deck
    ShuffleDeck(&deck);

    DealCards(&player1,&player2,&CommunityCards,&deck);

    DisplayCards(&player1,&player2,&CommunityCards,&deck);




    return 0;
}




//terms and rules functions
//need to style it for better user experience

void printRulesOfTheGame()
{
    printf("Texas Hold'em is a popular form of poker, where each player is dealt two private cards known as hole cards, and five community cards are dealt face up in three stages. ");
    printf("The stages consist of a series of three cards (the flop), later an additional single card (the turn or fourth street), and a final card (the river or fifth street). ");
    printf("Players have the option to check, bet, raise or fold after each deal. \n");
    printf("The player with the best five-card poker hand wins the pot. In the event of identical hands, the pot will be equally divided between the players with the best hands. \n");
    printf("There are no hands used in Hold'em other than the hands listed in this chart. For example, having three pairs is actually only \"two pair,\" with the highest-valued two pair making your hand. \n");
    printf("The hand with the highest pair wins. If the hands have the same high pair, the second pair wins. If both hands have the same high pair, the hand with the highest card outside the pair wins. ");
    printf("This means that the hand with the highest card overall wins. \n");
    printf("If the board has three of the same card, the highest card not in that set (so a player with three 8s and a 9 on the board would beat a player with three 8s and a 7 on the board). \n");
    printf("If the board has three of the same card, the highest card not in that set (so a player with three 8s and a 9 on the board would beat a player with three 8s and a 7 on the board). \n");
    printf("If the board has three of the same card, the highest card not in that set (so a player with three 8s and a 9 on the board would beat a player with three 8s and a 7 on the board). \n");
    printf("If the board has three of the same card, the highest card not in that set (so a player with three 8s and a 9 on the board would beat a player with three 8s and a 7 on the board). \n");
    printf("If the board has three of the same card, the highest card not in that set (so a player with three 8s and a 9 on the board would beat a player with three 8s and a 7 on the board). \n");
    printf("If the board has three of the same card, the highest card not in that set (so a player with three 8s and a 9 on the board would beat a player with three 8s and a 7 on the board). \n");
    printf("If the board has three of the same card, the highest card not in that set (so a player with three 8s and a 9 on the board would beat a player with three 8s and a 7 on the board). \n");
    printf("If the board has three of the same card, the highest card not in that set (so a player with three 8s and a 9 on the board would beat a player with three 8s and a 7 on the board). \n");

}

void printTermsOfUse()
{

    printf("\n\nTerms of Use:\n");
    printf("By playing this game, you agree that it is for entertainment purposes only. The developers of this game are not responsible for any losses or damages incurred while playing the game. ");
    printf("This game is intended for use by adults only. If you are under the age of 18, please do not play this game. ");
    printf("You agree to behave in a respectful manner towards other players and to follow the rules of the game. ");
    printf("Any violation of these terms may result in your account being suspended or terminated. ");

}


//end of terms and rules of the game functions

int max(int num1, int num2)
{
    return (num1 > num2 ) ? num1 : num2;
}


bool FirsthasHighCard(Player player1,Player player2)
{
    int firstfirst = player1.hand.cards[0].rank;
    int firstsecond = player1.hand.cards[1].rank;

    int secondfirst = player2.hand.cards[0].rank;
    int secondsecond = player2.hand.cards[1].rank;

    int maxfirst = max(firstfirst,firstsecond);
    int maxsecond = max(secondfirst,secondsecond);

    if(maxfirst>maxsecond)
    {
        return true;
    }
    return false;
}

bool SecondhasHighCard(Player player1,Player player2)
{
    int firstfirst = player1.hand.cards[0].rank;
    int firstsecond = player1.hand.cards[1].rank;

    int secondfirst = player2.hand.cards[0].rank;
    int secondsecond = player2.hand.cards[1].rank;

    int maxfirst = max(firstfirst,firstsecond);
    int maxsecond = max(secondfirst,secondsecond);

    if(maxsecond > maxfirst)
    {
        return true;
    }

    return false;
}


bool hasPair(Hand hand, CommunityCards communityCards)
{
    for(int i=0;i<NUM_CARDS_IN_HAND-1;i++)//check if you have a pair in your hand
    {
        for(int j=i+1;j<NUM_CARDS_IN_HAND;j++)
        {
            if(hand.cards[i].rank == hand.cards[j].rank)
            {
                return true;
            }
        }
    }

    for(int i=0;i<NUM_CARDS_IN_HAND;i++)//check if you have a pair with the computer also
    {
        for(int j=0;j<communityCards.num_cards;j++)
        {
            if(hand.cards[i].rank == communityCards.cards[j].rank)
                return true;
        }

    }

    for(int i=0;i<communityCards.num_cards-1;i++)//check if you have a pair in the computer only
    {
        for(int j=i+1;j<communityCards.num_cards;j++)
        {
            if(communityCards.cards[i].rank == communityCards.cards[j].rank)
                return true;
        }
    }
    return false;
}


bool hasTwoPair(Hand hand,CommunityCards communityCards)
{
int count = 0;


    for(int i=0;i<NUM_CARDS_IN_HAND-1;i++)//check if you have one pair in your cards
    {
        for(int j=i+1;j<NUM_CARDS_IN_HAND;j++)
        {
            if(hand.cards[i].rank == hand.cards[j].rank)
            {
                count++;
            }
        }
    }


    for(int i=0;i<NUM_CARDS_IN_HAND;i++)//check if you have pair with the commuity cards
    {
        for(int j=0;j<communityCards.num_cards;j++)
        {
            if(hand.cards[i].rank == communityCards.cards[j].rank)
                count++;
        }

    }
    for(int i=0;i<communityCards.num_cards-1;i++)//check if you have a pair in the computer only
    {
        for(int j=0;j<communityCards.num_cards;j++)
        {
            if(communityCards.cards[i].rank == communityCards.cards[j].rank)
                count++;
        }
    }

    if(count>=2)
    {
        return true;
    }

    return false;
}


//-----------------------------start of helping functions

bool hasPairInHand(Hand hand)//helping function for check in the threepair function
{
    for(int i=0;i<NUM_CARDS_IN_HAND-1;i++)//check if you have a pair in your hand
    {
        for(int j=i+1;j<NUM_CARDS_IN_HAND;j++)
        {
            if(hand.cards[i].rank == hand.cards[j].rank)
            {
                return true;
            }
        }
    }
    return false;
}


int pairsInComputer(CommunityCards communityCards)//another helping fuction for the Three pair function
{
    for(int i=0;i<communityCards.num_cards-1;i++)//check if you have a pair in the computer only
    {
        for(int j=0;j<communityCards.num_cards;j++)
        {
            if(communityCards.cards[i].rank == communityCards.cards[j].rank)
                return communityCards.cards[i].rank;
        }
    }
}


//--------------------------end of helping functions

bool hasThreePair(Hand hand,CommunityCards communityCards)
{

    if(hasPairInHand(hand))
    {
        int checkCardexist = hand.cards[0].rank;
        for(int i=0; i<communityCards.num_cards; i++)
        {
            if(checkCardexist==communityCards.cards[i].rank)//means that he have 2 pair in his hand and another one in the computer hand witch make this a 3 of kind
                return true;
        }
    }
    else if(pairsInComputer(communityCards)==hand.cards[0].rank || pairsInComputer(communityCards) == hand.cards[0].rank)
    {
        return true;
    }

    return false;
}


bool hasFlush(Hand hand, CommunityCards communityCards)
{
    int countcolor1 = 1;
    int countcolor2 = 1;

    if(hand.cards[0].suit==hand.cards[1].suit)
    { countcolor1++;
        for(int i=0;i<communityCards.num_cards;i++)
        {
        if(hand.cards[0].suit == communityCards.cards[i].suit)
            countcolor1++;
        }
    }

    else {
        for (int i = 0; i < communityCards.num_cards; i++) {
            if (hand.cards[0].suit == communityCards.cards[i].suit) {
                countcolor1++;
            } else if (hand.cards[1].suit == communityCards.cards[i].suit) {
                countcolor2++;
            } else {
                continue;
            }
        }
    }

    if(countcolor1 >=5 || countcolor2>=5)
        return true;


    return false;


}


void BubbleSort(int arr[], int size)
{
    int i, j, temp;

    for(i=0;i<size;i++)
    {
        for(j=0;j<size-i-1;j++)
        {
            if(arr[j] > arr[j+1])
            {
                temp = arr[j+1];
                arr[j+1] = arr[j];
                arr[j] = temp;
            }
        }
    }
}


void CombineArr(int comp[], int hand[], int compSize, int handSize, int combinedArr[])
{
    for (int i = 0; i < compSize; i++)
    {
        combinedArr[i] = comp[i];
    }

    for (int i = 0; i < handSize; i++)
    {
        combinedArr[compSize + i] = hand[i];
    }
}


bool hasStraight(Hand hand, CommunityCards communityCards)
{
    int combinedSize = NUM_CARDS_IN_HAND + communityCards.num_cards;
    Card combinedArr[combinedSize];

    for (int i = 0; i < NUM_CARDS_IN_HAND; i++) {
        combinedArr[i] = hand.cards[i];
    }
    for (int i = 0; i < communityCards.num_cards; i++) {
        combinedArr[NUM_CARDS_IN_HAND + i] = communityCards.cards[i];
    }


    for (int i = 0; i < combinedSize - 1; i++) {
        for (int j = i + 1; j < combinedSize; j++) {
            if (combinedArr[i].rank > combinedArr[j].rank) {
                Card temp = combinedArr[i];
                combinedArr[i] = combinedArr[j];
                combinedArr[j] = temp;
            }
        }
    }


    int count = 1;
    for (int i = 0; i < combinedSize - 1; i++) {
        if (combinedArr[i].rank + 1 == combinedArr[i + 1].rank) {
            count++;
            if (count >= 5) {
                return true;
            }
        } else if (combinedArr[i].rank != combinedArr[i + 1].rank) {
            count = 1;
        }
    }


    if (combinedArr[0].rank == TWO && combinedArr[1].rank == THREE && combinedArr[2].rank == FOUR &&
        combinedArr[3].rank == FIVE && combinedArr[4].rank == ACE) {
        return true;
    }

    return false;
}


int threeSamePairsInComputer(CommunityCards communityCards)
{
    int count=0;
    for(int i=0;i<communityCards.num_cards-1;i++)//check if you have a pair in the computer only
    {
        for(int j=i+1;j<communityCards.num_cards;j++)
        {
            if(communityCards.cards[i].rank == communityCards.cards[j].rank)
                count++;
            if(count==3)
                return communityCards.cards[i].rank;
        }
    }
}//need check again if it works


bool IsthreeSamePairsInComputer(CommunityCards communityCards)
{
    int count=0;
    for(int i=0;i<communityCards.num_cards-1;i++)//check if you have a pair in the computer only
    {
        for(int j=i+1;j<communityCards.num_cards;j++)
        {
            if(communityCards.cards[i].rank == communityCards.cards[j].rank)
                count++;
            if(count==3)
                return true;        }
    }
    return false;
}//need check again if it works

bool hasFourPair(Hand hand, CommunityCards communityCards)
{
    int countWhenHasPair = 0;

    if (hasPairInHand(hand))
    {
        // Loop over all cards in hand and community cards
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < communityCards.num_cards; j++)
            {
                if (hand.cards[i].rank == communityCards.cards[j].rank)
                {
                    countWhenHasPair++;

                    if (countWhenHasPair == 3)
                    {
                        return true; // Found four of a kind
                    }
                }
            }
        }
    }

    // Check for three same pairs in community cards
    if (IsthreeSamePairsInComputer(communityCards))
    {
        if (threeSamePairsInComputer(communityCards) == hand.cards[0].rank ||
            threeSamePairsInComputer(communityCards) == hand.cards[1].rank)
        {
            return true; // Found four of a kind
        }
    }

    return false; // No four of a kind found
}


bool hasFullHouse(Hand hand,CommunityCards communityCards)
{
    if(hasPairInHand(hand) && threeSamePairsInComputer(communityCards))
    {
        return true;
    }

    else
    {
      int countfirst = 1;
      int countsecond = 1;

        for(int i=0;i<communityCards.num_cards-2;i++)
        {

                if(hand.cards[0].rank == communityCards.cards[i].rank)
                {
                    countfirst++;
                }
                else if(hand.cards[1].rank == communityCards.cards[i].rank)
                {
                    countsecond++;
                }
                if((countfirst==3 && countsecond==2) || (countfirst==2 && countsecond==3))
                {
                    return true;
                }

        }
    }


return false;

}

bool hasStraightFlush(Hand hand, CommunityCards communityCards)
{
    int combinedSize = NUM_CARDS_IN_HAND + communityCards.num_cards;
    Card combinedArr[combinedSize];


    //setting the combine array

    for (int i = 0; i < NUM_CARDS_IN_HAND; i++) {
        combinedArr[i] = hand.cards[i];
    }
    for (int i = 0; i < communityCards.num_cards; i++) {
        combinedArr[NUM_CARDS_IN_HAND + i] = communityCards.cards[i];
    }


    for (int i = 0; i < combinedSize - 1; i++) {
        for (int j = i + 1; j < combinedSize; j++) {
            if (combinedArr[i].rank > combinedArr[j].rank) {
                Card temp = combinedArr[i];
                combinedArr[i] = combinedArr[j];
                combinedArr[j] = temp;
            }
        }
    }

//start the checking

    int count = 1;
    for (int i = 0; i < combinedSize - 1; i++) {
        if (combinedArr[i].rank + 1 == combinedArr[i + 1].rank && combinedArr[i].suit == combinedArr[i+1].suit) {
            count++;
            if (count >= 5) {
                return true;
            }
        } else if (combinedArr[i].rank != combinedArr[i + 1].rank) {
            count = 1;
        }
    }

//its for the case the ace is continue from the ace -- need another one one the king if keep going to ace and 2 and 3 and so on

    if (combinedArr[0].rank == TWO && combinedArr[1].rank == THREE && combinedArr[2].rank == FOUR &&
        combinedArr[3].rank == FIVE && combinedArr[4].rank == ACE)
    {
        if(combinedArr[0].suit == combinedArr[1].suit && combinedArr[1].rank == combinedArr[2].suit && combinedArr[2].suit == combinedArr[3].suit&& combinedArr[3].rank == combinedArr[4].suit)
        {

         return true;
        }
    }

    return false;
}


bool IsChanceRoyal(Card cards[]) {
    return cards[4].rank == ACE && cards[3].rank == KING && cards[2].rank == QUEEN && cards[1].rank == JACK && cards[0].rank == TEN &&
           cards[0].suit == cards[1].suit && cards[0].suit == cards[2].suit && cards[0].suit == cards[3].suit && cards[0].suit == cards[4].suit;
}


bool hasRoyalFlush(Hand hand, CommunityCards communityCards)
{


 Card allCards[NUM_CARDS_IN_HAND+ communityCards.num_cards];

    for (int i = 0; i < NUM_CARDS_IN_HAND; i++) {
        allCards[i] = hand.cards[i];
    }


    for (int i = 0; i < NUM_COMMUNITY_CARDS; i++) {
        allCards[NUM_CARDS_IN_HAND + i] = communityCards.cards[i];
    }


    for (int i = 0; i < NUM_COMMUNITY_CARDS + NUM_CARDS_IN_HAND - 1; i++) {
        for (int j = 0; j < NUM_COMMUNITY_CARDS + NUM_CARDS_IN_HAND - i - 1; j++) {
            if (allCards[j].rank > allCards[j + 1].rank) {
                Card temp = allCards[j];
                allCards[j] = allCards[j + 1];
                allCards[j + 1] = temp;
            }
        }
    }

    Card New_High[5];

    //VERY NOT EFFICIENT!!!!! TRY TO FIX WHEN YOU DONE!!!


        for(int i=0;i<5;i++)
        {
            New_High[i] = allCards[NUM_CARDS_IN_HAND+ communityCards.num_cards - 5 + i];
        }

        if(IsChanceRoyal(New_High))
        {
            return true;
        }

        return false;
        }

//-----------------SET OF FUNCTION TO DETERMINE WHO THE WINNER IS IF THE CARD HAND IS EQUAL------------------------------//
void sortCards(Card cards[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (cards[j].rank > cards[j + 1].rank) {
                Card temp = cards[j];
                cards[j] = cards[j + 1];
                cards[j + 1] = temp;
            }
        }
    }
}

// Function to find flush
Card findFlush(Card cards[], int size) {
    int count = 1;
    Card target;
    for (int i = 0; i < size - 1; i++) {
        if (cards[i].suit == cards[i + 1].suit) {
            count++;
            if (count >= 5) {
                target = cards[i + 1]; // Store the last card of the flush
            }
        } else {
            count = 1;
        }
    }
    return target;
}

int maxCard(int num1, int num2)
{
    if (num1 == num2) {
        return 0;
    }
    return (num1 > num2 ) ? 1 : 2;
}


bool hasTwoPairInComputer(CommunityCards CommunityCards) {
    int countPair = 0;

    for (int i = 0; i < CommunityCards.num_cards - 1; i++) {
        for (int j = i + 1; j < CommunityCards.num_cards; j++) {
            if (CommunityCards.cards[i].rank == CommunityCards.cards[j].rank) {
                countPair++;
                for(int k=j; k<CommunityCards.num_cards; k++) {
                    if(CommunityCards.cards[i].rank == CommunityCards.cards[k].rank ) {
                        return false;
                    }
                }
                break;
            }
        }
    }

    return countPair == 2;
}
//need a little check

bool hasThreePairInComupter(CommunityCards CommunityCards)
{
    int countPair = 1;
    for(int i=0; i<CommunityCards.num_cards-1; i++)
    {
        countPair = 1;
        for(int j=i+1; j<CommunityCards.num_cards;j++)
        {
            if(CommunityCards.cards[i].rank == CommunityCards.cards[j].rank)
            {
                countPair++;
            }
            if(countPair==3)
                return true;
        }
    }
    return false;
}

int theCardThatMatch(Player player,CommunityCards communityCards)
{
    for(int i=0;i<communityCards.num_cards; i++)
    {
        if(player.hand.cards[0].rank == communityCards.cards[i].rank)
        {
            return player.hand.cards[0].rank;
        }
        else if(player.hand.cards[1].rank == communityCards.cards[i].rank)
        {
            return player.hand.cards[1].rank;
        }
        else
        {
            continue;
        }
    }
}

//helping function for the checking function,not efficient at all i think! need to check

int IfBothHasPair(Player player1,Player player2,CommunityCards communityCards)
{



   int firstPair=0,secondPair=0;

   if(player1.hand.cards[0].rank == player1.hand.cards[1].rank)
   {firstPair == player1.hand.cards[0].rank;}

   if(player2.hand.cards[0].rank == player2.hand.cards[1].rank)
   {secondPair == player2.hand.cards[0].rank;}

   if(firstPair > 0 && secondPair > 0)
   {
       if(firstPair>secondPair)
            return 1;
       else if(secondPair>firstPair)
            return 2;
        else
            return 0;//means that its a tie
   }

    for(int i=0;i<NUM_CARDS_IN_HAND;i++)//check if you have a pair with the computer also
    {
        for(int j=0;j<communityCards.num_cards;j++)
        {
            if(player1.hand.cards[i].rank == communityCards.cards[j].rank)
                firstPair = communityCards.cards[j].rank;
            else if(player2.hand.cards[i].rank == communityCards.cards[j].rank)
                secondPair = communityCards.cards[j].rank;

               if(firstPair > 0 && secondPair > 0)
                {
                    if(firstPair>secondPair)
                        return 1;
                    else if(secondPair>firstPair)
                        return 2;
                    else
                        return 0;
                }
        }

    }

    for(int i=0;i<communityCards.num_cards-1;i++)//check if you have a pair in the computer only-the winner is the one with the high card
    {
        for(int j=i+1;j<communityCards.num_cards;j++)
        {
            if(communityCards.cards[i].rank == communityCards.cards[j].rank)
                if(FirsthasHighCard(player1,player2))
                   {
                       return 1;
                   }
                else if(SecondhasHighCard(player1,player2))
                   {
                      return 2;
                   }
        }
    }


return 0;

}

int IfBothHasTwoPair(Player player1,Player player2,CommunityCards communityCards)
{

    int firstpairfirst,firstpairsecond;
    int secondpairfirst,secondpairsecond;

    int maxfirst,maxsecond;

    if(hasTwoPairInComputer(communityCards))
    {
    return maxCard(max(player1.hand.cards[0].rank,player1.hand.cards[1].rank),max(player2.hand.cards[0].rank,player2.hand.cards[1].rank));//retrun the player with the highest card-check the highest card from each player!
    }

     else if(hasPairInHand(player1.hand))
    {
        firstpairfirst == player1.hand.cards[0].rank;

        if(hasPairInHand(player2.hand))
            {
                secondpairfirst == player2.hand.cards[0].rank;
                return maxCard(firstpairfirst,secondpairfirst);

            }
        else
        {
            return maxCard(firstpairfirst,theCardThatMatch(player2,communityCards));
        }

    }

    else if(hasPairInHand(player2.hand))
    {
        secondpairfirst = player2.hand.cards[0].rank;
        if(hasPairInHand(player1.hand))
        {
            return maxCard(max(player1.hand.cards[0].rank,player1.hand.cards[1].rank),max(player2.hand.cards[0].rank,player2.hand.cards[1].rank));
        }
        else
        {
            return maxCard(theCardThatMatch(player1,communityCards),secondpairfirst);
        }
    }

    else
    {
        return maxCard(max(player1.hand.cards[0].rank,player1.hand.cards[1].rank),max(player2.hand.cards[0].rank,player2.hand.cards[1].rank));
    }
    return 0;
}

int BothHasThreePair(Player player1,Player player2,CommunityCards communityCards)
{


    //because else it would be 4 of kind or full house  ---- we know that when you activate this function there must be only 3 of kind

return maxCard(max(player1.hand.cards[0].rank,player1.hand.cards[1].rank),max(player2.hand.cards[0].rank,player2.hand.cards[1].rank));
}

int BothHasStraight(Player player1,Player player2,CommunityCards CommunityCards)
{
 Card firstallCards[NUM_CARDS_IN_HAND+ CommunityCards.num_cards];

    for (int i = 0; i < NUM_CARDS_IN_HAND; i++) {
        firstallCards[i] = player1.hand.cards[i];
    }


    for (int i = 0; i < NUM_COMMUNITY_CARDS; i++) {
        firstallCards[NUM_CARDS_IN_HAND + i] = CommunityCards.cards[i];
    }


    for (int i = 0; i < NUM_COMMUNITY_CARDS + NUM_CARDS_IN_HAND - 1; i++) {
        for (int j = 0; j < NUM_COMMUNITY_CARDS + NUM_CARDS_IN_HAND - i - 1; j++) {
            if (firstallCards[j].rank > firstallCards[j + 1].rank) {
                Card temp = firstallCards[j];
                firstallCards[j] = firstallCards[j + 1];
                firstallCards[j + 1] = temp;
            }
        }
    }

 Card secondallCards[NUM_CARDS_IN_HAND+ CommunityCards.num_cards];

    for (int i = 0; i < NUM_CARDS_IN_HAND; i++) {
        secondallCards[i] = player2.hand.cards[i];
    }


    for (int i = 0; i < NUM_COMMUNITY_CARDS; i++) {
        secondallCards[NUM_CARDS_IN_HAND + i] = CommunityCards.cards[i];
    }


    for (int i = 0; i < NUM_COMMUNITY_CARDS + NUM_CARDS_IN_HAND - 1; i++) {
        for (int j = 0; j < NUM_COMMUNITY_CARDS + NUM_CARDS_IN_HAND - i - 1; j++) {
            if (secondallCards[j].rank > secondallCards[j + 1].rank) {
                Card temp = secondallCards[j];
                secondallCards[j] = secondallCards[j + 1];
                secondallCards[j + 1] = temp;
            }
        }
    }

 return maxCard(firstallCards[NUM_CARDS_IN_HAND+CommunityCards.num_cards].rank , secondallCards[NUM_CARDS_IN_HAND + CommunityCards.num_cards].rank);


}

int BothHasFlush(Player player1, Player player2, CommunityCards CommunityCards)
{
    Card firstallCards[NUM_CARDS_IN_HAND + CommunityCards.num_cards];
    Card secondallCards[NUM_CARDS_IN_HAND + CommunityCards.num_cards];

    // Combine player1's hand with community cards
    for (int i = 0; i < NUM_CARDS_IN_HAND; i++) {
        firstallCards[i] = player1.hand.cards[i];
        secondallCards[i] = player2.hand.cards[i];
    }

    for (int i = 0; i < NUM_COMMUNITY_CARDS; i++) {
        firstallCards[NUM_CARDS_IN_HAND + i] = CommunityCards.cards[i];
        secondallCards[NUM_CARDS_IN_HAND + i] = CommunityCards.cards[i];
    }

    // Sort cards by rank
    sortCards(firstallCards, NUM_CARDS_IN_HAND + CommunityCards.num_cards);
    sortCards(secondallCards, NUM_CARDS_IN_HAND + CommunityCards.num_cards);

    // Check for flushes
    Card first_target = findFlush(firstallCards, NUM_CARDS_IN_HAND + CommunityCards.num_cards);
    Card second_target = findFlush(secondallCards, NUM_CARDS_IN_HAND + CommunityCards.num_cards);

    return maxCard(first_target.rank, second_target.rank);
}

int BothHasFullHouse(Player player1,Player player2,CommunityCards CommunityCards)
{

     Card firstallCards[NUM_CARDS_IN_HAND+ CommunityCards.num_cards];

    for (int i = 0; i < NUM_CARDS_IN_HAND; i++) {
        firstallCards[i] = player1.hand.cards[i];
    }


    for (int i = 0; i < NUM_COMMUNITY_CARDS; i++) {
        firstallCards[NUM_CARDS_IN_HAND + i] = CommunityCards.cards[i];
    }

    int firsttwopair;
    int firstthreepair;
    int firstcount = 0;

    for(int i=0;i<CommunityCards.num_cards;i++)
    {
        for(int j=i+1; j<CommunityCards.num_cards+1;j++)
        {
        if(firstallCards[i].rank == firstallCards[j].rank)
            firstcount++;
        if(firstcount>2)
            firstthreepair=firstallCards[i].rank;
        if(firstthreepair>0)
        {
            if(firstcount==2)
                firsttwopair = firstallCards[i].rank;
        }
        }
        firstcount=0;
    }


    Card secondallCards[NUM_CARDS_IN_HAND+ CommunityCards.num_cards];

    for (int i = 0; i < NUM_CARDS_IN_HAND; i++) {
        secondallCards[i] = player2.hand.cards[i];
    }


    for (int i = 0; i < NUM_COMMUNITY_CARDS; i++) {
        secondallCards[NUM_CARDS_IN_HAND + i] = CommunityCards.cards[i];
    }

    int secondtwopair;
    int secondthreepair;
    int secondcount=0;

        for(int i=0;i<CommunityCards.num_cards;i++)
    {
        for(int j=i+1; j<CommunityCards.num_cards+1;j++)
        {
        if(secondallCards[i].rank == secondallCards[j].rank)
            secondcount++;
        if(secondcount>2)
            secondthreepair=secondallCards[i].rank;
       if(secondthreepair>0)
       {
         if(secondcount==2)
                secondtwopair = secondallCards[i].rank;
       }

        }
        secondcount=0;
    }




    if(maxCard(firstthreepair,secondthreepair)!=0)
        return maxCard(firstthreepair,secondthreepair);
    else if(maxCard(firsttwopair,secondtwopair)!=0)
        return maxCard(firsttwopair,secondtwopair);
    else
    return 0;
}

int BothHasFourPair(Player player1,Player player2,CommunityCards CommunityCards)
{
    Card firstallCards[NUM_CARDS_IN_HAND+ CommunityCards.num_cards];

    for (int i = 0; i < NUM_CARDS_IN_HAND; i++) {
        firstallCards[i] = player1.hand.cards[i];
    }


    for (int i = 0; i < NUM_COMMUNITY_CARDS; i++) {
        firstallCards[NUM_CARDS_IN_HAND + i] = CommunityCards.cards[i];
    }

    int first_target;
    int firstcount=0;
    sortCards(firstallCards,2+CommunityCards.num_cards);
    for(int i=0;i<CommunityCards.num_cards;i++)
    {
        for(int j=i+1;j<CommunityCards.num_cards+1;j++)
    {
     if(firstallCards[i].rank == firstallCards[j].rank)
            firstcount++;

     if(firstcount>3)
     first_target = firstallCards[i].rank;

    }
    firstcount=0;
    }

    Card secondallCards[NUM_CARDS_IN_HAND+ CommunityCards.num_cards];

    for (int i = 0; i < NUM_CARDS_IN_HAND; i++) {
        secondallCards[i] = player2.hand.cards[i];
    }


    for (int i = 0; i < NUM_COMMUNITY_CARDS; i++) {
        secondallCards[NUM_CARDS_IN_HAND + i] = CommunityCards.cards[i];
    }


    int second_target;
    int secondcount=0;
    sortCards(secondallCards,2+CommunityCards.num_cards);
    for(int i=0;i<CommunityCards.num_cards;i++)
    {
        for(int j=i+1;j<CommunityCards.num_cards+1;j++)
    {
     if(secondallCards[i].rank == secondallCards[j].rank)
            secondcount++;

     if(secondcount>3)
     second_target = secondallCards[i].rank;

    }
    secondcount=0;
    }

    return maxCard(first_target,second_target);

}

int BothHasStraightFlush(Player player1, Player player2, CommunityCards CommunityCards)
{
    Card firstallCards[NUM_CARDS_IN_HAND + CommunityCards.num_cards];

    // Combine player1's hand with community cards
    for (int i = 0; i < NUM_CARDS_IN_HAND; i++) {
        firstallCards[i] = player1.hand.cards[i];
    }

    for (int i = 0; i < CommunityCards.num_cards; i++) {
        firstallCards[NUM_CARDS_IN_HAND + i] = CommunityCards.cards[i];
    }

    // Sort cards by rank and then by suit
    sortCards(firstallCards, NUM_CARDS_IN_HAND + CommunityCards.num_cards);

    // Initialize variables to track straight flush
    int maxStraightFlushRank1 = -1;
    int straightFlushRankCount1 = 1;

    // Check for straight flush in player1's hand and community cards
    for (int i = 0; i < NUM_CARDS_IN_HAND + CommunityCards.num_cards - 1; i++) {
        if (firstallCards[i].suit == firstallCards[i + 1].suit && // Same suit
            firstallCards[i].rank == firstallCards[i + 1].rank - 1) { // Consecutive ranks
            straightFlushRankCount1++;
            if (straightFlushRankCount1 >= 5) {
                maxStraightFlushRank1 = firstallCards[i + 1].rank; // Update max rank
            }
        } else {
            straightFlushRankCount1 = 1; // Reset count
        }
    }

    Card secondallCards[NUM_CARDS_IN_HAND + CommunityCards.num_cards];

    // Combine player2's hand with community cards
    for (int i = 0; i < NUM_CARDS_IN_HAND; i++) {
        secondallCards[i] = player2.hand.cards[i];
    }

    for (int i = 0; i < CommunityCards.num_cards; i++) {
        secondallCards[NUM_CARDS_IN_HAND + i] = CommunityCards.cards[i];
    }

    // Sort cards by rank and then by suit
    sortCards(secondallCards, NUM_CARDS_IN_HAND + CommunityCards.num_cards);

    // Initialize variables to track straight flush
    int maxStraightFlushRank2 = -1;
    int straightFlushRankCount2 = 1;

    // Check for straight flush in player2's hand and community cards
    for (int i = 0; i < NUM_CARDS_IN_HAND + CommunityCards.num_cards - 1; i++) {
        if (secondallCards[i].suit == secondallCards[i + 1].suit && // Same suit
            secondallCards[i].rank == secondallCards[i + 1].rank - 1) { // Consecutive ranks
            straightFlushRankCount2++;
            if (straightFlushRankCount2 >= 5) {
                maxStraightFlushRank2 = secondallCards[i + 1].rank; // Update max rank
            }
        } else {
            straightFlushRankCount2 = 1; // Reset count
        }
    }

    // Determine the winner based on the max rank of straight flush
    return maxCard(maxStraightFlushRank1, maxStraightFlushRank2);
}

//------------------END OF HELPING FUNCTION---------------------//

int whoIsWinner(Player player1, Player player2,CommunityCards communityCards) {
    // Check if either player has folded
    if (player1.folded && player2.folded) {
        // Both players have folded, return a tie
        return 0;
    } else if (player1.folded) {
        // Player 1 has folded, player 2 wins
        return 2;
    } else if (player2.folded) {
        // Player 2 has folded, player 1 wins
        return 1;
    }

    // Compare the hands of the two players
    // Check for Royal Flush

    if (hasRoyalFlush(player1.hand, communityCards) && !hasRoyalFlush(player2.hand, communityCards)) {
        return 1;  // Player 1 wins with Royal Flush
    } else if (!hasRoyalFlush(player1.hand, communityCards) && hasRoyalFlush(player2.hand, communityCards)) {
        return 2;  // Player 2 wins with Royal Flush
    }

    // Check for Straight Flush
     if(hasStraightFlush(player1.hand,communityCards) && hasStraightFlush(player2.hand,communityCards))
        return BothHasStraightFlush(player1,player2,communityCards);
      else if (hasStraightFlush(player1.hand, communityCards) && !hasStraightFlush(player2.hand, communityCards)) {
        return 1;  // Player 1 wins with Straight Flush
    } else if (!hasStraightFlush(player1.hand, communityCards) && hasStraightFlush(player2.hand, communityCards)) {
        return 2;  // Player 2 wins with Straight Flush
    }

    // Check for Four of a Kind
    if(hasFourPair(player1.hand,communityCards) && hasFourPair(player2.hand,communityCards))
        return BothHasFourPair(player1,player2,communityCards);
    else if (hasFourPair(player1.hand, communityCards) && !hasFourPair(player2.hand, communityCards)) {
        return 1;  // Player 1 wins with Four of a Kind
    } else if (!hasFourPair(player1.hand, communityCards) && hasFourPair(player2.hand, communityCards)) {
        return 2;  // Player 2 wins with Four of a Kind
    }

    // Check for Full House
    if(hasFullHouse(player1.hand,communityCards) && hasFullHouse(player2.hand,communityCards))
        return BothHasFullHouse(player1,player2,communityCards);
    if (hasFullHouse(player1.hand, communityCards) && !hasFullHouse(player2.hand, communityCards)) {
        return 1;  // Player 1 wins with Full House
    } else if (!hasFullHouse(player1.hand, communityCards) && hasFullHouse(player2.hand, communityCards)) {
        return 2;  // Player 2 wins with Full House
    }

    // Check for Flush
    if(hasFlush(player1.hand,communityCards) && hasFlush(player2.hand,communityCards))
        return BothHasFlush(player1,player2,communityCards);
    if (hasFlush(player1.hand, communityCards) && !hasFlush(player2.hand, communityCards)) {
        return 1;  // Player 1 wins with Flush
    } else if (!hasFlush(player1.hand, communityCards) && hasFlush(player2.hand, communityCards)) {
        return 2;  // Player 2 wins with Flush
    }

    // Check for Straight
    if(hasStraight(player1.hand,communityCards) && hasStraight(player2.hand,communityCards))
        return BothHasStraight(player1,player2,communityCards);
    if (hasStraight(player1.hand, communityCards) && !hasStraight(player2.hand, communityCards)) {
        return 1;  // Player 1 wins with Straight
    } else if (!hasStraight(player1.hand, communityCards) && hasStraight(player2.hand, communityCards)) {
        return 2;  // Player 2 wins with Straight
    }

    // Check for Three of a Kind
    if(hasThreePair(player1.hand,communityCards) && hasThreePair(player2.hand,communityCards))
        return BothHasThreePair(player1,player2,communityCards);
    if (hasThreePair(player1.hand, communityCards) && !hasThreePair(player2.hand, communityCards)) {
        return 1;  // Player 1 wins with Three of a Kind
    } else if (!hasThreePair(player1.hand, communityCards) && hasThreePair(player2.hand, communityCards)) {
        return 2;  // Player 2 wins with Three of a Kind
    }

    // Check for Two Pair
    if(hasTwoPair(player1.hand,communityCards) && hasTwoPair(player2.hand,communityCards))
        return IfBothHasTwoPair(player1,player2,communityCards);
    if (hasTwoPair(player1.hand, communityCards) && !hasTwoPair(player2.hand, communityCards)) {
        return 1;  // Player 1 wins with Two Pair
    } else if (!hasTwoPair(player1.hand, communityCards) && hasTwoPair(player2.hand, communityCards)) {
        return 2;  // Player 2 wins with Two Pair
    }

    // Check for Pair
    if(hasPair(player1.hand,communityCards) && hasPair(player2.hand,communityCards))
        return IfBothHasPair(player1,player2,communityCards);
    if (hasPair(player1.hand, communityCards) && !hasPair(player2.hand, communityCards)) {
        return 1;  // Player 1 wins with Pair
    } else if (!hasPair(player1.hand, communityCards) && hasPair(player2.hand, communityCards)) {
        return 2;  // Player 2 wins with Pair
    }

    // If no one wins with a high hand, compare high cards
    if (FirsthasHighCard(player1, player2)) {
        return 1;  // Player 1 wins with high card
    } else if (SecondhasHighCard(player1, player2)) {
        return 2;  // Player 2 wins with high card
    }

    // If both players have the same hand, it's a tie
    return 0;
}

//--------------------START OF GAME FLOW FUNCTIONS---------------------------//

// Function to initialize the deck with cards
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


void RemoveCardFromDeck(Deck* deck, Card cardToRemove) {
    // Find the index of the card to remove in the deck
    int indexToRemove = -1;
    for (int i = 0; i < deck->num_cards; i++) {
        if (deck->cards[i].rank == cardToRemove.rank && deck->cards[i].suit == cardToRemove.suit) {
            indexToRemove = i;
            break;
        }
    }

    // If the card is found, remove it by shifting the cards after it
    if (indexToRemove != -1) {
        for (int i = indexToRemove; i < deck->num_cards - 1; i++) {
            deck->cards[i] = deck->cards[i + 1];
        }
        // Decrease the count of cards in the deck
        deck->num_cards--;
    }
}


void DealCards(Player* player1, Player* player2, CommunityCards* communityCards, Deck* deck) {
    // Shuffle the deck before dealing
    ShuffleDeck(deck);

    // Deal cards to players
    for (int i = 0; i < NUM_CARDS_IN_HAND; i++) {
        player1->hand.cards[i] = deck->cards[i];
        player2->hand.cards[i] = deck->cards[NUM_CARDS_IN_HAND + i];
    }

    // Remove dealt cards from the deck
    for (int i = 0; i < NUM_CARDS_IN_HAND; i++) {
        RemoveCardFromDeck(deck, player1->hand.cards[i]);
        RemoveCardFromDeck(deck, player2->hand.cards[i]);
    }

    // Deal community cards
    for (int i = 0; i < NUM_COMMUNITY_CARDS; i++) {
        communityCards->cards[i] = deck->cards[2 * NUM_CARDS_IN_HAND + i];
    }

    // Remove dealt community cards from the deck
    for (int i = 0; i < NUM_COMMUNITY_CARDS; i++) {
        RemoveCardFromDeck(deck, communityCards->cards[i]);
    }

    // Update the number of cards in the players' and community cards' hands
    player1->hand.num_cards = NUM_CARDS_IN_HAND;
    player2->hand.num_cards = NUM_CARDS_IN_HAND;
    communityCards->num_cards = NUM_COMMUNITY_CARDS;
}


void BettingRound(Player* player1, Player* player2, CommunityCards* CommunityCards) {

    // Placeholder logic for a simple betting round
    // In a real implementation, you'd have more sophisticated betting rules

    // Assume player1 starts the betting
    Player* currentPlayer = player1;

    // Continue the betting round until both players have had a chance to act
    bool player1HasActed = false;
    bool player2HasActed = false;

    while (!player1HasActed || !player2HasActed) {
        // Simulate player actions (replace with your actual logic)
        // Here we're just printing the player's action
        printf("%s's turn to act:\n", currentPlayer == player1 ? "Player 1" : "Player 2");
        printf("1. Bet\n2. Call\n3. Fold\n4. Raise\n");

        // Simulate player choosing an action (replace with your actual logic)
        // Here we're just reading input from the user
        int action;
        scanf("%d", &action);

        // Variables to track each player's chips
        int player1_chips = player1->chips;
        int player2_chips = player2->chips;

        // Determine which player's turn it is
        int* play_now_chips;
        bool* play_now_has_acted;
        bool* opponent_has_acted;
        if (currentPlayer == player1) {
            play_now_chips = &player1_chips;
            play_now_has_acted = &player1HasActed;
            opponent_has_acted = &player2HasActed;
        } else {
            play_now_chips = &player2_chips;
            play_now_has_acted = &player2HasActed;
            opponent_has_acted = &player1HasActed;
        }

        // Variable to hold the bet amount
        int bet;

        switch (action) {
            case 1:
                // Player wants to bet
                printf("Insert the bet amount: ");
                scanf("%d", &bet);
                if (bet > *play_now_chips) {
                    // If the bet amount exceeds player's chips, force player to go all-in
                    printf("Not enough chips. Going all-in with %d chips.\n", *play_now_chips);
                    bet = *play_now_chips;
                    *play_now_chips = 0;
                } else {
                    // Subtract bet amount from player's chips
                    *play_now_chips -= bet;
                }
                break;
            case 2:
                // Player wants to call (match current bet) or raise
                if (*opponent_has_acted) {
                    // Opponent has already acted, so player can choose to call or raise
                    printf("1. Call\n2. Raise\n");
                    int call_or_raise;
                    scanf("%d", &call_or_raise);
                    switch (call_or_raise) {
                        case 1:
                            // Player calls
                            printf("Player calls.\n");
                            // Implement call logic here
                            break;
                        case 2:
                            // Player raises
                            printf("Insert the raise amount: ");
                            scanf("%d", &bet);
                            if (bet > *play_now_chips) {
                                // If the raise amount exceeds player's chips, force player to go all-in
                                printf("Not enough chips. Going all-in with %d chips.\n", *play_now_chips);
                                bet = *play_now_chips;
                                *play_now_chips = 0;
                            } else {
                                // Subtract raise amount from player's chips
                                *play_now_chips -= bet;
                            }
                            // Implement raise logic here
                            break;
                        default:
                            printf("Invalid action.\n");
                            break;
                    }
                } else {
                    // Opponent has not acted yet, so player can only call
                    printf("Player calls.\n");
                    // Implement call logic here
                }
                break;
            case 3:
                // Player wants to fold
                printf("Player folds.\n");
                // Implement fold logic here
                // Set player's folded status to true
                currentPlayer->folded = true;
                break;
            case 4:
                // Player wants to raise
                printf("Insert the raise amount: ");
                scanf("%d", &bet);
                if (bet > *play_now_chips) {
                    // If the raise amount exceeds player's chips, force player to go all-in
                    printf("Not enough chips. Going all-in with %d chips.\n", *play_now_chips);
                    bet = *play_now_chips;
                    *play_now_chips = 0;
                } else {
                    // Subtract raise amount from player's chips
                    *play_now_chips -= bet;
                }
                // Implement raise logic here
                // This would involve increasing the current bet and forcing other players to match or fold
                break;
            default:
                printf("Invalid action.\n");
                break;
        }

        // Toggle the current player
        currentPlayer = (currentPlayer == player1) ? player2 : player1;

        // Update the flags to track if both players have acted
        *play_now_has_acted = true;
    }
}


bool IsGameOver(Player* player1, Player* player2, CommunityCards* CommunityCards) {
    // Placeholder logic for determining if the game is over
    // In a real implementation, you would need to define the conditions for game over

    // For example, if the game is over when one of the players has lost all their chips
    if (player1->chips <= 0 || player2->chips <= 0) {
        return true;
    }

    // Or if a certain number of rounds have been played
    // You can add your own conditions here

    // If none of the game-over conditions are met, return false
    return false;
}


void StartGame(Player* player1, Player* player2, CommunityCards* CommunityCards, Deck* Deck) {
    // Initialize the game (deal cards, set up initial conditions, etc.)
    DealCards(player1, player2, CommunityCards, Deck);

    // Main game loop
    while (!IsGameOver(player1, player2, CommunityCards)) {
        // Perform a betting round
        BettingRound(player1, player2, CommunityCards);

        // Additional game logic can be added here, such as dealing additional community cards

        // Check if the game is over after each round
        if (IsGameOver(player1, player2, CommunityCards)) {
            break;
        }

        // Additional rounds or actions can be added here
    }

    // After the game is over, perform any necessary cleanup or display the results
    // For example, display the winner, reset the game state for a new game, etc.
    printf("Game over!\n");

    // Determine the winner
    int winner = whoIsWinner(*player1, *player2, *CommunityCards);
    if (winner == 0) {
        printf("It's a tie!\n");
    } else if (winner == 1) {
        printf("Player 1 wins!\n");
    } else if (winner == 2) {
        printf("Player 2 wins!\n");
    }

    // Additional cleanup or actions after determining the winner
}

