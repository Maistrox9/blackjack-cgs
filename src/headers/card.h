#ifndef CARD_H
#define CARD_H

#include <string>
#include <vector>

class Card {

	char rank;
	char suit;
	std::vector<std::string> ui_cardv;

	public:
		Card(char rank, char suit);

		char get_rank();

		char get_suit();

		std::string get_card();

		std::vector<std::string> get_ui_cardv();
};


#endif
