#include <string>
#include "headers/card.h"


Card::Card(std::string rank, std::string suit) {
	this->rank = rank;
	this->suit = suit;
}

std::string Card::get_rank() {
	return this->rank;
}

std::string Card::get_suit() {
	return this->suit;
}

std::string Card::get_card() {
	return this->rank + "-" + this->suit;
}