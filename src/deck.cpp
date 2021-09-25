#include "headers/deck.h"

Card Deck::deal_card() {
	// return one random card
	int rand_rank = rand() % 13;
	int rand_suit = rand() % 4;
	return Card(this->rank[rand_rank], this->suit[rand_suit]);
}
