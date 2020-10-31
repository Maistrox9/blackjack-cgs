#include <iostream>
#include <algorithm>
#include <time.h>
#include <termios.h>
#include <unistd.h>
#include "headers/ui.h"
#include "headers/game.h"
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
        if(p_hand_value > 21 || (p_hand_value < d_hand_value && d_hand_value <=21)) {
            std::cout << "*You: LOST!" << std::endl;
            game.set_lost_player();
        }
        else if(p_hand_value <= 21 && (p_hand_value > d_hand_value || d_hand_value > 21)) {
            std::cout << "*You: WON!" << std::endl;
            game.set_won_player();
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
    //const char * server_path = (get_current_dir() + "/server").c_str();
    //system(".../Open-Casino-BlackJack/server'");
    //join_game();
    system("clear");
    ui::title();
    ui::under_construction();
    //ui::instructions();
    getch();
}

bool join_game() {
    Client client;
    client.setup_socket(20202);
    if(!client.connect_to_server())
        return false;
    std::string msg;

    //name );

    do {
        std::cout << "==> You: ";
        std::cin >> msg;
    } while(msg.size() <= 3);
    
    client.send_msg(msg);

    //bet
    do {
        msg = client.recv_msg();
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
        std::cout << "==> Server: " << msg << std::endl;
    } while(msg != ":exit");

    client.close_socket();

    return true;
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