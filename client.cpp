#include "headers/client.h"
#include <iostream>
#include <limits>

void error(const char *msg) {
    perror(msg);
    exit(0);
}

void check(int exp, const char *msg) {
    if(exp < 0) {
        error(msg);
    }
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

void Client::connect_to_server() {
    check(connect(cli_sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)), "[-]ERROR connecting");

    std::cout << "[+]Connected to Server." << std::endl;
}

void Client::close_socket() {
    close(cli_sock);
}