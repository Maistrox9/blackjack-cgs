#include <iostream>
#include "headers/ui.h"

inline const char * const BoolToString(bool b)
{
  return b ? "true" : "false";
}

void ui::title(){
    std::string str = R"(
        ██████╗ ██╗      █████╗  ██████╗██╗  ██╗     ██╗ █████╗  ██████╗██╗  ██╗
        ██╔══██╗██║     ██╔══██╗██╔════╝██║ ██╔╝     ██║██╔══██╗██╔════╝██║ ██╔╝
        ██████╔╝██║     ███████║██║     █████╔╝      ██║███████║██║     █████╔╝ 
        ██╔══██╗██║     ██╔══██║██║     ██╔═██╗ ██   ██║██╔══██║██║     ██╔═██╗ 
        ██████╔╝███████╗██║  ██║╚██████╗██║  ██╗╚█████╔╝██║  ██║╚██████╗██║  ██╗
        ╚═════╝ ╚══════╝╚═╝  ╚═╝ ╚═════╝╚═╝  ╚═╝ ╚════╝ ╚═╝  ╚═╝ ╚═════╝╚═╝  ╚═╝
    )";

    std::cout << str << std::endl;
}

void ui::start_menu_1(){
    std::string str = R"(
                [X] Single Player
                [ ] Multi Player
                [ ] How to Play
                [ ] Exit
    )";
    
    std::cout << str << std::endl;
}

void ui::start_menu_2(){
    std::string str = R"(
                [ ] Single Player
                [X] Multi Player
                [ ] How to Play
                [ ] Exit
    )";
    
    std::cout << str << std::endl;
}

void ui::start_menu_3(){
    std::string str = R"(
                [ ] Single Player
                [ ] Multi Player
                [X] How to Play
                [ ] Exit
    )";
    
    std::cout << str << std::endl;
}

void ui::start_menu_4(){
    std::string str = R"(
                [ ] Single Player
                [ ] Multi Player
                [ ] How to Play
                [X] Exit
    )";
    
    std::cout << str << std::endl;
}

void ui::singleplayer_menu_1() {
    std::string str = R"(
                [X] New Game
                [ ] Load Game
                [ ] Back
    )";
    
    std::cout << str << std::endl;
}

void ui::singleplayer_menu_2() {
    std::string str = R"(
                [ ] New Game
                [X] Load Game
                [ ] Back
    )";
    
    std::cout << str << std::endl;
}

void ui::singleplayer_menu_3() {
    std::string str = R"(
                [ ] New Game
                [ ] Load Game
                [X] Back
    )";
    
    std::cout << str << std::endl;
}

void ui::multiplayer_menu_1() {
    std::string str = R"(
                [X] Host New Game
                [ ] Join Game
                [ ] Back
    )";
    
    std::cout << str << std::endl;
}

void ui::multiplayer_menu_2() {
    std::string str = R"(
                [ ] Host New Game
                [X] Join Game
                [ ] Back
    )";
    
    std::cout << str << std::endl;
}

void ui::multiplayer_menu_3() {
    std::string str = R"(
                [ ] Host New Game
                [ ] Join Game
                [X] Back
    )";
    
    std::cout << str << std::endl;
}

void ui::header(std::string name, unsigned int wallet, unsigned int bet) {
    std::cout << "\tname: " << name << "\t\t\twallet: " << wallet << "\t\t\tbet: " << bet << std::endl;
}

void ui::header(std::string name, unsigned int wallet, unsigned int bet, int times) {
    std::string str = "\tname " + name + "\t\t\twallet: " + std::to_string(wallet) + "\t\t\tbet: " + std::to_string(bet) + "\n";
    int str_size = str.size();
    for(int i=0; i < str_size; i++) {
        if(str[i] == 'b')
            break;
        if(str[i] == '\t')
            str += '\t';
        else
            str += " ";
    }
    std::cout << str << "times: x" << times << std::endl;
}

void ui::hand(std::string name, std::string hand, int total, bool dealer_first_round) {
    std::cout << "\n" << name << ":\n---" << std::endl;
    std::cout << hand << std::endl;
    if(dealer_first_round)
        std::cout << " Total: " << "> " << total << "\n---" << std::endl;
    else 
        std::cout << " Total: " << total << "\n---" << std::endl;
}

std::string ui::hand_str(std::string name, std::string hand, int total, bool dealer_first_round) {
    if(dealer_first_round)
        return std::string() + "\n" + name + ":\n---\n" + hand + "\n Total: " + "> " + std::to_string(total) + "\n---\n";
    else 
        return std::string() + "\n" + name + ":\n---\n" + hand + "\n Total: " + std::to_string(total) + "\n---\n";
}

std::string ui::hand_str(std::string name, std::string hand, int total, std::string status, bool blackjack) {
    return std::string() + "\n" + name + ":\n---\n" + hand + "\n Total: " + std::to_string(total) + " | Status: " + status + " | BlackJack: " + BoolToString(blackjack) + "\n---\n";
}

void ui::under_construction() {
    std::string str = R"(
         .------------------------------------------------------------------. 
        | .----------------------------------------------------------------. |
        | |                                                                | |
        | |                               __   ___  __                     | |
        | |                    |  | |\ | |  \ |__  |__)                    | |
        | |                    \__/ | \| |__/ |___ |  \                    | |
        | |                                                                | |
        | |      __   __        __  ___  __        __  ___    __           | |
        | |     /  ` /  \ |\ | /__`  |  |__) |  | /  `  |  | /  \ |\ |     | |
        | |     \__, \__/ | \| .__/  |  |  \ \__/ \__,  |  | \__/ | \|     | |
        | |                                                                | |
        | |                                                                | |
        | |                  (Press any key to continue)                   | |
        | '----------------------------------------------------------------' |
         '------------------------------------------------------------------' 
    )";

    std::cout << str << std::endl;
}