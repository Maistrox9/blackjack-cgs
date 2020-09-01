#ifndef HAND_H
#define HAND_H
#include <vector>
#include "card.h"


class Hand {

	std::vector<Card> cards;
	bool soft = false;
	bool split = false;

	public:
		void add_card(Card card);
		std::string get_card_rank(int i);
		std::string get_card_str(int i);
		std::string get_cards();
		int get_card_value(std::string rank);
		int get_total_value();
		void free();
};


#endif