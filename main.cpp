#include <iostream>
#include <time.h>
#include <string>
#include <algorithm>
#include "headers/game.h"


void welcome_start();


int main() {
	welcome_start();
	srand(time(NULL));
	Game game;

	std::string name, add_start;
	do {
		std::cout << "Player name: ";
		std::cin >> name;
		game.add_player(name);
		do {
			std::cout << "'add' or 'start': ";
			std::cin >> add_start;
			std::transform(add_start.begin(), add_start.end(), add_start.begin(), ::tolower);
		} while(add_start != "add" && add_start != "start");
	} while(add_start == "add");

	std::string cont_brk = "";
	do {
		game.players_bet();
		game.deal_first_hands();
		game.check_players();
		game.check_dealer();
		game.final_status();
		do {
			std::cout << "'continue' or 'leave': ";
			std::cin >> cont_brk;
			std::transform(cont_brk.begin(), cont_brk.end(), cont_brk.begin(), ::tolower);
		} while(cont_brk != "continue" && cont_brk != "leave");
	} while(cont_brk == "continue");

	return 0;
}


void welcome_start() {
	// output welcome message at the start
	std::cout << "*********" << std::endl;
	std::cout << "BlackJack" << std::endl;
	std::cout << "*********" << std::endl;
	std::cout << std::endl;
	std::cout << "Welcome to BlackJack!" << std::endl;
	std::cout << "---------------------\n" << std::endl;
}
