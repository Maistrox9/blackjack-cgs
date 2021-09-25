#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>
#include "player.h"
#include "hand.h"
#include "deck.h"

class Game {
	Deck deck;
	Hand dealer_hand;
	std::string dealer_first_ui_hand;
	Player player{"player"};
	std::vector<Player> players;

	public:
		std::vector<Player> get_players();
		unsigned int get_players_size();
		std::string get_player_name();
		std::string get_player_name(int player_index);
		int get_player_wallet();
		int get_player_wallet(int player_index);
		std::string get_player_hand();
		std::string get_player_hand(int player_index);
		std::string get_player_ui_hand();
		std::string get_player_ui_hand(int player_index);
		int get_player_hand_value();
		int get_player_hand_value(int player_index);
		int get_player_bet();
		int get_player_bet(int player_index);
		std::string get_player_status();
		std::string get_player_status(int player_index);
		bool get_player_blackjack();
		bool get_player_blackjack(int player_index);
		std::string get_dealer_hand(bool first_round = false);
		std::string get_dealer_ui_hand(bool first_round = false);
		int get_dealer_hand_value(bool first_round = false);
		void set_player(std::string name, unsigned int wallet = 10000);
		void set_bet_player(unsigned int bet);
		void set_bet_player(int player_index, unsigned int bet);
		void set_player_status(short int status);
		void set_player_status(int player_index, short int status);
		void enable_player_blackjack();
		void enable_player_blackjack(int player_index);
		void add_player(std::string name);
		void add_card_player();
		void add_card_player(int player_index);
		void add_card_dealer(bool firs_round = false);
		void flush_player();
		void flush_player(int player_index);
		void flush_dealer();
		void deal_first_hands();
};


#endif
