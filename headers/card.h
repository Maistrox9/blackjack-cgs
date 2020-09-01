#ifndef CARD_H
#define CARD_H


class Card {

	std::string rank;
	std::string suit;

	public:
		Card(std::string rank, std::string suit);

		std::string get_rank();

		std::string get_suit();

		std::string get_card();
};


#endif