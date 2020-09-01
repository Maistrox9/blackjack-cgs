#include <vector>
#include <string>
#include <iostream>
#include "headers/hand.h"


void Hand::add_card(Card card) {
	this->cards.push_back(card);
}

std::string Hand::get_card_rank(int i) {
	return this->cards[i].get_rank();
}

std::string Hand::get_card_str(int i) {
	return " " + this->cards[i].get_card();
}

std::string Hand::get_cards() {
	std::string cards_tostring = " ";
	for(Card card : this->cards) {
		cards_tostring += card.get_card() + " || ";
	}
	cards_tostring.erase(cards_tostring.size()-4, 4);
	return cards_tostring;
}

int Hand::get_card_value(std::string rank) {
	if(rank == "J" || rank == "Q" || rank == "K") {
		return 10;
	}
	else if(rank == "A") {
		this->soft=true;
		return 11;
	}
	else{
		return std::stoi(rank);
	}
}

int Hand::get_total_value() {
	int total = 0;
	for(Card card : cards) {
		total += get_card_value(card.get_rank());
	}
	if(this->soft && total > 21) {
		total -= 10;
	}
	return total;
}

void Hand::free() {
	this->cards = {};
	this->soft = false;
	this->split = false;
}