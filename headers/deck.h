#ifndef DECK_H
#define DECK_H
#include "card.h"


class Deck {

	std::vector<std::string> rank = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
	std::vector<std::string> suit = {"Diamond", "Clubs", "Hearts", "Spade"};

	public:
		Card deal_card();
};


#endif