#include "headers/server.h"
#include <iostream>

void error(const char *msg) {
    perror(msg);
    exit(1);
}

void check(int exp, const char *msg) {
    if(exp < 0) {
        error(msg);
    }
}

void Server::send_msg(int cli_sock, std::string msg) {
    uint32_t msg_len;
    msg_len = htonl(msg.size());
    send(cli_sock, &msg_len, sizeof(uint32_t), 0);
    send(cli_sock, msg.c_str(), msg.size(), 0);
}

void Server::send_msg_to_all(std::string msg) {
    for(unsigned int i=0; i < this->clients_sockets.size(); i++) {
        send_msg(this->clients_sockets[i], msg);
    }
}

void Server::send_msg_to_all_except(unsigned int cli_num, std::string msg) {
    for(unsigned int i=0; i < this->clients_sockets.size(); i++) {
        if(i != cli_num)
            send_msg(this->clients_sockets[i], msg);
    }
}

void Server::recv_msg(int cli_sock, int cli_num) {
    uint32_t msg_len;
    std::vector<uint8_t> rcvBuf;
    recv(cli_sock, &msg_len, sizeof(uint32_t), 0);
    msg_len = ntohl(msg_len);
    rcvBuf.resize(msg_len, 0x00);
    recv(cli_sock, &(rcvBuf[0]), msg_len, 0);
    std::string received_msg(rcvBuf.begin(), rcvBuf.end());
    if(received_msg == ":exit") {
        getpeername(cli_sock, (struct sockaddr*)&this->cli_addr, (socklen_t*)&this->sock_len);
        close(cli_sock);
        std::cout << "[X]Disconnected from client" << cli_num << "; " << inet_ntoa(this->cli_addr.sin_addr) << ":" << ntohs(this->cli_addr.sin_port) << std::endl;
    }
    else
        std::cout << "==> Client " << cli_num << ": " << received_msg << std::endl;
}

std::string Server::recv_msg(int cli_sock) {
    uint32_t msg_len;
    std::vector<uint8_t> rcvBuf;
    recv(cli_sock, &msg_len, sizeof(uint32_t), 0);
    msg_len = ntohl(msg_len);
    rcvBuf.resize(msg_len, 0x00);
    recv(cli_sock, &(rcvBuf[0]), msg_len, 0);
    std::string received_msg(rcvBuf.begin(), rcvBuf.end());
    if(received_msg == ":exit") {
        getpeername(cli_sock, (struct sockaddr*)&this->cli_addr, (socklen_t*)&this->sock_len);
        close(cli_sock);
        std::cout << "[X]Disconnected from client; " << inet_ntoa(this->cli_addr.sin_addr) << ":" << ntohs(this->cli_addr.sin_port) << std::endl;
    }
    else
        std::cout << "==> Client: " << received_msg << std::endl;

    return received_msg;
}

unsigned int Server::get_clients_sockets_size() {
    return this->clients_sockets.size();
}

int Server::get_client_socket(int cli_pos) {
    return this->clients_sockets[cli_pos];
}

void Server::setup_socket(int pn) {
    this->portno = pn;
    //create socket
    check(this->serv_sock = socket(AF_INET, SOCK_STREAM, 0), "[-]ERROR opening socket");  
    std::cout << "[+]Server Socket is created." << std::endl;
    //initialize the adress stuct
    bzero((char *) &this->serv_addr, sizeof(this->serv_addr));
    this->serv_addr.sin_family = AF_INET;
    this->serv_addr.sin_addr.s_addr = INADDR_ANY;  
    this->serv_addr.sin_port = htons(this->portno);
    //bind socket
    check(bind(this->serv_sock, (struct sockaddr *) &this->serv_addr, sizeof(this->serv_addr)), "[-]ERROR on Binding");  
    std::cout << "[+]Bind to port " << this->portno << std::endl;
    //listen
    check(listen(this->serv_sock, 5), "[-]Error on Listening");
    std::cout << "[+]Start Listening for new Connections...." << std::endl;
}

int Server::accept_new_connection() {
    int cli_sock;
    check(cli_sock = accept(this->serv_sock, (struct sockaddr *)&this->cli_addr, &this->sock_len), "[-]ERROR on accept");
    std::cout << "[V]Connection accepted from " << inet_ntoa(this->cli_addr.sin_addr) << " port " << ntohs(this->cli_addr.sin_port) << std::endl;
    return cli_sock;
}

void Server::listen_for_connections(int num_of_players) {
    std::string msg;
    this->sock_len = sizeof(this->serv_addr);
    for(int i=0; i < num_of_players; i++) {
        int cli_sock = accept_new_connection();
        msg = "Waiting for (" + std::to_string(num_of_players-(i+1)) + ") more Players to start the game....";
        std::cout << "[=] " + msg << std::endl;
        this->clients_sockets.push_back(cli_sock);
        send_msg(cli_sock, "Welcome To the Server! [Player " + std::to_string(i+1) + "].");
        send_msg_to_all(msg);
    }
}

void Server::close_sockets() {
    for(unsigned int i=0; i < this->clients_sockets.size(); i++) {
        close(this->clients_sockets[i]);
    }
    close(this->serv_sock);
}