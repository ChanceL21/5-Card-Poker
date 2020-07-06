#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
/*
contains the face and suit of a card, both represented by an integer
*/
typedef struct card
{
	int face;
	int suit;
} Card;

/*
contains an array of 5 struct cards, which represents a players hand
*/
typedef struct hand
{
	Card cards[5];
} Hand;

/*
Description: prints menu to user
Date Created: 11/14/2019
Date Modified: 11/16/2019
Parameter Type: void
Return Type: void
Preconditions: none
Postconditions: none
*/
void display_menu(void);

/*
Description: prompts user for option correspond to menu selection
Date Created: 11/14/2019
Date Modified: 11/16/2019
Parameter Type: void
Return Type: int
Preconditions: none
Postconditions: none
*/
int get_option(void);

/*
Description: determines if menu option is satisfactory. Returns 1 if so, and 0 otherwise
Date Created: 11/14/2019
Date Modified: 11/16/2019
Parameter Type: int
Return Type: int
Preconditions: none
Postconditions: none
*/
int evaluate_option(int option);

/*
Description: Continuously displays menu until proper option is input
Date Created: 11/14/2019
Date Modified: 11/16/2019
Parameter Type: void
Return Type: int
Preconditions: none
Postconditions: none
*/
int menu_select(void);

/*
Description: Prints Poker rules to user
Date Created: 11/14/2019
Date Modified: 11/16/2019
Parameter Type: void
Return Type: void
Preconditions: none
Postconditions: none
*/
void display_rules(void);

/*
Description: Handles main gameplay of Poker
Date Created: 11/14/2019
Date Modified: 11/16/2019
Parameter Type: void
Return Type: void
Preconditions: none
Postconditions: none
*/
void play_game();

/*
Description: randomly assigns numbers 1 through 52 to a suit and a face in a 2 dimensional int array, effectively shuffling the cards
Date Created: 11/14/2019
Date Modified: 11/16/2019
Parameter Type: 2D int array
Return Type: void
Preconditions: none
Postconditions: array modified
*/
void shuffle(int wDeck[][13]);

/*
Description: deals cards and adds them to a hand. Only replaces a card if the player intended it to be
Date Created: 11/14/2019
Date Modified: 11/16/2019
Parameter Type: 2D int array, const char array, const char array, int, Hand, int array
Return Type: void
Preconditions: none
Postconditions: Hand and deck spot modified
*/
void deal(const int wDeck[][13], const char* wFace[], const char* wSuit[], int* deck_spot, Hand* hand, int replaced[5]);

/*
Description: Displays hand to screen
Date Created: 11/14/2019
Date Modified: 11/16/2019
Parameter Type: face array, suit array, Hand
Return Type: void
Preconditions: none
Postconditions: none
*/
void display_hand(const char* wFace[], const char* wSuit[], Hand hand);

/*
Description: asks players which cards to replace. 1 represents a card to be replaced, 0 represents a kept card.
Date Created: 11/14/2019
Date Modified: 11/16/2019
Parameter Type: int array
Return Type: void
Preconditions: none
Postconditions: replacement array modified
*/
void player_cards_to_replace(int player_replaced[5]);

/*
Description: checks if a character is either y or n. returns 1 if y, 0 if n.
Date Created: 11/14/2019
Date Modified: 11/16/2019
Parameter Type: char
Return Type: int
Preconditions: none
Postconditions: none
*/
int check_yes_no(char yes_no);

/*
Description: returns 1 if player wants to play again, 0 otherwise
Date Created: 11/14/2019
Date Modified: 11/16/2019
Parameter Type: void
Return Type: int
Preconditions: none
Postconditions: none
*/
int play_again(void);

/*
Description: takes in a Hand sorts the hand with the most frequent faces first, and within faces that have the same frequency, sorts in descending order. 
			 For example, a hand of faces 2, 3, 5, 3, 2, would be sorted as 3, 3, 2, 2, 5.
Date Created: 11/14/2019
Date Modified: 11/16/2019
Parameter Type: Hand
Return Type: void
Preconditions: none
Postconditions: sorted_hand modified
*/
void sort_hand(Hand hand, int sorted_hand[5]);

/*
Description: determines winner based on the score type of the players, and if they are the same, determines the winner based on high card
Date Created: 11/14/2019
Date Modified: 11/16/2019
Parameter Type: int, int array, int, int array, const char* array
Return Type: void
Preconditions: none
Postconditions: none
*/
void determine_winner(int player_score, int player_sorted_faces[5], int computer_score, int computer_sorted_faces[5], const char* score[6]);

/*
Description: compares sorted face values. returns 1 if user has stronger hand, 2 if computer, and 0 if its a tie.
Date Created: 11/14/2019
Date Modified: 11/16/2019
Parameter Type: int array, int array
Return Type: int
Preconditions: none
Postconditions: none
*/
int int_array_compare(int player_sorted_faces[5], int computer_sorted_faces[5]);

/*
Description: determines the hand score, returned as 0 or 8 in ascending strength, with 0 being high card and 8 being a straight flush
Date Created: 11/14/2019
Date Modified: 11/16/2019
Parameter Type: Hand
Return Type: int
Preconditions: none
Postconditions: none
*/
int evaluate_hand(Hand hand);

/*
Description: returns 1 if hand has a flush, 0 otherwise
Date Created: 11/14/2019
Date Modified: 11/16/2019
Parameter Type: Hand
Return Type: int
Preconditions: none
Postconditions: none
*/
int flush(Hand hand);

/*
Description: returns 1 if hand has a straight, 0 otherwise
Date Created: 11/14/2019
Date Modified: 11/16/2019
Parameter Type: Hand
Return Type: int
Preconditions: none
Postconditions: none
*/
int straight(Hand hand);

/*
Description: returns 1 if hand has a four of a kind, 0 otherwise
Date Created: 11/14/2019
Date Modified: 11/16/2019
Parameter Type: Hand
Return Type: int
Preconditions: none
Postconditions: none
*/
int four_of_a_kind(Hand hand);

/*
Description: returns 1 if hand has a full house, 0 otherwise
Date Created: 11/14/2019
Date Modified: 11/16/2019
Parameter Type: Hand
Return Type: int
Preconditions: none
Postconditions: none
*/
int full_house(Hand hand);

/*
Description: returns 1 if hand has a three of a kind, 0 otherwise
Date Created: 11/14/2019
Date Modified: 11/16/2019
Parameter Type: Hand
Return Type: int
Preconditions: none
Postconditions: none
*/
int three_of_a_kind(Hand hand);

/*
Description: returns 1 if hand has a two pair, 0 otherwise
Date Created: 11/14/2019
Date Modified: 11/16/2019
Parameter Type: Hand
Return Type: int
Preconditions: none
Postconditions: none
*/
int two_pair(Hand hand);

/*
Description: returns 1 if hand has a pair, 0 otherwise
Date Created: 11/14/2019
Date Modified: 11/16/2019
Parameter Type: Hand
Return Type: int
Preconditions: none
Postconditions: none
*/
int pair(Hand hand);

/*
Description: computer replaces up to 3 cards. it will not replace any cards if it has a straight or a flush. It will only replace cards that it has no duplicates of, up to 3.
Date Created: 11/14/2019
Date Modified: 11/16/2019
Parameter Type: int array, Hand
Return Type: void
Preconditions: none
Postconditions: int array modified
*/
void computer_cards_to_replace(int computer_replaced[5], Hand hand);