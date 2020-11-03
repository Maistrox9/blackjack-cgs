#include <iostream>
#include <sstream>
#include <algorithm>
#include <time.h>
#include <termios.h>
#include <unistd.h>
#include <thread>
#include<ios>
#include<limits>
#include "headers/ui.h"
#include "headers/game.h"
#include "headers/server.h"
#include "headers/client.h"

#define KEY_ENTER 10
#define KEY_ARROW 27
#define KEY_UP 65
#define KEY_DOWN 66
#define KEY_RIGHT 67
#define KEY_LEFT 68
#define KEY_Q 113
#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100

Game game;

void start_menu();
void singleplayer_menu();
void multiplayer_menu();
void instruction_menu();
bool new_game();
void load_game();
void host_new_game();
void game_server(int, int);
bool join_game();
void get_name();
void get_bet();
std::string get_current_dir();
char getch();


int main() {
    srand(time(NULL));
    start_menu();
}

void start_menu(){
    short int next = 1;
    while(true) {
        system("clear");
	    ui::title();
        switch (next) {
            case 1: ui::start_menu_1();
                    break;
            case 2: ui::start_menu_2();
                    break;
            case 3: ui::start_menu_3();
                    break;
            case 4: ui::start_menu_4();
                    break;
        }
        switch(getch()) {
            case KEY_ARROW:
                if(getch() == 91) {
                    switch(getch()) {
                        case KEY_UP:
                            if(next > 1 && next <= 4)
                                next--;
                            else if(next == 1)
                                next = 4;
                            break;

                        case KEY_DOWN:
                            if(next >= 1 && next < 4)
                                next++;
                            else if(next == 4)
                                next = 1;
                            break;
                    }
                }
                break;

            case KEY_W:
                if(next > 1 && next <= 4)
                    next--;
                else if(next == 1)
                    next = 4;
                break;

            case KEY_S:
                if(next >= 1 && next < 4)
                    next++;
                else if(next == 4)
                    next = 1;
                break;

            case KEY_ENTER:
                switch(next) {
                    case 1: singleplayer_menu();
                            break;
                    case 2: multiplayer_menu();
                            break;
                    case 3: instruction_menu();
                            break;
                    case 4: system("clear");
                            exit(0);
                            break;
                }
                break;
        }
    }
}

void singleplayer_menu() {
    bool back = false;
    short int next = 1;
    while(true) {
        system("clear");
	    ui::title();
        switch (next) {
            case 1: ui::singleplayer_menu_1();
                    break;
            case 2: ui::singleplayer_menu_2();
                    break;
            case 3: ui::singleplayer_menu_3();
                    break;
        }
        switch(getch()) {
            case KEY_ARROW:
                if(getch() == 91) {
                    switch(getch()) {
                        case KEY_UP:
                            if(next > 1 && next <= 3)
                                next--;
                            else if(next == 1)
                                next = 3;
                            break;

                        case KEY_DOWN:
                            if(next >= 1 && next < 3)
                                next++;
                            else if(next == 3)
                                next = 1;
                            break;
                    }
                }
                break;

            case KEY_W:
                if(next > 1 && next <= 3)
                    next--;
                else if(next == 1)
                    next = 3;
                break;

            case KEY_S:
                if(next >= 1 && next < 3)
                    next++;
                else if(next == 3)
                    next = 1;
                break;

            case KEY_ENTER:
                switch(next) {
                    case 1: new_game();
                            break;
                    case 2: load_game();
                            break;
                    case 3: back = true;
                            break;
                }
                break;
        }
        if(back)
            break;
    }
}

void multiplayer_menu() {
    bool back = false;
    short int next = 1;
    while(true) {
        system("clear");
	    ui::title();
        switch (next) {
            case 1: ui::multiplayer_menu_1();
                    break;
            case 2: ui::multiplayer_menu_2();
                    break;
            case 3: ui::multiplayer_menu_3();
                    break;
        }
        switch(getch()) {
            case KEY_ARROW:
                if(getch() == 91) {
                    switch(getch()) {
                        case KEY_UP:
                            if(next > 1 && next <= 3)
                                next--;
                            else if(next == 1)
                                next = 3;
                            break;

                        case KEY_DOWN:
                            if(next >= 1 && next < 3)
                                next++;
                            else if(next == 3)
                                next = 1;
                            break;
                    }
                }
                break;

            case KEY_W:
                if(next > 1 && next <= 3)
                    next--;
                else if(next == 1)
                    next = 3;
                break;

            case KEY_S:
                if(next >= 1 && next < 3)
                    next++;
                else if(next == 3)
                    next = 1;
                break;

            case KEY_ENTER:
                switch(next) {
                    case 1: host_new_game();
                            break;
                    case 2: join_game();
                            break;
                    case 3: back = true;
                            break;
                }
                break;
        }
        if(back)
            break;
    }
}

void instruction_menu() {
    system("clear");
    ui::title();
    ui::under_construction();
    //ui::instructions();
    getch();
}

bool new_game() {
    get_name();
    char cont;
    do {
        get_bet();
        //deal fist hand
        game.add_card_player();
        game.add_card_dealer(true);
        game.add_card_player();
        game.add_card_dealer();
        //check player
        std::string p_name = game.get_player_name(), p_hand, d_hand = game.get_dealer_ui_hand(true);
        int p_wallet = game.get_player_wallet(), p_bet = game.get_player_bet(), p_hand_value, d_hand_value = game.get_dealer_hand_value(true);
        std::string hit_stay = "";
        do {
            p_hand_value = game.get_player_hand_value();
            system("clear");
            ui::title();
            ui::header(p_name, p_wallet, p_bet);
            ui::hand("Dealer", d_hand, d_hand_value, true);
            ui::hand("You", game.get_player_ui_hand(), p_hand_value);
            if(p_hand_value == 21)
                std::cout << "BLACKJACK!" << std::endl;
            else if(p_hand_value > 21)
                std::cout << "BUSTED!" << std::endl;
            else {
                do {
                    std::cout << "'hit' or 'stay'?: ";
                    std::cin >> hit_stay;
                } while (hit_stay != "hit" && hit_stay != "stay");
                if (hit_stay == "hit") {
                    game.add_card_player();
                }
            }
        } while(hit_stay == "hit" && p_hand_value < 21);
        p_hand = game.get_player_ui_hand();
        //check dealer
        if(p_hand_value <= 21) {
            do {
                d_hand_value = game.get_dealer_hand_value();
                system("clear");
                ui::title();
                ui::header(p_name, p_wallet, p_bet);
                ui::hand("Dealer", game.get_dealer_ui_hand(), game.get_dealer_hand_value());
                ui::hand("You", p_hand, p_hand_value);
                if(d_hand_value > 21) 
                    std::cout << "Dealer Busted\n" << std::endl;
                else if(d_hand_value < 17) 
                    game.add_card_dealer();
            } while(d_hand_value < 17);
        }
        system("clear");
        ui::title();
        ui::header(p_name, p_wallet, p_bet);
        ui::hand("Dealer", game.get_dealer_ui_hand(), game.get_dealer_hand_value());
        ui::hand("You", p_hand, p_hand_value);
        if(d_hand_value == 21) 
            std::cout << "Dealer BlackJack\n" << std::endl;
        //final status
        if(p_hand_value > 21 || (p_hand_value < d_hand_value && d_hand_value <= 21)) {
            std::cout << "*You: LOST!" << std::endl;
            game.set_player_status(-1);
        }
        else if(p_hand_value <= 21 && (p_hand_value > d_hand_value || d_hand_value > 21)) {
            std::cout << "*You: WON!" << std::endl;
            game.set_player_status(1);
        }
        else if(p_hand_value == d_hand_value) 
            std::cout << "*You: MATCH THE DEALER!" << std::endl;
        game.flush_player();
        game.flush_dealer();
        do {
            std::cout << "continue [y/n]: ";
            std::cin >> cont;
        } while(cont != 'y' && cont != 'n');
        if(cont == 'n')
            return false;

    } while(cont == 'y');

    return true;
}

void load_game() {
    system("clear");
    ui::title();
    ui::under_construction();
    //ui::instructions();
    getch();
}

void host_new_game() {
    int port_number;
    int num_of_players;
    system("clear");
    ui::title();
    //ui::under_construction();
    do {
        std::string s = "";
        std::cout << "Enter port number (Default: 31210): ";
        getline(std::cin, s);
        std::stringstream ss(s);
        try {
            if(s.empty()) port_number = 31210;
            else port_number = std::stoi(s);
        }
        catch(...) {
            port_number = -1;
        }
    } while(port_number < 0 || port_number > 65535);
    do {
        std::cout << "How many players (between 2 and 5): ";
        std::cin >> num_of_players;
    } while(num_of_players < 2 || num_of_players > 5);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::thread client_thread(join_game);
    game_server(port_number, num_of_players);
    client_thread.join();
}

bool join_game() {
    int server_port_number;
    Client client;
    do {
        std::string s = "";
        std::cout << "Enter port number (Default: 31210): ";
        getline(std::cin, s);
        std::stringstream ss(s);
        try {
            if(s.empty()) server_port_number = 31210;
            else server_port_number = std::stoi(s);
        }
        catch(...) {
            server_port_number = -1;
        }
    } while(server_port_number < 0 || server_port_number > 65535);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    client.setup_socket(server_port_number);
    if(!client.connect_to_server()) return false;
    std::string msg;

    //name );
    do {
        msg = client.recv_msg();
        system("clear");
        ui::title();
        std::cout << "==> Server: " << msg << std::endl;
    } while(msg != "Plaese enter your name");
    
    do {
        std::cout << "==> You: ";
        std::cin >> msg;
    } while(msg.size() <= 3);
    
    client.send_msg(msg);

    //bet
    do {
        msg = client.recv_msg();
        system("clear");
        ui::title();
        std::cout << "==> Server: " << msg << std::endl;
    } while(msg != "bet!");

    msg = client.recv_msg();

    int wallet = stoi(msg);
    int bet = 0;

    do {
        std::cout << "==> You: ";
        std::cin >> bet;
        if(bet > wallet)
			std::cout << "==> Game: you don't have that amount" << std::endl;
		else if(bet < 1)
			std::cout << "==> Game: you must bet at least 1$" << std::endl;
    } while(bet > wallet || bet < 1);

    client.send_msg(std::to_string(bet));

    //hit or stay
    int hand_value;
    do {
        do {
            msg = client.recv_msg();
            if(msg.substr(1,6) == "Dealer") {
                system("clear");
                ui::title();
                std::cout << msg << std::endl;
            }
            else
                std::cout << "==> Server: " << msg << std::endl;
        } while(msg != "hit or stay?");

        do {
            std::cout << "==> You: ";
            std::cin >> msg;
        } while (msg != "hit" && msg != "stay");

        client.send_msg(msg);
        if(msg == "hit")
            hand_value = stoi(client.recv_msg());
            
    } while(msg == "hit" && hand_value < 21);

    do {
        msg = client.recv_msg();
        if(msg.substr(0,1) == "\n") {
            system("clear");
            ui::title();
            std::cout << msg << std::endl;
        }
        else
            std::cout << "==> Server: " << msg << std::endl;
    } while(msg != ":exit");

    client.close_socket();

    return true;
}

void game_server(int port_number, int num_of_players) {
    //setup server and connect to clients
    Server server;
    server.setup_socket(port_number);
    server.listen_for_connections(num_of_players);
    //setup game
    Game game;
    server.send_msg_to_all("The Game has finally started. The server will now take everyone's name.");
    //get players names
    for(unsigned int i=0; i < num_of_players; i++) {
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
    for(unsigned int i=0; i < num_of_players; i++) {
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
    std::vector<std::string> all_hands;
    std::string all_hands_str;
    game.add_card_dealer(true);
    for(unsigned int i=0; i < num_of_players; i++) {
        game.add_card_player(i);
    }
    game.add_card_dealer();
    all_hands.push_back(ui::hand_str("Dealer", game.get_dealer_ui_hand(true), game.get_dealer_hand_value(true), true));
    for(unsigned int i=0; i < num_of_players; i++) {
        all_hands.push_back(ui::hand_str(game.get_player_name(i), game.get_player_ui_hand(i), game.get_player_hand_value(i), game.get_player_status(i), game.get_player_blackjack(i)));
    }
    //show hands
    all_hands_str = "";
    std::for_each(all_hands.begin(), all_hands.end(), [&](const std::string &piece){ all_hands_str += piece; });
    server.send_msg_to_all(all_hands_str);
    //check players
    int hand_value;
    for(unsigned int i=0; i < num_of_players; i++) {
        std::string name = game.get_player_name(i);
        server.send_msg_to_all_except(i, "Cheking [" + name + "]....");
        hand_value = game.get_player_hand_value(i);
        do {
            if(hand_value < 21) {
                server.send_msg(server.get_client_socket(i), "hit or stay?");
                msg = server.recv_msg(server.get_client_socket(i));
                if (msg == "hit") {
                    game.add_card_player(i);
                    hand_value = game.get_player_hand_value(i);
                    server.send_msg(server.get_client_socket(i), std::to_string(hand_value));
                    all_hands[i+1] = ui::hand_str(name, game.get_player_ui_hand(i), hand_value, game.get_player_status(i), game.get_player_blackjack(i));
                    all_hands_str = "";
                    std::for_each(all_hands.begin(), all_hands.end(), [&](const std::string &piece){ all_hands_str += piece; });
                    server.send_msg_to_all(all_hands_str + "\n==> Server: " + name + ": " + msg);
                }
                else 
                    server.send_msg_to_all(name + ": " + msg);
            }
            if(hand_value == 21) {
                game.enable_player_blackjack(i);
                all_hands[i+1] = ui::hand_str(name, game.get_player_ui_hand(i), hand_value, game.get_player_status(i), game.get_player_blackjack(i));
                all_hands_str = "";
                std::for_each(all_hands.begin(), all_hands.end(), [&](const std::string &piece){ all_hands_str += piece; });
                server.send_msg_to_all(all_hands_str + "\n==> Server: " + name + " BLACKJACK!");
            }
            else if(hand_value > 21) {
                game.set_player_status(i, -1);
                all_hands[i+1] = ui::hand_str(name, game.get_player_ui_hand(i), hand_value, game.get_player_status(i), game.get_player_blackjack(i));
                all_hands_str = "";
                std::for_each(all_hands.begin(), all_hands.end(), [&](const std::string &piece){ all_hands_str += piece; });
                server.send_msg_to_all(all_hands_str + "\n==> Server: " + name + " BUSTED!");
            }
        } while(msg == "hit" && hand_value < 21);
    }
    //check dealer
    std::string dealer_status;
    do {
        hand_value = game.get_dealer_hand_value();
        if(hand_value == 21)
            dealer_status = "BlackJack!";
		else if(hand_value > 21)
            dealer_status = "BlackJack!";
		else if(hand_value < 17)
			game.add_card_dealer();
    } while(hand_value < 17);
    all_hands[0] = ui::hand_str("Dealer", game.get_dealer_ui_hand(), game.get_dealer_hand_value());
    all_hands_str = "";
    std::for_each(all_hands.begin(), all_hands.end(), [&](const std::string &piece){ all_hands_str += piece; });
	server.send_msg_to_all(all_hands_str + "\n==> Server: Dealer " + dealer_status);
    //final status
    int dealer_hand_value = game.get_dealer_hand_value();
	int player_hand_value = 0;
	for(unsigned int i=0; i < num_of_players; i++) {
		std::string name = game.get_player_name(i);;
		player_hand_value = game.get_player_hand_value(i);
        if(player_hand_value <= 21) {
            if(dealer_hand_value > 21 || player_hand_value > dealer_hand_value) {
                game.set_player_status(i, 1);
                all_hands[i+1] = ui::hand_str(name, game.get_player_ui_hand(i), player_hand_value, game.get_player_status(i), game.get_player_blackjack(i));
            }
            else if(dealer_hand_value <= 21 && player_hand_value < dealer_hand_value) {
                game.set_player_status(i, -1);
                all_hands[i+1] = ui::hand_str(name, game.get_player_ui_hand(i), player_hand_value, game.get_player_status(i), game.get_player_blackjack(i));
            }
            else if(player_hand_value == dealer_hand_value) {
                game.set_player_status(i, 0);
                all_hands[i+1] = ui::hand_str(name, game.get_player_ui_hand(i), player_hand_value, game.get_player_status(i), game.get_player_blackjack(i));
		    }
        }
	}
    all_hands_str = "";
    std::for_each(all_hands.begin(), all_hands.end(), [&](const std::string &piece){ all_hands_str += piece; });
    server.send_msg_to_all(all_hands_str + "\n==> Server: End of Game");
    for(unsigned int i=0; i < num_of_players; i++) {
        game.flush_player(i);
    }
	game.flush_dealer();
    //exit
    usleep(15000000);
    server.send_msg_to_all(":exit");
    server.close_sockets();
}

void get_name() {
    std::string name;
    ui::title;
    std::cout << "Enter your name: ";
    std::cin >> name;
    game.set_player(name);
}

void get_bet() {
    bool done = false;
    int bet = 0, times = 1, wallet = game.get_player_wallet(), wallet_v = wallet;
    std::string name = game.get_player_name();
    while(true) {
        system("clear");
        ui::title();
        ui::header(name, wallet_v, bet, times);
        std::cout << "[bet: ↑ ↓ || W S]\n[times: ← → || A D]\n" << std::endl;
        std::cout << "place your bet!" << std::endl;
        switch (getch()) {
            case KEY_ARROW:
                if(getch() == 91) {
                    switch (getch()) {
                        case KEY_UP:
                            if(bet < wallet && (bet+times) <= wallet) {
                                bet += times;
                                wallet_v -= times;
                            }
                            break;
                        case KEY_DOWN: 
                            if(bet > 0 && (bet-times) >= 0 && (wallet_v+times) <= wallet) {
                                bet -= times;
                                wallet_v += times;
                            }
                            break;
                        case KEY_RIGHT:
                            if(times < 1000000) {
                                switch(std::to_string(times).front()) {
                                    case '1':
                                        times *= 5;
                                        break;
                                    case '5':
                                        times *= 2;
                                        break;
                                }
                            }
                            break;
                        case KEY_LEFT:
                            if(times > 1) {
                                switch(std::to_string(times).front()) {
                                    case '1':
                                        times /= 2;
                                        break;
                                    case '5':
                                        times /= 5;
                                        break;
                                }
                            }
                            break;
                    }
                }
                break;
            case KEY_W:
                if(bet < wallet && (bet+times) <= wallet) {
                    bet += times;
                    wallet_v -= times;
                }
                break;
            case KEY_S:
                if(bet > 0 && (bet-times) >= 0 && (wallet_v+times) <= wallet) {
                    bet -= times;
                    wallet_v += times;
                }
                break;
            case KEY_D:
                if(times < 1000000) {
                    switch(std::to_string(times).front()) {
                        case '1':
                            times *= 5;
                            break;
                        case '5':
                            times *= 2;
                            break;
                    }
                }
                break;
            case KEY_A:
                if(times > 1) {
                    switch(std::to_string(times).front()) {
                        case '1':
                            times /= 2;
                            break;
                        case '5':
                            times /= 5;
                            break;
                    }
                }
                break;
                
            case KEY_ENTER:
                game.set_bet_player(bet);
                done = true;
                break;
        }
        if(done)
            break;
    }
}

std::string get_current_dir() {
   char buff[FILENAME_MAX];
   getcwd( buff, FILENAME_MAX );
   std::string current_dir(buff);
   return current_dir;
}

char getch() {
    char buf = 0;
    struct termios old = {0};
    fflush(stdout);
    if(tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if(tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if(read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if(tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    return buf;
}
