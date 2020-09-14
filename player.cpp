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

void Player::set_name(std::string name) {
	this->name = name;
}

void Player::set_wallet(unsigned int wallet) {
	this->wallet = wallet;
}

void Player::add_bet(int bet) {
	this->bet = bet;
}

void Player::won_bet() {
	this->wallet += this->bet;
}

void Player::lost_bet() {
	this->wallet -= this->bet;
}

void Player::flush() {
	this->hand.free();
	this->bet = 0;
	this->split = false;
	this->doubleDown = false;
}
