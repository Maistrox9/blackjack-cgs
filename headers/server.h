#ifndef SERVER_H
#define SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdint.h>
#include <vector>
#include <string>

class Server {
    int serv_sock, portno;
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t sock_len;
    std::vector<int> clients_sockets;

    int accept_new_connection();
    
    public:
        void send_msg(int client_socket, std::string message);
        void send_msg_to_all(std::string message);
        void send_msg_to_all_except(unsigned int client_number, std::string message);
        void recv_msg(int client_socket, int client_number);
        std::string recv_msg(int client_socket);
        unsigned int get_clients_sockets_size();
        int get_client_socket(int client_position);
        void setup_socket(int port_number);
        void handle_all_connections();
        void listen_for_connections(int number_of_players);
        void close_sockets();
};


#endif