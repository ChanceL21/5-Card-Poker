#include "PA7.h"

void display_menu(void) // printing menu
{
	printf("Welcome to 5-Card Poker!\n");
	printf("1. Print Game Rules\n");
	printf("2. Start a Game of Poker\n");
	printf("3. Exit\n");
}

int get_option(void) // prompts for option once
{
	int option = 0;
	printf("Please enter the number corresponding with the desired action: ");
	scanf("%d", &option);
	return option;
}

int evaluate_option(int option) // makes sure option is between 1 and 3, inclusively
{
	if (option < 1 || option > 3)
	{
		printf("That's not a valid option!\n");
		return 0; // not satisfied
	}
	else
	{
		return 1; // satisfied
	}
}

int menu_select(void) // continues to display menu until option requirements are satisfied
{
	int option = 0;
	do {
		display_menu();
		option = get_option();
		system("cls");
	} while (!evaluate_option(option));
	return option;
}


void display_rules(void) // shows poker rules
{
	printf("In this game, the user plays against the computer in 5-Card Poker.\n"
		"The goal is to end with a stronger hand than your opponent.\n"
		"The possible hands, in order of ascending strength, are listed below:\n\n"
		"Name            | Combination\n"
		"----------------------------------------------------------------------\n"
		"High Card       | No interesting Combination\n"
		"Pair            | Two cards with the same face value\n"
		"Two Pair        | Two sets of two cards with the same face value\n"
		"Three of a Kind | Three cards with the same face value\n"
		"Straight        | All five cards in sequential order\n"
		"Flush           | All five cards of the same suit\n"
		"Full House      | A three of a kind and a pair\n"
		"Four of a Kind  | Four cards with the same face value\n"
		"Straight Flush  | All five cards suited and in sequential order\n\n"
		"First, both the user and computer each draw 5 cards from a shuffled deck.\n"
		"Then both have the option to replace up to 3 cards in their hand. Finally,\n"
		"both show their cards and a winner is determined. If, for example, both players a pair,\n"
		"then the higher pair wins. If both have the same pair, then the winner is chosen based on\n"
		"who has the highest card of their remainers. If both players have a two pair, then the winner is\n"
		"the one with the highest pair. If both players have a full house, then the winner is the one with\n" 
		"the highest three of a kind. If both players have a straight or a flush, then the winner is the one\n"
		"with the highest card. In all cases, if both players have the same high card, then it is based\n"
		"on the next highest card, and so on, until a tie is possible with 2 entirely equal hands.\n");
}

void play_game() // main gameplay function
{
	char scanned_variable = '\0'; // for scanning so play can progress game at their own pace

	/* initialize suit array */
	const char* suit[4] = { "Hearts", "Diamonds", "Clubs", "Spades" };

	/* initialize face array */
	const char* face[13] = { "Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight",
		"Nine", "Ten", "Jack", "Queen", "King", "Ace" };

	/* initialize score array, indeces represent strength of hand */
	const char* score[9] = { "high card", "pair", "two pair", "three of a kind", "straight", "flush", "full house", "four of a kind", "straight flush" };

	Hand player_hand, computer_hand;
	
	do {
	
		/* initalize deck array */
		int deck[4][13] = { 0 };


		shuffle(deck);

		int deck_spot = 1;

		int player_replaced[5] = { 1, 1, 1, 1, 1 }; // 1 represents a card to be replaced when dealing. Since 5 cards are needed at beginning, all are 'replaced'
		int computer_replaced[5] = { 1, 1, 1, 1, 1 };




		deal(deck, face, suit, &deck_spot, &player_hand, player_replaced);
		deal(deck, face, suit, &deck_spot, &computer_hand, computer_replaced);


		system("cls"); //clearning screen throughout


		printf("Your hand:\n");
		display_hand(face, suit, player_hand); //showing player's hand

		player_cards_to_replace(player_replaced); // records their replaced cards
		deal(deck, face, suit, &deck_spot, &player_hand, player_replaced); // deals new cards and replaces old ones


		system("cls");

		printf("Your hand:\n");
		display_hand(face, suit, player_hand);

		printf("Enter any non-whitespace character to allow the computer to exchange its cards: ");
		scanf(" %c", &scanned_variable);

		system("cls");

		printf("Your hand:\n");
		display_hand(face, suit, player_hand);

		computer_cards_to_replace(computer_replaced, computer_hand); // letting computer determine cards to replace
		deal(deck, face, suit, &deck_spot, &computer_hand, computer_replaced); // replace them from the deck


		printf("Enter any non-whitespace character to show cards and determine a winner: ");
		scanf(" %c", &scanned_variable);

		system("cls");

		//show both hands at the end

		printf("Computer's hand:\n");
		display_hand(face, suit, computer_hand);
		printf("Your hand:\n");
		display_hand(face, suit, player_hand);


		//results

		int player_score = -1;
		int computer_score = -1;

		player_score = evaluate_hand(player_hand); // determine strength of user and computer's hand
		computer_score = evaluate_hand(computer_hand);

		int player_sorted_faces[5] = { 0, 0, 0, 0, 0 };
		int computer_sorted_faces[5] = { 0, 0, 0, 0, 0 };

		sort_hand(player_hand, player_sorted_faces);
		sort_hand(computer_hand, computer_sorted_faces); // sorting hands in case the hands have the same strength and a high card is necessary to determine winner


		determine_winner(player_score, player_sorted_faces, computer_score, computer_sorted_faces, score);


	} while (play_again()); // starts another round if player wants to
}

void shuffle(int wDeck[][13])
{
	int row = 0;    /* row number */
	int column = 0; /*column number */
	int card = 0;   /* card counter */

	/* for each of the 52 cards, choose slot of deck randomly */
	for (card = 1; card <= 52; card++)
	{
		/* choose new random location until unoccupied slot found */
		do
		{
			row = rand() % 4;
			column = rand() % 13;
		} while (wDeck[row][column] != 0);

		/* place card number in chosen slot of deck */
		wDeck[row][column] = card;
	}
}

/* deal cards in deck and fill hand, as much as necessary*/
void deal(const int wDeck[][13], const char* wFace[], const char* wSuit[], int * deck_spot, Hand * hand, int replaced[5])
{
	int row = 0;    /* row number */
	int column = 0; /*column number */

	for (int replaced_index = 0; replaced_index < 5; replaced_index++)
	{

		if (replaced[replaced_index])
		{
			/* loop through rows of wDeck */
			for (row = 0; row <= 3; row++)
			{
				/* loop through columns of wDeck for current row */
				for (column = 0; column <= 12; column++)
				{
					/* if slot contains current card, display card */
					if (wDeck[row][column] == *deck_spot)
					{
						hand->cards[replaced_index].face = column;
						hand->cards[replaced_index].suit = row;
					}
				}
			}

			*deck_spot += 1; // deck spot has to be remembered in successive dealing calls
		}
	}

}

void display_hand(const char* wFace[], const char* wSuit[], Hand hand)
{

	for (int i = 0; i < 5; i++)
	{
		printf("Card %d: %5s of %s\n", i + 1, wFace[hand.cards[i].face], wSuit[hand.cards[i].suit]); // show hand to user
	}
	printf("\n");
}

void player_cards_to_replace(int player_replaced[5])
{
	int cards_replaced = 0;
	char yes_no = '\0';

	for (int i = 0; i < 5; i++)
	{
		player_replaced[i] = 0;
	}

	for (int i = 0; i < 5 && cards_replaced < 3; i++) // ask user if they want to replace cards until they run out or until they exhaust all 3 replacements. continue to ask if input is not valid.
	{
		do {
			printf("Would you like to replace card %d? Please type 'y' for yes or 'n' for no: ", i + 1);
			scanf(" %c", &yes_no);
			

		} while (!check_yes_no(yes_no));

		if (yes_no == 'y')
		{
			player_replaced[i] = 1;
			cards_replaced += 1;
		}
	}
}

int check_yes_no(char yes_no) // check if a character is y or n, returns 1 or 0, respectively.
{
	if (yes_no != 'y' && yes_no != 'n')
	{
		printf("That is not a proper input!\n");
		return 0;
	}

	return 1;
}

int play_again(void) // returns 1 if player wants to play another round, 0 otherwise
{
	char yes_no = '\0';

	do {
		printf("Would you like to play another round? Please type 'y' for yes or 'n' for no: ");
		scanf(" %c", &yes_no);

	} while (!check_yes_no(yes_no));

	system("cls");

	if (yes_no == 'y')
	{
		return 1;
	}
	return 0;
}

void sort_hand(Hand hand, int sorted_hand[5])
{
	int sorted_index = 0;

	int face_frequency[13] = { 0 };

	int max_frequency = 0;

	for (int i = 0; i < 5; i++)
	{
		face_frequency[hand.cards[i].face] += 1; // create a frequency of all the faces
	}
	
	// record the the highest frequency of any face
	max_frequency = face_frequency[0];
	for (int i = 0; i <13; i++)
	{
		if (face_frequency[i] > max_frequency)
		{
			max_frequency = face_frequency[i];
		}
	}

	// look for any faces that are of the max frequency, and add them, consecutively, to the sorting hand, as many as the frequency is. Then do the same for one less than the max, and so on, until it is 0.
	for (int i = max_frequency; i > 0; i--)
	{
		for (int j = 12; j >= 0; j--)
		{
			if (face_frequency[j] == i)
			{
				for (int k = 0; k < i; k++)
				{
					sorted_hand[sorted_index] = j;
					sorted_index += 1;
				}
			}
		}
	}
}

void determine_winner(int player_score, int player_sorted_faces[5], int computer_score, int computer_sorted_faces[5], const char* score[6])
{
	int high_card = 0;

	if (player_score == computer_score) // if the hands have the same score (both have a pair, or a flush, etc) then a high card must be used to determine a winner
	{
		printf("Both parties have a %s.\n", score[player_score]);
		high_card = int_array_compare(player_sorted_faces, computer_sorted_faces);
		if (high_card == 0)
		{
			printf("Its a tie!\n");
		}
		else if (high_card == 1)
		{
			printf("However, you win by higher cards!\n");
		}
		else
		{
			printf("However, computer wins by higher cards!\n");
		}
	}
	else // winner is known just from the hand scores
	{

		printf("The computer has a %s.\n", score[computer_score]);
		printf("You have a %s.\n", score[player_score]);

		if (player_score > computer_score)
		{
			printf("You win!\n");
		}
		else
		{
			printf("Computer wins!\n");
		}
	}
}

int int_array_compare(int player_sorted_faces[5], int computer_sorted_faces[5]) // basically a strcmp but with an int array
{
	for (int i = 0; i < 5; i++)
	{
		if (player_sorted_faces[i] > computer_sorted_faces[i])
		{
			return 1; // player has higher significant cards
		}
		if (computer_sorted_faces[i] > player_sorted_faces[i])
		{
			return 2; // computer has high significant cards
		}
	}

	return 0; // both hands have equal value
}

int evaluate_hand(Hand hand) // return value of hand. checks for better hands first
{
	if (flush(hand) && straight(hand)) //straight flush
	{
		return 8;
	}
	if (four_of_a_kind(hand))
	{
		return 7;
	}
	if (full_house(hand))
	{
		return 6;
	}
	if (flush(hand))
	{
		return 5;
	}
	if (straight(hand))
	{
		return 4;
	}
	if (three_of_a_kind(hand))
	{
		return 3;
	}
	if (two_pair(hand))
	{
		return 2;
	}
	if (pair(hand))
	{
		return 1;
	}
	return 0; // high card, all other hand scores fail
}

int flush(Hand hand)
{
	int suit = hand.cards[0].suit;

	for (int i = 1; i < 5; i++)
	{
		if (hand.cards[i].suit != suit)
		{
			return 0; // not a flush
		}
	}

	return 1; // all of same suit. is a flush
}

int straight(Hand hand)
{
	int count = 0;

	int face_frequency[14] = { 0 };
	for (int i = 0; i < 5; i++)
	{
		face_frequency[hand.cards[i].face + 1] += 1;

		if (hand.cards[i].face == 12) // making it so that the ace can act as either the '1' or the '13' in a straight
		{
			face_frequency[0] += 1;
		}
	}

	for (int i = 0; i < 14; i++)
	{
		if (face_frequency[i])
		{
			count += 1;

			if (count == 5)
			{
				return 1; // is a straight
			}
		}
		else
		{
			count = 0;
		}
	}

	return 0; // is not a straight
}

int four_of_a_kind(Hand hand)
{
	int face_frequency[13] = { 0 };
	for (int i = 0; i < 5; i++)
	{
		face_frequency[hand.cards[i].face] += 1;
	}
	for (int i = 0; i < 13; i++)
	{
		if (face_frequency[i] == 4) // four of a kind
		{
			return 1;
		}
	}

	return 0;
}

int full_house(Hand hand)
{
	int three_of_a_kind = 0, pair = 0;
	int face_frequency[13] = { 0 };
	for (int i = 0; i < 5; i++)
	{
		face_frequency[hand.cards[i].face] += 1;
	}
	for (int i = 0; i < 13; i++)
	{
		if (face_frequency[i] == 3) // three of a kind
		{
			three_of_a_kind = 1;
		}
		if (face_frequency[i] == 2) // pair
		{
			pair = 1;
		}
	}
	if (three_of_a_kind && pair) // if both, then full house
	{
		return 1;
	}
	return 0;
}

int three_of_a_kind(Hand hand)
{
	int face_frequency[13] = { 0 };
	for (int i = 0; i < 5; i++)
	{
		face_frequency[hand.cards[i].face] += 1;
	}
	for (int i = 0; i < 13; i++)
	{
		if (face_frequency[i] == 3) // three of a kind
		{
			return 1;
		}
	}

	return 0;
}

int two_pair(Hand hand)
{
	int pairs = 0;
	int face_frequency[13] = { 0 };
	for (int i = 0; i < 5; i++)
	{
		face_frequency[hand.cards[i].face] += 1;
	}
	for (int i = 0; i < 13; i++)
	{
		if (face_frequency[i] == 2)
		{
			pairs += 1; // tallying number of pairs
		}
	}
	if (pairs == 2) // if two separate pairs are found, then its a two pair
	{
		return 1;
	}
	return 0;
}

int pair(Hand hand)
{
	int face_frequency[13] = { 0 };
	for (int i = 0; i < 5; i++)
	{
		face_frequency[hand.cards[i].face] += 1;
	}
	for (int i = 0; i < 13; i++)
	{
		if (face_frequency[i] == 2) // pair
		{
			return 1;
		}
	}

	return 0;
}

void computer_cards_to_replace(int computer_replaced[5], Hand hand)
{
	int cards_replaced = 0;
	int duplicate_found = 0;

	for (int i = 0; i < 5; i++)
	{
		computer_replaced[i] = 0;
	}

	if (!flush(hand) && !straight(hand)) // if computer already has a flush or straight, all 5 cards should be kept
	{
		for (int i = 0; i < 5 && cards_replaced < 3; i++) // will try to replace cards until all 5 cards are evaluated, or 3 replacements are exhausted
		{
			duplicate_found = 0;
			for (int j = 0; j < 5 && !duplicate_found; j++)
			{
				if (i != j && hand.cards[i].face == hand.cards[j].face) // if there is a duplicate of that face value in the hand, then keep it (making sure not to compare it to itself)
				{
					duplicate_found = 1;
				}
			}
			if (!duplicate_found)
			{
				computer_replaced[i] = 1;
				cards_replaced += 1;
			}
		}
	}

	// printing to the user the number of cards the computer replaced, so they know what to expect and to make it more immersive, since a person would see this in real life
	//the English slightly changes based on 0, 1, or 2 cards

	if (cards_replaced == 0)
	{
		printf("The computer did not replace any cards.\n");
	}
	else if (cards_replaced == 1)
	{
		printf("The computer replaced 1 card.\n");
	}
	else
	{
		printf("The computer replaced %d cards.\n", cards_replaced);
	}
}