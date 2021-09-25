#include "headers/player.h"

Player::Player(std::string name) {
	this->name = name;
}

void Player::hand_add_card(Card card) {
	this->hand.add_card(card);
}

int Player::get_hand_value() {
	return this->hand.get_total_value();
}

std::string Player::get_hand() {
	return this->hand.get_cards();
}

std::string Player::get_ui_hand() {
	return this->hand.get_ui_cards();
}

std::string Player::get_name() {
	return this->name;
}

int Player::get_wallet() {
	return this->wallet;
}

int Player::get_bet() {
	return this->bet;
}

std::string Player::get_status() {
	return this->status;
}

void Player::set_name(std::string name) {
	this->name = name;
}

void Player::set_wallet(unsigned int wallet) {
	this->wallet = wallet;
}

void Player::set_status(short int status) {
	switch (status) {
	case -1: this->status = "Lost";
			this->wallet -= this->bet;
			break;
	case 0: this->status = "Match";
			break;
	case 1: this->status = "Won";
			this->wallet += this->bet;
			break;
	default:
		break;
	};
}

void Player::add_bet(int bet) {
	this->bet = bet;
}

void Player::flush() {
	this->hand.free();
	this->bet = 0;
	this->status = "...";
	this->blackjack = false;
	this->split = false;
	this->doubleDown = false;
}
