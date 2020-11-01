#include <iostream>
#include <limits>
#include <unistd.h>
#include "headers/client.h"

bool check(int exp, const char *msg, bool wait = false) {
    if(exp < 0) {
        perror(msg);
        if(!wait)
            exit(0);
        else
            return false;
    }
    else
        return true;
}

void Client::send_msg(std::string msg) {
    msg_len = htonl(msg.size());
    send(cli_sock, &msg_len, sizeof(uint32_t), 0);
    send(cli_sock, msg.c_str(), msg.size(), 0);
    if(msg == ":exit") {
        close(cli_sock);
        std::cout << "[-]Disconnected from server." << std::endl;
    }
}

std::string Client::recv_msg() {
    recv(cli_sock, &msg_len, sizeof(uint32_t), 0);
    msg_len = ntohl(msg_len);
    rcvBuf.resize(msg_len, 0x00);
    recv(cli_sock, &(rcvBuf[0]), msg_len, 0);
    std::string received_msg(rcvBuf.begin(), rcvBuf.end());

    return received_msg;
}

void Client::setup_socket(int pn) {
    portno = pn;

    // socket
    check(cli_sock = socket(AF_INET, SOCK_STREAM, 0), "[-]ERROR opening socket");

    std::cout << "[+]Client Socket is created." << std::endl;

    // host
    check(hostname = gethostname(host, sizeof(host)), "[-]ERROR getting host name");
    server = gethostbyname(host);
    if (server == NULL) {
        fprintf(stderr,"[-]ERROR, no such host\n");
        exit(0);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));

    //initialize the adress stuct
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);
}

bool Client::connect_to_server() {
    char retry;
    int i;
    std::cout << "[~]Trying to connect to server...." << std::endl;
    do {
        for(i=0; i < 5; i++) {
            if(check(connect(cli_sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)), "[-]Failed to connect to Server.", true))
                break;
            else
                usleep(1000000);
        }
        if(i < 5) {
            std::cout << "[+]Connected to Server." << std::endl;
            break;
        }
        else {
            std::cout << "[-]Couldn't connect to Server." << std::endl;
            do {
                std::cout << "[#]Retry? [y/n]: ";
                std::cin >> retry;
            } while(retry != 'y' && retry != 'n');
            if(retry == 'n')
                return false;
        }
    } while(retry == 'y');

    return true;
}

void Client::close_socket() {
    close(cli_sock);
}
