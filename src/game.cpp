#include <iostream>
#include <algorithm>
#include "headers/game.h"

std::vector<Player> Game::get_players() {
	return this->players;
}

unsigned int Game::get_players_size() {
	return this->players.size();
}

std::string Game::get_player_name() {
	return this->player.get_name();
}

std::string Game::get_player_name(int plyr_idx) {
	return this->players[plyr_idx].get_name();
}

int Game::get_player_wallet() {
	return this->player.get_wallet();
}

int Game::get_player_wallet(int plyr_idx) {
	return this->players[plyr_idx].get_wallet();
}

std::string Game::get_player_hand() {
	return this->player.get_hand();
}

std::string Game::get_player_hand(int plyr_idx) {
	return this->players[plyr_idx].get_hand();
}

std::string Game::get_player_ui_hand() {
	return this->player.get_ui_hand();
}

std::string Game::get_player_ui_hand(int plyr_idx) {
	return this->players[plyr_idx].get_ui_hand();
}

int Game::get_player_hand_value() {
	return this->player.get_hand_value();
}

int Game::get_player_hand_value(int plyr_idx) {
	return this->players[plyr_idx].get_hand_value();
}

std::string Game::get_player_status() {
	return this->player.get_status();
}

std::string Game::get_player_status(int plyr_idx) {
	return this->players[plyr_idx].get_status();
}

bool Game::get_player_blackjack() {
	return this->player.blackjack;
}

bool Game::get_player_blackjack(int plyr_idx) {
	return this->players[plyr_idx].blackjack;
}

std::string Game::get_dealer_hand(bool first_round) {
	if(first_round)
		return this->dealer_hand.get_card_str(0);
	else
		return this->dealer_hand.get_cards();
}

std::string Game::get_dealer_ui_hand(bool first_round) {
	if(first_round) {
		return this->dealer_first_ui_hand;
	}
	else
		return this->dealer_hand.get_ui_cards();
}

int Game::get_dealer_hand_value(bool first_round) {
	if(first_round)
		return this->dealer_hand.get_card_value(this->dealer_hand.get_card_rank(0));
	else
		return this->dealer_hand.get_total_value();
}

int Game::get_player_bet() {
	return this->player.get_bet();
}

int Game::get_player_bet(int plyr_idx) {
	return this->players[plyr_idx].get_bet();
}

void Game::set_player(std::string name, unsigned int wallet) {
	this->player.set_name(name);
	this->player.set_wallet(wallet);
}

void Game::set_bet_player(unsigned int bet) {
	this->player.add_bet(bet);
}

void Game::set_bet_player(int plyr_idx, unsigned int bet) {
	this->players[plyr_idx].add_bet(bet);
}

void Game::set_player_status(short int status) {
	this->player.set_status(status);
}

void Game::set_player_status(int plyr_idx, short int status) {
	this->players[plyr_idx].set_status(status);
}

void Game::enable_player_blackjack() {
	this->player.blackjack = true;
}

void Game::enable_player_blackjack(int plyr_idx) {
	this->players[plyr_idx].blackjack = true;
}

void Game::add_player(std::string name) {
	this->players.push_back(Player(name));
}

void Game::add_card_player() {
	this->player.hand_add_card(this->deck.deal_card());
}

void Game::add_card_player(int plyr_idx) {
	this->players[plyr_idx].hand_add_card(this->deck.deal_card());
}

void Game::add_card_dealer(bool first_round) {
	this->dealer_hand.add_card(this->deck.deal_card());
	if(first_round) {
		std::string first_ui_hand = dealer_hand.get_ui_cards();
		std::vector<std::string> ui_hidden_cardv {".------.",
								 				R"(|/.--./|)",
								 				R"(|/ // /|)",
								 				R"(|/ // /|)",
								 				R"(|/'--'/|)",
								 				  "`------'"};

		int n_pos = first_ui_hand.find("\n");
		first_ui_hand.replace(n_pos, 1, ui_hidden_cardv[0] + "\n");
		for(int i=1; i < 6; i++) {
			n_pos = first_ui_hand.find("\n", n_pos+1);
			n_pos = first_ui_hand.find("\n", n_pos+1);
			first_ui_hand.replace(n_pos, 1, ui_hidden_cardv[i] + "\n");
		}
		this->dealer_first_ui_hand = first_ui_hand;
	}
}

void Game::flush_player() {
	this->player.flush();
}

void Game::flush_player(int plyr_idx) {
	this->players[plyr_idx].flush();
}

void Game::flush_dealer() {
	this->dealer_hand.free();
	this->dealer_first_ui_hand = "";
}

void Game::deal_first_hands() {
	for(int i=0; i < 2; i++) {
		this->dealer_hand.add_card(deck.deal_card());
		for(std::vector<Player>::iterator player = this->players.begin(); player != this->players.end(); ++player) {
			player->hand_add_card(deck.deal_card());
		}
	}
}
