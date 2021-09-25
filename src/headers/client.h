#ifndef CLIENT_H
#define CLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdint.h>
#include <netdb.h>
#include <string>
#include <vector>

class Client {
    int cli_sock, portno, hostname, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char host[256];

    std::string msg;
    uint32_t msg_len;
    std::vector<uint8_t> rcvBuf;

    public:
        void send_msg(std::string message);
        std::string recv_msg();
        void setup_socket(int pn);
        bool connect_to_server();
        void close_socket();
};

#endif
