#ifndef UI_H
#define UI_H

#include <string>

struct ui{

    static void title();
    static void start_menu_1();
    static void start_menu_2();
    static void start_menu_3();
    static void start_menu_4();
    static void singleplayer_menu_1();
    static void singleplayer_menu_2();
    static void singleplayer_menu_3();
    static void multiplayer_menu_1();
    static void multiplayer_menu_2();
    static void multiplayer_menu_3();
    static void header(std::string name, unsigned int wallet, unsigned int bet);
    static void header(std::string name, unsigned int wallet, unsigned int bet, int times);
    static void hand(std::string name, std::string hand, int total, bool dealer_first_round = false);
    static void under_construction();

};

#endif