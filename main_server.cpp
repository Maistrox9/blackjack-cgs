#include <iostream>
#include <string>
#include "headers/server.h"
#include "headers/game.h"

int main() {
    //setup server and connect to clients
    Server server;
    server.setup_socket(20202);
    server.listen_for_connections(2);
    //setup game
    Game game;
    std::cout << "[=]Game Started!" << std::endl;
    server.send_msg_to_all("The Game has finally started. The server will now take everyone's name.");
    //get players names
    for(unsigned int i=0; i < server.get_clients_sockets_size(); i++) {
        server.send_msg_to_all_except(i, "Waiting for player " + std::to_string(i+1) + " to enter his name.");
        server.send_msg(server.get_client_socket(i), "Plaese enter your name");
        std::string name = server.recv_msg(server.get_client_socket(i));
        game.add_player(name);
        server.send_msg(server.get_client_socket(i), "Your name [" + name + "] was successfully added.");
        server.send_msg_to_all_except(i, "Player" + std::to_string(i+1) + " name: [" + name + "]");
    }
    //get players bet
    std::string msg;
    server.send_msg_to_all("Betting Now!");
    for(unsigned int i=0; i < server.get_clients_sockets_size(); i++) {
        std::string name = game.get_player_name(i);
		int wallet = game.get_player_wallet(i);
        msg = "[" + name + "] has " + std::to_string(wallet) + "$";
        server.send_msg_to_all(msg);
        server.send_msg_to_all_except(i, "[" + name + "] is betting....");
        server.send_msg(server.get_client_socket(i), "bet!");
        server.send_msg(server.get_client_socket(i), std::to_string(wallet));
        msg = server.recv_msg(server.get_client_socket(i));
        game.set_bet_player(i, std::stoi(msg));
        msg = "[" + name + "] betted " + msg + "$";
        server.send_msg_to_all_except(i, msg);
    }
    //deal first hands
    srand(time(NULL));
    game.deal_first_hands();
    //show hands
    for(unsigned int i=0; i < server.get_clients_sockets_size(); i++) {
        msg = "\n\t" + game.get_player_name(i) + ":\n\t---\n\t" + game.get_player_hand(i) + "\n\t Total: " + std::to_string(game.get_player_hand_value(i)) + "\n\t---";
        server.send_msg_to_all(msg);
    }
    msg = "\n\tDealer:\n\t---\n\t" + game.get_dealer_hand(true) + " || **-******\n\t Total: " + std::to_string(game.get_dealer_hand_value(true)) + "\n\t---";
    server.send_msg_to_all(msg);
    //check players
    int hand_value;
    for(unsigned int i=0; i < server.get_clients_sockets_size(); i++) {
        std::string name = game.get_player_name(i);;
        server.send_msg_to_all_except(i, "Cheking [" + name + "]....");
        hand_value = game.get_player_hand_value(i);
        server.send_msg_to_all("\n\t" + name + ":\n\t---\n\t" + game.get_player_hand(i) + "\n\t Total: " + std::to_string(hand_value) + "\n\t---");
        do {
            if(hand_value < 21) {
                server.send_msg(server.get_client_socket(i), "hit or stay?");
                msg = server.recv_msg(server.get_client_socket(i));
                server.send_msg_to_all_except(i, name + ": " + msg);
                if (msg == "hit") {
                    game.add_card_player(i);
                    hand_value = game.get_player_hand_value(i);
                    server.send_msg(server.get_client_socket(i), std::to_string(hand_value));
                    server.send_msg_to_all("\n\t" + name + ":\n\t---\n\t" + game.get_player_hand(i) + "\n\t Total: " + std::to_string(hand_value) + "\n\t---");
                }
            }
            if(hand_value == 21)
                server.send_msg_to_all(name + " BLACKJACK!");
            else if(hand_value > 21)
                server.send_msg_to_all(name + " BUSTED!");
        } while(msg == "hit" && hand_value < 21);
    }
    //check dealer
    do {
        hand_value = game.get_dealer_hand_value();
        server.send_msg_to_all("\n\tDealer:\n\t---\n\t" + game.get_dealer_hand() + "\n\t Total: " + std::to_string(hand_value) + "\n\t---");
        if(hand_value == 21)
			server.send_msg_to_all("Dealer BlackJack!");
		else if(hand_value > 21)
			server.send_msg_to_all("Dealer Busted!");
		else if(hand_value < 17)
			game.add_card_dealer();
    } while(hand_value < 17);
    //final status
    int dealer_hand_value = game.get_dealer_hand_value();
	int player_hand_value = 0;
	for(unsigned int i=0; i < server.get_clients_sockets_size(); i++) {
		std::string name = game.get_player_name(i);;
		player_hand_value = game.get_player_hand_value(i);
		if(player_hand_value > 21 || (player_hand_value < dealer_hand_value && dealer_hand_value <=21)) {
			server.send_msg_to_all("[" + name + "]: LOST!");
			game.set_lost_player(i);
		}
		else if(player_hand_value <= 21 && (player_hand_value > dealer_hand_value || dealer_hand_value > 21)) {
			server.send_msg_to_all("[" + name + "]: WON!");
			game.set_won_player(i);
		}
		else if(player_hand_value == dealer_hand_value) {
            server.send_msg_to_all("[" + name + "]: MATCH THE DEALER!");
		}
		game.flush_player(i);
	}
	game.flush_dealer();
    //exit
    server.send_msg_to_all(":exit");
    server.close_sockets();
}
