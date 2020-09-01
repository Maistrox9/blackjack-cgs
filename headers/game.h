#ifndef GAME_H
#define GAME_H
#include <vector>
#include "player.h"
#include "deck.h"
#include "hand.h"


class Game {
	Deck deck;
	Hand dealer_hand;
	std::vector<Player> players;

	public:
		std::vector<Player> get_players();
		unsigned int get_players_size();
		std::string get_player_name(int player_position);
		int get_player_wallet(int player_position);
		std::string get_player_hand(int player_position);
		int get_player_hand_value(int player_position);
		std::string get_dealer_hand(bool first_round = false);
		int get_dealer_hand_value(bool first_round = false);
		void add_player(std::string name);
		void add_bet_player(int player_position, int bet);
		void add_card_player(int player_position);
		void add_card_dealer();
		void set_won_player(int player_position);
		void set_lost_player(int player_position);
		void flush_player(int player_position);
		void flush_dealer();
		void players_bet();
		void deal_first_hands();
		void check_players();	
		void check_dealer();
		void final_status();
};


#endif