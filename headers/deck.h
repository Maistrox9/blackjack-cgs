#ifndef DECK_H
#define DECK_H

#include <vector>
#include "card.h"

class Deck {

	std::vector<char> rank = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};
	std::vector<char> suit = {'D', 'C', 'H', 'S'};

	public:
		Card deal_card();
};


#endif
