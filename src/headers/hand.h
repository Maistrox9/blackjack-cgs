#ifndef HAND_H
#define HAND_H

#include <string>
#include <vector>
#include "card.h"

class Hand {

	std::vector<Card> cards;
	std::string ui_cards;
	bool soft = false;
	bool split = false;

	public:
		void add_card(Card card);
		char get_card_rank(int i);
		std::string get_card_str(int i);
		std::string get_cards();
		std::string get_ui_cards();
		int get_card_value(char rank);
		int get_total_value();
		void free();
};


#endif
