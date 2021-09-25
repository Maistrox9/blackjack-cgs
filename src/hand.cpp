#include <iostream>
#include "headers/hand.h"

void Hand::add_card(Card card) {
	this->cards.push_back(card);
	std::vector<std::string> ui_cardv = card.get_ui_cardv();
	if(this->ui_cards == "") {
		for(int i=0; i < 6; i++) {
			this->ui_cards += ui_cardv[i] + "\n";
		}
	}
	else {
		int n_pos = this->ui_cards.find("\n");
		this->ui_cards.replace(n_pos, 1, ui_cardv[0] + "\n");
		for(int i=1; i < 6; i++) {
			n_pos = this->ui_cards.find("\n", n_pos+1);
			n_pos = this->ui_cards.find("\n", n_pos+1);
			this->ui_cards.replace(n_pos, 1, ui_cardv[i] + "\n");
		}
	}
}

char Hand::get_card_rank(int i) {
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

std::string Hand::get_ui_cards() {
	return this-> ui_cards;
}

int Hand::get_card_value(char rank) {
	if(rank == 'J' || rank == 'Q' || rank == 'K' || rank == 'T') {
		return 10;
	}
	else if(rank == 'A') {
		this->soft=true;
		return 11;
	}
	else{
		return (rank - 48);
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
	this->ui_cards = "";
	this->soft = false;
	this->split = false;
}
