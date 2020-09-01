#include "headers/client.h"
#include <iostream>
#include <string>

std::string input_message();

int main() {
    Client client;
    client.setup_socket(20202);
    client.connect_to_server();
    std::string msg;

    //name
    do {
        msg = client.recv_msg();
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
        hand_value = stoi(client.recv_msg());
    } while(msg == "hit" && hand_value < 21);

    do {
        msg = client.recv_msg();
        std::cout << "==> Server: " << msg << std::endl;
    } while(msg != ":exit");

    client.close_socket();
}

std::string input_message() {
    std::string msg;
    std::cout << "==> You: ";
    //std::cin.clear();
    //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, msg);

    return msg;
}