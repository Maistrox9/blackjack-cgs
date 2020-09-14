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

std::string Game::get_player_name(int plyr_pos) {
	return this->players[plyr_pos].get_name();
}

int Game::get_player_wallet() {
	return this->player.get_wallet();
}

int Game::get_player_wallet(int plyr_pos) {
	return this->players[plyr_pos].get_wallet();
}

std::string Game::get_player_hand() {
	return this->player.get_hand();
}

std::string Game::get_player_hand(int plyr_pos) {
	return this->players[plyr_pos].get_hand();
}

std::string Game::get_player_ui_hand() {
	return this->player.get_ui_hand();
}

std::string Game::get_player_ui_hand(int plyr_pos) {
	return this->players[plyr_pos].get_ui_hand();
}

int Game::get_player_hand_value() {
	return this->player.get_hand_value();
}

int Game::get_player_hand_value(int plyr_pos) {
	return this->players[plyr_pos].get_hand_value();
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

int Game::get_player_bet(int plyr_pos) {
	return this->players[plyr_pos].get_bet();
}

void Game::set_player(std::string name, unsigned int wallet) {
	this->player.set_name(name);
	this->player.set_wallet(wallet);
}

void Game::set_bet_player(unsigned int bet) {
	this->player.add_bet(bet);
}

void Game::set_bet_player(int plyr_pos, unsigned int bet) {
	this->players[plyr_pos].add_bet(bet);
}

void Game::set_won_player() {
	this->player.won_bet();
}

void Game::set_won_player(int plyr_pos) {
	this->players[plyr_pos].won_bet();
}

void Game::set_lost_player() {
	this->player.lost_bet();
}

void Game::set_lost_player(int plyr_pos) {
	this->players[plyr_pos].lost_bet();
}

void Game::add_player(std::string name) {
	this->players.push_back(Player(name));
}

void Game::add_card_player() {
	this->player.hand_add_card(this->deck.deal_card());
}

void Game::add_card_player(int plyr_pos) {
	this->players[plyr_pos].hand_add_card(this->deck.deal_card());
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

void Game::flush_player(int plyr_pos) {
	this->players[plyr_pos].flush();
}

void Game::flush_dealer() {
	this->dealer_hand.free();
	this->dealer_first_ui_hand = "";
}

void Game::players_bet() {
	std::string name = "";
	int bet = 0;
	int wallet = 0;
	for(std::vector<Player>::iterator player = this->players.begin(); player != this->players.end(); ++player) {
		name = player->get_name();
		wallet = player->get_wallet();
		std::cout << "*" << name << " has " << wallet << "$" << std::endl;
		do {
			std::cout << name << " bet: ";
			std::cin >> bet;
			if(bet > wallet)
				std::cout << name << "doesn't have that amount" << std::endl;
			else if(bet < 1)
				std::cout << name << "must bet at least 1$" << std::endl;
		} while(bet > wallet || bet < 1);
		player->add_bet(bet);
	}
}

void Game::deal_first_hands() {
	for(int i=0; i < 2; i++) {
		this->dealer_hand.add_card(deck.deal_card());
		for(std::vector<Player>::iterator player = this->players.begin(); player != this->players.end(); ++player) {
			player->hand_add_card(deck.deal_card());
		}
	}
}

void Game::check_players() {
	std::cout << "\nDealer:\n---" << std::endl;
	std::cout << this->dealer_hand.get_card_str(0) << " || **-******" << std::endl;
	std::cout << " Total: " << "> " << this->dealer_hand.get_card_value(dealer_hand.get_card_rank(0)) << "\n---" << std::endl;
	for(std::vector<Player>::iterator player = this->players.begin(); player != this->players.end(); ++player) {
		std::string hit_stay = "";
		int hand_value = 0;
		do {
			hand_value = player->get_hand_value();
			std::cout << "\n" << player->get_name() <<":\n---" << std::endl;
			std::cout << player->get_hand() << std::endl;
			std::cout << " Total: " << hand_value << "\n---" << std::endl;
			if(hand_value == 21) {
				std::cout << "BLACKJACK!" << std::endl;
			}
			else if(hand_value > 21) {
				std::cout << "BUSTED!" << std::endl;
			}
			else {
				do {
					std::cout << "'hit' or 'stay'?: ";
					std::cin >> hit_stay;
					std::transform(hit_stay.begin(), hit_stay.end(), hit_stay.begin(), ::tolower);
				} while (hit_stay != "hit" && hit_stay != "stay");
				if (hit_stay == "hit") {
					player->hand_add_card(deck.deal_card());
				}
			}
		} while(hit_stay == "hit" && hand_value < 21);
	}
}

void Game::check_dealer() {
	int hand_value = 0;
	do {
		hand_value = this->dealer_hand.get_total_value();
		std::cout << "\nDealer:\n---" << std::endl;
		std::cout << this->dealer_hand.get_cards() << std::endl;
		std::cout << " Total: " << hand_value << "\n---\n" << std::endl;
		if(hand_value == 21) {
			std::cout << "Dealer BlackJack\n" << std::endl;
		}
		else if(hand_value > 21) {
			std::cout << "Dealer Busted\n" << std::endl;
		}
		else if(hand_value < 17){
			this->dealer_hand.add_card(deck.deal_card());
		}
	} while(hand_value < 17);
}

void Game::final_status() {
	int dealer_hand_value = this->dealer_hand.get_total_value();
	int player_hand_value = 0;
	std::string player_name = "";
	for(std::vector<Player>::iterator player = this->players.begin(); player != this->players.end(); ++player) {
		player_name = player->get_name();
		player_hand_value = player->get_hand_value();
		if(player_hand_value > 21 || (player_hand_value < dealer_hand_value && dealer_hand_value <=21)) {
			std::cout << "*" << player_name << ": LOST!" << std::endl;
			player->lost_bet();
		}
		else if(player_hand_value <= 21 && (player_hand_value > dealer_hand_value || dealer_hand_value > 21)) {
			std::cout << "*" << player_name << ": WON!" << std::endl;
			player->won_bet();
		}
		else if(player_hand_value == dealer_hand_value) {
			std::cout << "*" << player_name << ": MATCH THE DEALER!" << std::endl;
		}
		player->flush();
	}
	this->dealer_hand.free();
}
